#include "SoundboardEngine.h"
#include <algorithm>
#include <cmath>

SoundboardEngine::Voice::~Voice()
{
    transport.stop();
    transport.setSource(nullptr);
    readerSource.reset();
    transport.releaseResources();
}

SoundboardEngine::SoundboardEngine(juce::AudioFormatManager& f, juce::TimeSliceThread& t)
    : formats(f), readerThread(t)
{
    addBank("Jingles");
    addBank("Reaktionen");
}

SoundboardEngine::~SoundboardEngine()
{
    stopAll(false);
    // Caller stops the audio processing before destroying the processor.
    std::atomic_store(&voices, std::make_shared<VoiceList>());
}

void SoundboardEngine::prepare(double sampleRate, int maxBlockSize)
{
    hostSampleRate.store(sampleRate);
    hostBlockSize.store(maxBlockSize);
    // A host may re-prepare an existing instance while clips are running.
    const auto running = std::atomic_load(&voices);
    for (const auto& voice : *running)
        voice->transport.prepareToPlay(maxBlockSize, sampleRate);
}

void SoundboardEngine::release()
{
    const auto playing = std::atomic_load(&voices);
    for (const auto& v : *playing)
    {
        v->transport.stop();
        v->finished.store(true);
    }
    publishVoices(std::make_shared<VoiceList>());
}

void SoundboardEngine::publishVoices(std::shared_ptr<VoiceList> next)
{
    retiredSnapshots.push_back({ juce::Time::getMillisecondCounterHiRes(), std::atomic_load(&voices) });
    std::atomic_store(&voices, std::move(next));
}

std::vector<SoundboardEngine::Bank> SoundboardEngine::getBanks() const
{
    const juce::ScopedLock l(banksLock);
    return banks;
}

SoundboardEngine::Bank* SoundboardEngine::findBank(int id)
{
    for (auto& b : banks) if (b.id == id) return &b;
    return nullptr;
}

const SoundboardEngine::Bank* SoundboardEngine::findBank(int id) const
{
    for (const auto& b : banks) if (b.id == id) return &b;
    return nullptr;
}

int SoundboardEngine::addBank(const juce::String& preferredName)
{
    const juce::ScopedLock l(banksLock);
    Bank b;
    b.id = nextBankId++;
    b.name = preferredName.trim().isNotEmpty() ? preferredName.trim() : "Bank " + juce::String(b.id);
    banks.push_back(std::move(b));
    return banks.back().id;
}

bool SoundboardEngine::renameBank(int bankId, const juce::String& name)
{
    const juce::ScopedLock l(banksLock);
    auto* b = findBank(bankId);
    if (b == nullptr || name.trim().isEmpty()) return false;
    b->name = name.trim();
    return true;
}

bool SoundboardEngine::removeBank(int bankId)
{
    const juce::ScopedLock l(banksLock);
    if (banks.size() <= 1) return false;
    auto it = std::find_if(banks.begin(), banks.end(), [bankId](const Bank& b) { return b.id == bankId; });
    if (it == banks.end()) return false;
    banks.erase(it);
    // Existing voices deliberately keep playing after bank removal.
    return true;
}

bool SoundboardEngine::setPad(int bankId, int padIndex, const Pad& pad)
{
    if (!juce::isPositiveAndBelow(padIndex, padsPerBank)) return false;
    const juce::ScopedLock l(banksLock);
    auto* b = findBank(bankId);
    if (b == nullptr) return false;
    b->pads[static_cast<size_t>(padIndex)] = pad;
    return true;
}

bool SoundboardEngine::clearPad(int bankId, int padIndex)
{
    return setPad(bankId, padIndex, Pad{});
}

bool SoundboardEngine::triggerPad(int bankId, int padIndex)
{
    if (!juce::isPositiveAndBelow(padIndex, padsPerBank)) return false;
    Pad pad;
    {
        const juce::ScopedLock l(banksLock);
        const auto* b = findBank(bankId);
        if (b == nullptr) return false;
        pad = b->pads[static_cast<size_t>(padIndex)];
    }
    if (!pad.file.existsAsFile())
    {
        error = "Sample fehlt: " + pad.file.getFileName();
        return false;
    }

    // File I/O and source setup happen on the message thread, not in processBlock.
    std::unique_ptr<juce::AudioFormatReader> reader(formats.createReaderFor(pad.file));
    if (!reader || reader->sampleRate <= 0 || reader->lengthInSamples <= 0)
    {
        error = "Sample nicht lesbar: " + pad.file.getFileName();
        return false;
    }
    auto old = std::atomic_load(&voices);
    if ((int) old->size() >= maxSimultaneousVoices)
    {
        error = "Maximal 24 gleichzeitig spielende Samples";
        return false;
    }
    auto voice = std::make_shared<Voice>(bankId, padIndex);
    voice->loop = pad.loop;
    voice->fadeSeconds = juce::jlimit(0.0f, 10.0f, pad.fadeSeconds);
    const double fileRate = reader->sampleRate;
    voice->readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader.release(), true);
    voice->readerSource->setLooping(pad.loop);
    voice->transport.setSource(voice->readerSource.get(), 32768, &readerThread, fileRate, 2);
    voice->transport.prepareToPlay(hostBlockSize.load(), hostSampleRate.load());
    voice->gain.reset(hostSampleRate.load(), 0.008);
    voice->gain.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(juce::jlimit(-60.f, 6.f, pad.gainDb)));
    voice->transport.start();
    auto next = std::make_shared<VoiceList>(*old);
    next->push_back(voice);
    publishVoices(next);
    error.clear();
    return true;
}

void SoundboardEngine::stopPad(int bankId, int padIndex, bool fade)
{
    auto current = std::atomic_load(&voices);
    for (auto& v : *current)
        if (v->bankId == bankId && v->padIndex == padIndex)
            (fade ? v->fadeOutRequested : v->immediateStop).store(true);
}

void SoundboardEngine::stopAll(bool fade)
{
    auto current = std::atomic_load(&voices);
    for (auto& v : *current)
        (fade ? v->fadeOutRequested : v->immediateStop).store(true);
}

bool SoundboardEngine::isPadActive(int bankId, int padIndex) const
{
    auto current = std::atomic_load(&voices);
    for (const auto& v : *current)
        if (v->bankId == bankId && v->padIndex == padIndex && !v->finished.load())
            return true;
    return false;
}

int SoundboardEngine::activeCount() const
{
    int count = 0;
    auto current = std::atomic_load(&voices);
    for (const auto& v : *current) if (!v->finished.load()) ++count;
    return count;
}

void SoundboardEngine::mixInto(juce::AudioBuffer<float>& output, juce::AudioBuffer<float>& scratch)
{
    const auto active = std::atomic_load(&voices);
    const int numSamples = output.getNumSamples();
    if (scratch.getNumChannels() < 2 || scratch.getNumSamples() == 0) return;
    for (const auto& v : *active)
    {
        if (v->finished.load()) continue;
        if (v->immediateStop.exchange(false)) { v->finished.store(true); continue; }
        if (v->fadeOutRequested.exchange(false))
        {
            v->gain.reset(hostSampleRate.load(), v->fadeSeconds);
            v->gain.setTargetValue(0.0f);
        }
        for (int offset = 0; offset < numSamples && !v->finished.load(); offset += scratch.getNumSamples())
        {
            const int count = juce::jmin(scratch.getNumSamples(), numSamples - offset);
            scratch.clear(0, count);
            juce::AudioSourceChannelInfo info(&scratch, 0, count);
            v->transport.getNextAudioBlock(info);
            const float* srcLeft = scratch.getReadPointer(0);
            const float* srcRight = scratch.getReadPointer(1);
            float* dstLeft = output.getWritePointer(0, offset);
            float* dstRight = output.getWritePointer(1, offset);
            for (int i = 0; i < count; ++i)
            {
                const float g = v->gain.getNextValue();
                dstLeft[i] += srcLeft[i] * g;
                dstRight[i] += srcRight[i] * g;
            }
            if (v->gain.getTargetValue() == 0.0f && !v->gain.isSmoothing())
                v->finished.store(true);
        }
    }
}

void SoundboardEngine::timerTick()
{
    const auto now = juce::Time::getMillisecondCounterHiRes();
    while (!retiredSnapshots.empty() && now - retiredSnapshots.front().timestampMs > 5000.0)
        retiredSnapshots.pop_front(); // Destruct unused voices on message thread.
    const auto current = std::atomic_load(&voices);
    auto next = std::make_shared<VoiceList>();
    next->reserve(current->size());
    bool anyRemoved = false;
    for (const auto& v : *current)
    {
        if (v->finished.load() || (!v->loop && v->transport.hasStreamFinished()))
        {
            v->transport.stop();
            anyRemoved = true;
        }
        else next->push_back(v);
    }
    if (anyRemoved) publishVoices(next);
}

juce::ValueTree SoundboardEngine::saveState() const
{
    juce::ValueTree root("Soundboard");
    const juce::ScopedLock l(banksLock);
    for (const auto& bank : banks)
    {
        juce::ValueTree b("Bank");
        b.setProperty("id", bank.id, nullptr);
        b.setProperty("name", bank.name, nullptr);
        for (int i = 0; i < padsPerBank; ++i)
        {
            const auto& p = bank.pads[static_cast<size_t>(i)];
            if (p.file.getFullPathName().isEmpty()) continue;
            juce::ValueTree s("Pad");
            s.setProperty("index", i, nullptr);
            s.setProperty("file", p.file.getFullPathName(), nullptr);
            s.setProperty("name", p.name, nullptr);
            s.setProperty("gain", p.gainDb, nullptr);
            s.setProperty("loop", p.loop, nullptr);
            s.setProperty("fade", p.fadeSeconds, nullptr);
            b.addChild(s, -1, nullptr);
        }
        root.addChild(b, -1, nullptr);
    }
    return root;
}

void SoundboardEngine::loadState(const juce::ValueTree& state)
{
    if (!state.hasType("Soundboard")) return;
    std::vector<Bank> newBanks;
    int id = 1;
    for (int i = 0; i < state.getNumChildren(); ++i)
    {
        auto b = state.getChild(i);
        if (!b.hasType("Bank")) continue;
        Bank bank;
        bank.id = id++; // Reassign IDs to avoid clashes after imports.
        bank.name = b.getProperty("name", "Bank " + juce::String(bank.id)).toString();
        for (int j = 0; j < b.getNumChildren(); ++j)
        {
            auto s = b.getChild(j);
            const int slot = (int) s.getProperty("index", -1);
            if (!s.hasType("Pad") || !juce::isPositiveAndBelow(slot, padsPerBank)) continue;
            auto& p = bank.pads[static_cast<size_t>(slot)];
            p.file = juce::File(s.getProperty("file").toString());
            p.name = s.getProperty("name").toString();
            p.gainDb = juce::jlimit(-60.f, 6.f, (float) s.getProperty("gain", -6.0));
            p.loop = (bool) s.getProperty("loop", false);
            p.fadeSeconds = juce::jlimit(0.f, 10.f, (float) s.getProperty("fade", 0.7));
        }
        newBanks.push_back(std::move(bank));
    }
    if (newBanks.empty()) { Bank b; b.id = 1; b.name = "Bank 1"; newBanks.push_back(b); id = 2; }
    const juce::ScopedLock l(banksLock);
    banks = std::move(newBanks);
    nextBankId = id;
    // Running samples are not cut off on session restore.
}
