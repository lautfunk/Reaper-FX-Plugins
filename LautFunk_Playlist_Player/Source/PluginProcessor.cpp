#include "PluginProcessor.h"
#include "PluginEditor.h"

LautFunkPlaylistProcessor::LautFunkPlaylistProcessor()
  : juce::AudioProcessor(BusesProperties().withOutput("Stereo Out", juce::AudioChannelSet::stereo(), true)),
    soundboard(formats, readerThread)
{
    volumeParam = new juce::AudioParameterFloat(
        juce::ParameterID { "volume", 1 }, "Player Volume (dB)",
        juce::NormalisableRange<float>(-60.0f, 6.0f, 0.1f), -12.0f);
    addParameter(volumeParam);
    formats.registerBasicFormats();
    readerThread.startThread();
    startTimerHz(20); // EOF detection works even with the UI closed.
}

LautFunkPlaylistProcessor::~LautFunkPlaylistProcessor()
{
    stopTimer();
    cancelPendingUpdate();
    playingWanted = false;
    transport.stop();
    transport.setSource(nullptr);
    fileSource.reset();
    soundboard.release();
    readerThread.stopThread(2000);
}

bool LautFunkPlaylistProcessor::isBusesLayoutSupported(const BusesLayout& layout) const
{
    return layout.getMainOutputChannelSet() == juce::AudioChannelSet::stereo()
        && layout.getMainInputChannelSet().isDisabled();
}

void LautFunkPlaylistProcessor::prepareToPlay(double sampleRate, int blockSize)
{
    transport.prepareToPlay(blockSize, sampleRate);
    gain.reset(sampleRate, 0.025);
    gain.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(volumeParam->get()));
    soundboardScratch.setSize(2, juce::jmax(8192, blockSize));
    soundboard.prepare(sampleRate, blockSize);
}

void LautFunkPlaylistProcessor::releaseResources()
{
    transport.releaseResources();
    soundboard.release();
}

void LautFunkPlaylistProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;
    midi.clear();
    buffer.clear(); // Instrument: generate audio rather than pass the track's input.
    if (buffer.getNumChannels() < 2 || buffer.getNumSamples() == 0)
        return;

    juce::AudioSourceChannelInfo output(&buffer, 0, buffer.getNumSamples());
    transport.getNextAudioBlock(output);

    gain.setTargetValue(juce::Decibels::decibelsToGain(volumeParam->get()));
    auto* left = buffer.getWritePointer(0);
    auto* right = buffer.getWritePointer(1);
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        const float g = gain.getNextValue();
        left[i] *= g;
        right[i] *= g;
    }
    // Independent samples are mixed after playlist volume processing.
    soundboard.mixInto(buffer, soundboardScratch);
}

juce::AudioProcessorEditor* LautFunkPlaylistProcessor::createEditor()
{
    return new LautFunkPlaylistEditor(*this);
}

juce::Array<juce::File> LautFunkPlaylistProcessor::getTrackFiles() const
{
    const juce::ScopedLock lock(playlistLock);
    return tracks;
}

juce::Array<double> LautFunkPlaylistProcessor::getTrackDurations() const
{
    const juce::ScopedLock lock(playlistLock);
    return trackDurations;
}

LautFunkPlaylistProcessor::PlaylistStats LautFunkPlaylistProcessor::getPlaylistStats() const
{
    PlaylistStats result;
    const juce::ScopedLock lock(playlistLock);
    result.trackCount = tracks.size();
    for (const double seconds : trackDurations)
    {
        if (seconds >= 0.0) result.knownSeconds += seconds;
        else if (seconds == -1.0) ++result.pendingDurations;
        else ++result.unavailableDurations;
    }
    return result;
}

LautFunkPlaylistProcessor::RemainingTime LautFunkPlaylistProcessor::getRemainingTime() const
{
    RemainingTime out;
    const double pos = transport.getCurrentPosition();
    const juce::ScopedLock l(playlistLock);
    if (tracks.isEmpty() || currentIndex < 0 || currentIndex >= tracks.size()) return out;
    double total = 0.0;
    for (double seconds : trackDurations)
    {
        if (seconds >= 0.0) total += seconds;
        else out.approximate = true;
    }
    const double thisDuration = trackDurations[currentIndex];
    if (thisDuration >= 0.0) out.seconds = juce::jmax(0.0, thisDuration - pos);
    else { out.seconds = juce::jmax(0.0, transport.getLengthInSeconds() - pos); out.approximate = true; }

    if (repeatMode != RepeatMode::one)
    {
        for (int i = 0; i < trackDurations.size(); ++i)
        {
            if (i == currentIndex) continue;
            const bool pending = shuffle ? !playedShuffleIndices.contains(i) : i > currentIndex;
            if (pending && trackDurations[i] >= 0.0) out.seconds += trackDurations[i];
            else if (pending && trackDurations[i] < 0.0) out.approximate = true;
        }
    }
    // In shuffle mode only the current cycle is considered, not the next loop.
    if (total > 0.0) out.progress = juce::jlimit(0.0, 1.0, 1.0 - out.seconds / total);
    return out;
}

int LautFunkPlaylistProcessor::getCurrentIndex() const
{
    const juce::ScopedLock lock(playlistLock);
    return currentIndex;
}

void LautFunkPlaylistProcessor::appendFiles(const juce::Array<juce::File>& files)
{
    int previousCount = 0;
    int inserted = 0;
    {
        const juce::ScopedLock lock(playlistLock);
        previousCount = tracks.size();
        for (const auto& f : files)
        {
            if (f.existsAsFile() && (f.hasFileExtension("mp3") || f.hasFileExtension("wav")))
            {
                tracks.add(f);
                trackDurations.add(-1.0);
                ++inserted;
            }
        }
        if (inserted > 0 && currentIndex < 0)
            currentIndex = previousCount;
    }
    if (inserted > 0)
    {
        playedShuffleIndices.clear();
        status = juce::String(inserted) + " Datei(en) hinzugefügt";
        ++revision;
    }
    else
    {
        status = "Keine gültigen MP3-/WAV-Dateien ausgewählt";
    }
}

bool LautFunkPlaylistProcessor::importM3U8(const juce::File& playlist)
{
    if (!playlist.existsAsFile())
        return false;
    const auto content = playlist.loadFileAsString();
    juce::StringArray lines;
    lines.addLines(content);
    juce::Array<juce::File> files;
    for (auto line : lines)
    {
        line = line.trim();
        if (line.isEmpty() || line.startsWithChar('#'))
            continue;
        const juce::File f = juce::File::isAbsolutePath(line)
                                  ? juce::File(line)
                                  : playlist.getParentDirectory().getChildFile(line);
        files.add(f);
    }
    const auto before = getTrackFiles().size();
    appendFiles(files);
    return getTrackFiles().size() > before;
}

bool LautFunkPlaylistProcessor::exportM3U8(const juce::File& playlist) const
{
    juce::String m3u = "#EXTM3U\n";
    for (const auto& f : getTrackFiles())
        m3u += f.getFullPathName() + "\n";
    return playlist.replaceWithText(m3u, false, false, "\n");
}

bool LautFunkPlaylistProcessor::loadIndex(int index, bool autoStart)
{
    juce::File f;
    {
        const juce::ScopedLock lock(playlistLock);
        if (!juce::isPositiveAndBelow(index, tracks.size()))
        {
            status = "Playlist ist leer";
            playingWanted = false;
            return false;
        }
        currentIndex = index;
        f = tracks.getReference(index);
    }

    // Open and decode metadata on the message thread, not in processBlock().
    std::unique_ptr<juce::AudioFormatReader> reader(formats.createReaderFor(f));
    if (reader == nullptr)
    {
        playingWanted = false;
        transport.stop();
        transport.setSource(nullptr);
        fileSource.reset();
        status = "Datei fehlt oder kann nicht gelesen werden: " + f.getFileName();
        ++revision;
        return false;
    }

    transport.stop();
    transport.setSource(nullptr);
    fileSource.reset();
    const double sourceSampleRate = reader->sampleRate;
    if (sourceSampleRate > 0.0)
    {
        const auto seconds = static_cast<double>(reader->lengthInSamples) / sourceSampleRate;
        const juce::ScopedLock lock(playlistLock);
        if (juce::isPositiveAndBelow(index, tracks.size()) && tracks[index] == f)
            trackDurations.set(index, juce::jmax(0.0, seconds));
    }
    fileSource = std::make_unique<juce::AudioFormatReaderSource>(reader.release(), true);
    transport.setSource(fileSource.get(), 65536, &readerThread, sourceSampleRate, 2);
    transport.setPosition(0.0);
    playingWanted = autoStart;
    if (autoStart)
        transport.start();
    status = autoStart ? "Wiedergabe" : "Bereit";
    ++revision;
    return true;
}

void LautFunkPlaylistProcessor::startTrack(int index)
{
    playedShuffleIndices.clear();
    loadIndex(index, true);
}

void LautFunkPlaylistProcessor::play()
{
    if (getTrackFiles().isEmpty())
    {
        status = "Bitte zuerst Musik hinzufügen";
        return;
    }
    if (fileSource == nullptr || transport.hasStreamFinished())
    {
        loadIndex(juce::jmax(0, getCurrentIndex()), true);
        return;
    }
    playingWanted = true;
    transport.start();
    status = "Wiedergabe";
}

void LautFunkPlaylistProcessor::pause()
{
    playingWanted = false;
    transport.stop();
    status = "Pause";
}

void LautFunkPlaylistProcessor::stop()
{
    playingWanted = false;
    transport.stop();
    transport.setPosition(0.0);
    status = "Gestoppt";
}

void LautFunkPlaylistProcessor::seekSeconds(double seconds)
{
    transport.setPosition(juce::jlimit(0.0, transport.getLengthInSeconds(), seconds));
}

void LautFunkPlaylistProcessor::next()
{
    const auto files = getTrackFiles();
    if (files.isEmpty()) return;
    int index = getCurrentIndex();
    if (shuffle && files.size() > 1)
    {
        if (!playedShuffleIndices.contains(index)) playedShuffleIndices.add(index);
        juce::Array<int> candidates;
        for (int n = 0; n < files.size(); ++n)
            if (!playedShuffleIndices.contains(n)) candidates.add(n);
        if (candidates.isEmpty())
        {
            playedShuffleIndices.clear();
            for (int n = 0; n < files.size(); ++n)
                if (n != index) candidates.add(n);
        }
        index = candidates[juce::Random::getSystemRandom().nextInt(candidates.size())];
    }
    else
        index = (index + 1) % files.size();
    loadIndex(index, true);
}

void LautFunkPlaylistProcessor::previous()
{
    const auto files = getTrackFiles();
    if (files.isEmpty()) return;
    if (transport.getCurrentPosition() > 3.0)
    {
        transport.setPosition(0.0);
        return;
    }
    int index = getCurrentIndex();
    index = (index + files.size() - 1) % files.size();
    loadIndex(index, true);
}

void LautFunkPlaylistProcessor::advanceAtEnd()
{
    const auto files = getTrackFiles();
    if (files.isEmpty()) { stop(); return; }
    const auto oldIndex = juce::jmax(0, getCurrentIndex());
    int index = oldIndex;
    if (repeatMode == RepeatMode::one)
        index = oldIndex;
    else if (shuffle)
    {
        if (!playedShuffleIndices.contains(oldIndex)) playedShuffleIndices.add(oldIndex);
        juce::Array<int> candidates;
        for (int n = 0; n < files.size(); ++n)
            if (!playedShuffleIndices.contains(n)) candidates.add(n);
        if (candidates.isEmpty())
        {
            if (repeatMode == RepeatMode::off)
            {
                stop();
                status = "Playlist beendet";
                return;
            }
            playedShuffleIndices.clear();
            for (int n = 0; n < files.size(); ++n)
                if (n != oldIndex || files.size() == 1) candidates.add(n);
        }
        index = candidates[juce::Random::getSystemRandom().nextInt(candidates.size())];
    }
    else if (oldIndex + 1 < files.size())
        index = oldIndex + 1;
    else if (repeatMode == RepeatMode::all)
        index = 0;
    else
    {
        stop();
        status = "Playlist beendet";
        return;
    }

    // If a file was removed/moved outside REAPER, attempt the next entry.
    for (int attempt = 0; attempt < files.size(); ++attempt)
    {
        if (loadIndex(index, true))
            return;
        index = (index + 1) % files.size();
    }
    stop();
    status = "Keine abspielbare Datei in der Playlist";
}

void LautFunkPlaylistProcessor::timerCallback()
{
    soundboard.timerTick();
    if (playingWanted.load() && transport.hasStreamFinished())
        advanceAtEnd();

    // Scan at most one pending track per tick. This is deliberately run on the
    // message thread, never in the audio callback. The player keeps playing.
    // MP3/WAV duration is read from file metadata, not from the current track.
    juce::File file;
    int scanIndex = -1;
    {
        const juce::ScopedLock lock(playlistLock);
        for (int i = 0; i < trackDurations.size(); ++i)
        {
            if (trackDurations[i] == -1.0)
            {
                scanIndex = i;
                file = tracks[i];
                break;
            }
        }
    }
    if (scanIndex < 0) return;

    double seconds = -2.0; // File missing or unreadable.
    if (file.existsAsFile())
    {
        std::unique_ptr<juce::AudioFormatReader> reader(formats.createReaderFor(file));
        if (reader != nullptr && reader->sampleRate > 0.0 && reader->lengthInSamples >= 0)
            seconds = static_cast<double>(reader->lengthInSamples) / reader->sampleRate;
    }
    {
        const juce::ScopedLock lock(playlistLock);
        // The list may have been reordered while the file header was read.
        if (juce::isPositiveAndBelow(scanIndex, tracks.size()) &&
            tracks[scanIndex] == file && trackDurations[scanIndex] == -1.0)
        {
            trackDurations.set(scanIndex, seconds);
            ++revision;
        }
    }
}

void LautFunkPlaylistProcessor::setRepeatMode(RepeatMode newMode)
{
    { const juce::ScopedLock lock(playlistLock); repeatMode = newMode; }
    ++revision;
}

void LautFunkPlaylistProcessor::setShuffle(bool enabled)
{
    { const juce::ScopedLock lock(playlistLock); shuffle = enabled; }
    playedShuffleIndices.clear();
    ++revision;
}

void LautFunkPlaylistProcessor::removeTrack(int index)
{
    playedShuffleIndices.clear();
    bool removedCurrent = false;
    bool keepPlaying = playingWanted.load();
    int replacement = -1;
    {
        const juce::ScopedLock lock(playlistLock);
        if (!juce::isPositiveAndBelow(index, tracks.size())) return;
        removedCurrent = currentIndex == index;
        tracks.remove(index);
        trackDurations.remove(index);
        if (tracks.isEmpty()) currentIndex = -1;
        else if (removedCurrent) currentIndex = juce::jmin(index, tracks.size() - 1);
        else if (index < currentIndex) --currentIndex;
        replacement = currentIndex;
    }
    if (removedCurrent)
    {
        if (replacement >= 0) loadIndex(replacement, keepPlaying);
        else
        {
            stop();
            transport.setSource(nullptr);
            fileSource.reset();
        }
    }
    ++revision;
}

void LautFunkPlaylistProcessor::moveTrack(int source, int destination)
{
    playedShuffleIndices.clear();
    const juce::ScopedLock lock(playlistLock);
    if (!juce::isPositiveAndBelow(source, tracks.size()) ||
        !juce::isPositiveAndBelow(destination, tracks.size()) || source == destination)
        return;
    tracks.move(source, destination);
    trackDurations.move(source, destination);
    if (currentIndex == source) currentIndex = destination;
    else if (source < currentIndex && destination >= currentIndex) --currentIndex;
    else if (source > currentIndex && destination <= currentIndex) ++currentIndex;
    ++revision;
}

void LautFunkPlaylistProcessor::clearPlaylist()
{
    playedShuffleIndices.clear();
    stop();
    transport.setSource(nullptr);
    fileSource.reset();
    {
        const juce::ScopedLock lock(playlistLock);
        tracks.clear();
        trackDurations.clear();
        currentIndex = -1;
    }
    status = "Playlist geleert";
    ++revision;
}

void LautFunkPlaylistProcessor::getStateInformation(juce::MemoryBlock& dest)
{
    juce::ValueTree root("LautFunkPlaylist");
    {
        const juce::ScopedLock lock(playlistLock);
        root.setProperty("current", currentIndex, nullptr);
        root.setProperty("repeat", static_cast<int>(repeatMode), nullptr);
        root.setProperty("shuffle", shuffle, nullptr);
        for (const auto& f : tracks)
        {
            juce::ValueTree item("Track");
            item.setProperty("path", f.getFullPathName(), nullptr);
            root.addChild(item, -1, nullptr);
        }
    }
    root.setProperty("volume", volumeParam->get(), nullptr);
    root.addChild(soundboard.saveState(), -1, nullptr);
    if (auto xml = root.createXml())
        juce::AudioProcessor::copyXmlToBinary(*xml, dest);
}

void LautFunkPlaylistProcessor::setStateInformation(const void* data, int size)
{
    auto xml = juce::AudioProcessor::getXmlFromBinary(data, size);
    if (!xml) return;
    const auto tree = juce::ValueTree::fromXml(*xml);
    if (!tree.hasType("LautFunkPlaylist")) return;
    {
        const juce::ScopedLock lock(pendingLock);
        pendingState = tree;
    }
    triggerAsyncUpdate(); // Never open disk files in the host's state callback.
}

void LautFunkPlaylistProcessor::handleAsyncUpdate()
{
    playedShuffleIndices.clear();
    juce::ValueTree state;
    {
        const juce::ScopedLock lock(pendingLock);
        state = pendingState;
        pendingState = {};
    }
    if (!state.isValid()) return;

    stop();
    transport.setSource(nullptr);
    fileSource.reset();
    {
        const juce::ScopedLock lock(playlistLock);
        tracks.clear();
        trackDurations.clear();
        for (int i = 0; i < state.getNumChildren(); ++i)
        {
            auto t = state.getChild(i);
            if (t.hasType("Track"))
            {
                tracks.add(juce::File(t["path"].toString()));
                trackDurations.add(-1.0);
            }
        }
        currentIndex = juce::jlimit(-1, tracks.size() - 1, (int) state.getProperty("current", -1));
        repeatMode = static_cast<RepeatMode>(juce::jlimit(0, 2, (int) state.getProperty("repeat", 1)));
        shuffle = (bool) state.getProperty("shuffle", false);
    }
    auto sb = state.getChildWithName("Soundboard");
    if (sb.isValid()) soundboard.loadState(sb);
    const auto savedGain = juce::jlimit(-60.0f, 6.0f, (float) state.getProperty("volume", -12.0f));
    volumeParam->setValueNotifyingHost(volumeParam->convertTo0to1(savedGain));
    if (getCurrentIndex() >= 0)
        loadIndex(getCurrentIndex(), false); // Safety: don't auto-play on project open.
    ++revision;
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LautFunkPlaylistProcessor();
}
