#include "PluginEditor.h"

namespace
{
    const auto bg = juce::Colour(0xff101720);
    const auto panel = juce::Colour(0xff192734);
    const auto panelBright = juce::Colour(0xff233743);
    const auto teal = juce::Colour(0xff45d8c7);
    const auto white = juce::Colour(0xffedf5f8);
    const auto muted = juce::Colour(0xff94aab8);
}

LautFunkPlaylistEditor::LautFunkPlaylistEditor(LautFunkPlaylistProcessor& p)
    : juce::AudioProcessorEditor(&p), processor(p)
{
    setSize(980, 720);
    setResizable(true, true);
    setResizeLimits(900, 680, 1600, 1040);

    list.setRowHeight(32);
    list.setMultipleSelectionEnabled(false);
    list.setColour(juce::ListBox::backgroundColourId, panel);
    list.setColour(juce::ListBox::outlineColourId, panelBright);
    list.setColour(juce::ListBox::textColourId, white);
    list.setOutlineThickness(1);
    addAndMakeVisible(list);

    for (auto* b : { &addButton, &importButton, &exportButton, &removeButton,
                     &upButton, &downButton, &clearButton,
                     &prevButton, &playButton, &pauseButton, &stopButton, &nextButton })
    {
        setActionButtonStyle(*b, b == &playButton);
        addAndMakeVisible(*b);
    }
    addButton.onClick = [this] { chooseFiles(); };
    importButton.onClick = [this] { choosePlaylist(true); };
    exportButton.onClick = [this] { choosePlaylist(false); };
    removeButton.onClick = [this] {
        const auto row = list.getSelectedRow();
        if (row >= 0) processor.removeTrack(row);
    };
    upButton.onClick = [this] { moveSelection(-1); };
    downButton.onClick = [this] { moveSelection(1); };
    clearButton.onClick = [this] { processor.clearPlaylist(); };
    prevButton.onClick = [this] { processor.previous(); };
    playButton.onClick = [this] {
        const int selected = list.getSelectedRow();
        const int current = processor.getCurrentIndex();
        if (current < 0 && selected >= 0) processor.startTrack(selected);
        else processor.play();
    };
    pauseButton.onClick = [this] { processor.pause(); };
    stopButton.onClick = [this] { processor.stop(); };
    nextButton.onClick = [this] { processor.next(); };

    shuffleButton.setColour(juce::ToggleButton::textColourId, white);
    shuffleButton.setColour(juce::ToggleButton::tickColourId, teal);
    shuffleButton.setToggleState(processor.getShuffle(), juce::dontSendNotification);
    shuffleButton.onClick = [this] { processor.setShuffle(shuffleButton.getToggleState()); };
    addAndMakeVisible(shuffleButton);

    repeatBox.addItem("Repeat: AUS", 1);
    repeatBox.addItem("Repeat: ENDLOS", 2);
    repeatBox.addItem("Repeat: 1 TITEL", 3);
    repeatBox.setTooltip("ENDLOS wiederholt die gesamte Playlist ohne Ende.");
    repeatBox.setColour(juce::ComboBox::backgroundColourId, panel);
    repeatBox.setColour(juce::ComboBox::textColourId, white);
    repeatBox.setColour(juce::ComboBox::outlineColourId, panelBright);
    repeatBox.setSelectedId(static_cast<int>(processor.getRepeatMode()) + 1, juce::dontSendNotification);
    repeatBox.onChange = [this] {
        processor.setRepeatMode(static_cast<LautFunkPlaylistProcessor::RepeatMode>(repeatBox.getSelectedId() - 1));
    };
    addAndMakeVisible(repeatBox);

    gainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 70, 23);
    gainSlider.setRange(-60, 6, 0.1);
    gainSlider.setValue(processor.volumeParam->get(), juce::dontSendNotification);
    gainSlider.setTextValueSuffix(" dB");
    gainSlider.setColour(juce::Slider::thumbColourId, teal);
    gainSlider.setColour(juce::Slider::trackColourId, teal);
    gainSlider.setColour(juce::Slider::backgroundColourId, panelBright);
    gainSlider.setColour(juce::Slider::textBoxTextColourId, white);
    gainSlider.setColour(juce::Slider::textBoxBackgroundColourId, panel);
    gainSlider.setColour(juce::Slider::textBoxOutlineColourId, panelBright);
    gainSlider.onValueChange = [this] {
        auto* prm = processor.volumeParam;
        const auto newNormalized = prm->convertTo0to1(static_cast<float>(gainSlider.getValue()));
        prm->setValueNotifyingHost(newNormalized);
    };
    addAndMakeVisible(gainSlider);

    progressSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    progressSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    progressSlider.setRange(0.0, 1.0, 0.0001);
    progressSlider.setColour(juce::Slider::thumbColourId, teal);
    progressSlider.setColour(juce::Slider::trackColourId, teal);
    progressSlider.setColour(juce::Slider::backgroundColourId, panelBright);
    progressSlider.onDragEnd = [this] {
        processor.seekSeconds(progressSlider.getValue() * processor.getLength());
    };
    addAndMakeVisible(progressSlider);

    for (auto* label : { &nowPlaying, &timeLabel, &statusLabel, &gainLabel, &playlistStats, &repeatStatus })
    {
        label->setColour(juce::Label::textColourId, white);
        addAndMakeVisible(*label);
    }
    nowPlaying.setFont(juce::FontOptions(17.0f).withStyle("Bold"));
    timeLabel.setJustificationType(juce::Justification::centredRight);
    timeLabel.setColour(juce::Label::textColourId, muted);
    statusLabel.setColour(juce::Label::textColourId, muted);
    statusLabel.setFont(juce::FontOptions(12.0f));
    gainLabel.setText("LAUTSTÄRKE", juce::dontSendNotification);
    gainLabel.setColour(juce::Label::textColourId, muted);
    gainLabel.setFont(juce::FontOptions(11.0f));
    playlistStats.setColour(juce::Label::textColourId, white);
    playlistStats.setFont(juce::FontOptions(14.0f).withStyle("Bold"));
    repeatStatus.setJustificationType(juce::Justification::centredRight);
    repeatStatus.setFont(juce::FontOptions(12.0f).withStyle("Bold"));

    updateControls();
    startTimerHz(8);
}

LautFunkPlaylistEditor::~LautFunkPlaylistEditor()
{
    stopTimer();
    chooser.reset();
    list.setModel(nullptr);
}

void LautFunkPlaylistEditor::setActionButtonStyle(juce::TextButton& b, bool primary)
{
    b.setColour(juce::TextButton::buttonColourId, primary ? teal : panelBright);
    b.setColour(juce::TextButton::buttonOnColourId, teal.brighter(0.1f));
    b.setColour(juce::TextButton::textColourOffId, primary ? bg : white);
    b.setColour(juce::TextButton::textColourOnId, bg);
}

void LautFunkPlaylistEditor::paint(juce::Graphics& g)
{
    g.fillAll(bg);
    const auto w = getWidth();
    const auto h = getHeight();

    g.setColour(teal);
    g.setFont(juce::FontOptions(12.0f).withStyle("Bold"));
    g.drawText("LAUTFUNK AUDIO LAB", 22, 14, w - 44, 20,
               juce::Justification::centredLeft);
    g.setColour(white);
    g.setFont(juce::FontOptions(27.0f).withStyle("Bold"));
    g.drawText("PLAYLIST PLAYER", 22, 37, w - 260, 38,
               juce::Justification::centredLeft);
    g.setColour(muted);
    g.setFont(juce::FontOptions(12.0f));
    g.drawText("VST3  |  VERSION 1.0", w - 260, 37, 238, 30,
               juce::Justification::centredRight);

    // Non-overlapping, vertically anchored panels. The list shrinks or grows
    // between the toolbar and the fixed-height playback controls.
    g.setColour(panel);
    g.fillRoundedRectangle(16.0f, 142.0f, static_cast<float>(w - 32),
                           static_cast<float>(h - 396), 10.0f);
    g.fillRoundedRectangle(16.0f, static_cast<float>(h - 252),
                           static_cast<float>(w - 32), 106.0f, 10.0f);

    g.setColour(muted);
    g.setFont(juce::FontOptions(11.0f).withStyle("Bold"));
    g.drawText("AKTUELLER TITEL", 30, h - 244, w - 60, 19,
               juce::Justification::centredLeft);

    if (draggedOver)
    {
        g.setColour(teal.withAlpha(0.15f));
        g.fillRoundedRectangle(getLocalBounds().toFloat().reduced(8), 8);
        g.setColour(teal);
        g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(8), 8, 2);
    }
}

void LautFunkPlaylistEditor::resized()
{
    const auto w = getWidth();
    const auto h = getHeight();
    const int margin = 22;
    const int toolbarGap = 8;
    const int weights[] = { 124, 118, 146, 114, 66, 72, 90 };
    const int totalWeight = 730;
    const int usable = w - 2 * margin - 6 * toolbarGap;
    const int widths[] = {
        usable * weights[0] / totalWeight,
        usable * weights[1] / totalWeight,
        usable * weights[2] / totalWeight,
        usable * weights[3] / totalWeight,
        usable * weights[4] / totalWeight,
        usable * weights[5] / totalWeight,
        usable * weights[6] / totalWeight
    };
    juce::TextButton* toolbarButtons[] = {
        &addButton, &importButton, &exportButton, &removeButton,
        &upButton, &downButton, &clearButton
    };
    int x = margin;
    for (int i = 0; i < 7; ++i)
    {
        const int buttonWidth = (i == 6) ? w - margin - x : widths[i];
        toolbarButtons[i]->setBounds(x, 88, buttonWidth, 37);
        x += buttonWidth + toolbarGap;
    }

    playlistStats.setBounds(30, 150, w - 270, 31);
    repeatStatus.setBounds(w - 245, 150, 210, 31);
    list.setBounds(24, 193, w - 48, h - 458);

    nowPlaying.setBounds(30, h - 218, w - 306, 28);
    timeLabel.setBounds(w - 266, h - 218, 232, 28);
    progressSlider.setBounds(30, h - 184, w - 60, 28);

    const int buttonWidth = 112;
    const int gap = 10;
    x = (w - (5 * buttonWidth + 4 * gap)) / 2;
    for (auto* b : { &prevButton, &playButton, &pauseButton, &stopButton, &nextButton })
    {
        b->setBounds(x, h - 139, buttonWidth, 42);
        x += buttonWidth + gap;
    }
    statusLabel.setBounds(28, h - 89, w - 56, 21);

    repeatBox.setBounds(26, h - 58, 196, 36);
    shuffleButton.setBounds(235, h - 56, 134, 32);
    gainLabel.setBounds(w - 373, h - 53, 93, 24);
    gainSlider.setBounds(w - 278, h - 60, 250, 39);
}

int LautFunkPlaylistEditor::getNumRows()
{
    return snapshot.size();
}

void LautFunkPlaylistEditor::paintListBoxItem(int row, juce::Graphics& g,
                                              int width, int height, bool selected)
{
    if (!juce::isPositiveAndBelow(row, snapshot.size())) return;
    const bool current = row == processor.getCurrentIndex();
    const bool missing = !snapshot[row].existsAsFile();
    g.setColour(selected ? juce::Colour(0xff254654) : (row % 2 == 0 ? panel : juce::Colour(0xff1d2d3a)));
    g.fillRect(0, 0, width, height);
    g.setColour(current ? teal : muted);
    g.setFont(juce::FontOptions(12.0f));
    g.drawText(juce::String(row + 1).paddedLeft('0', 2), 10, 0, 33, height, juce::Justification::centredLeft);
    g.setColour(missing ? juce::Colours::tomato : (current ? teal : white));
    g.setFont(juce::FontOptions(14.0f).withStyle(current ? "Bold" : "Plain"));
    g.drawFittedText(snapshot[row].getFileName(), 53, 1, width - 228, height - 2,
                     juce::Justification::centredLeft, 1);
    g.setColour(missing ? juce::Colours::tomato : muted);
    g.setFont(juce::FontOptions(11.0f));
    g.drawText(missing ? "FEHLT" : snapshot[row].getFileExtension().toUpperCase(),
               width - 166, 0, 70, height, juce::Justification::centredRight);

    const double seconds = juce::isPositiveAndBelow(row, snapshotDurations.size())
                               ? snapshotDurations[row] : -1.0;
    g.setColour(seconds < -1.5 ? juce::Colours::tomato : muted);
    g.setFont(juce::FontOptions(12.0f));
    g.drawText(seconds >= 0.0 ? secondsToText(seconds)
                              : (seconds < -1.5 ? "--:--" : "…"),
               width - 95, 0, 85, height, juce::Justification::centredRight);
}

void LautFunkPlaylistEditor::listBoxItemDoubleClicked(int row, const juce::MouseEvent&)
{
    processor.startTrack(row);
}

void LautFunkPlaylistEditor::moveSelection(int offset)
{
    const int selected = list.getSelectedRow();
    const int destination = selected + offset;
    if (!juce::isPositiveAndBelow(destination, processor.getTrackFiles().size())) return;
    processor.moveTrack(selected, destination);
    updateControls();
    list.selectRow(destination);
}

juce::String LautFunkPlaylistEditor::secondsToText(double sec)
{
    const auto total = juce::jmax(0, (int) sec);
    const auto hours = total / 3600;
    const auto minutes = (total % 3600) / 60;
    const auto seconds = total % 60;
    if (hours > 0)
        return juce::String::formatted("%d:%02d:%02d", hours, minutes, seconds);
    return juce::String::formatted("%02d:%02d", minutes, seconds);
}

void LautFunkPlaylistEditor::timerCallback()
{
    updateControls();
}

void LautFunkPlaylistEditor::updateControls()
{
    const auto rev = processor.getRevision();
    const auto index = processor.getCurrentIndex();
    if (rev != lastRevision)
    {
        const bool changedTrack = (index != lastIndex);
        lastIndex = index;
        lastRevision = rev;
        snapshot = processor.getTrackFiles();
        snapshotDurations = processor.getTrackDurations();
        list.updateContent();
        list.repaint();
        if (changedTrack && index >= 0)
            list.scrollToEnsureRowIsOnscreen(index);
        repeatBox.setSelectedId(static_cast<int>(processor.getRepeatMode()) + 1, juce::dontSendNotification);
        shuffleButton.setToggleState(processor.getShuffle(), juce::dontSendNotification);
    }
    const auto files = processor.getTrackFiles();
    const auto name = juce::isPositiveAndBelow(index, files.size())
                          ? files[index].getFileNameWithoutExtension() : "Keine Datei ausgewählt";
    nowPlaying.setText(name, juce::dontSendNotification);
    nowPlaying.setTooltip(name);
    const double duration = processor.getLength();
    timeLabel.setText(secondsToText(processor.getPosition()) + " / " + secondsToText(duration),
                      juce::dontSendNotification);
    if (!progressSlider.isMouseButtonDown())
        progressSlider.setValue(duration > 0 ? processor.getPosition() / duration : 0.0,
                                juce::dontSendNotification);
    if (!gainSlider.isMouseButtonDown())
        gainSlider.setValue(processor.volumeParam->get(), juce::dontSendNotification);
    statusLabel.setText(processor.getStatus(), juce::dontSendNotification);

    const auto stats = processor.getPlaylistStats();
    juce::String summary = juce::String(stats.trackCount) + " TITEL   |   GESAMTSPIELZEIT  "
                           + secondsToText(stats.knownSeconds);
    if (stats.pendingDurations > 0)
        summary += "   (" + juce::String(stats.pendingDurations) + " werden gelesen)";
    if (stats.unavailableDurations > 0)
        summary += "   (" + juce::String(stats.unavailableDurations) + " ohne Dauer)";
    playlistStats.setText(summary, juce::dontSendNotification);

    const auto repeat = processor.getRepeatMode();
    const bool endlos = repeat == LautFunkPlaylistProcessor::RepeatMode::all;
    repeatStatus.setText(endlos ? "ENDLOS AKTIV" :
                         repeat == LautFunkPlaylistProcessor::RepeatMode::one
                             ? "1 TITEL WIEDERHOLEN" : "REPEAT AUS", juce::dontSendNotification);
    repeatStatus.setColour(juce::Label::textColourId, endlos ? teal : muted);
}

void LautFunkPlaylistEditor::chooseFiles()
{
    chooser = std::make_unique<juce::FileChooser>("MP3/WAV zur Playlist hinzufügen", juce::File{}, "*.mp3;*.wav");
    const juce::Component::SafePointer<LautFunkPlaylistEditor> safe(this);
    chooser->launchAsync(juce::FileBrowserComponent::openMode
                       | juce::FileBrowserComponent::canSelectMultipleItems
                       | juce::FileBrowserComponent::canSelectFiles,
        [safe](const juce::FileChooser& c)
        {
            if (safe != nullptr) safe->processor.appendFiles(c.getResults());
        });
}

void LautFunkPlaylistEditor::choosePlaylist(bool importing)
{
    chooser = std::make_unique<juce::FileChooser>(
        importing ? "Playlist öffnen" : "Playlist speichern",
        juce::File::getSpecialLocation(juce::File::userDocumentsDirectory), "*.m3u8");
    const juce::Component::SafePointer<LautFunkPlaylistEditor> safe(this);
    chooser->launchAsync(importing
                 ? (juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles)
                 : (juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::warnAboutOverwriting),
        [safe, importing](const juce::FileChooser& c)
        {
            if (safe == nullptr) return;
            auto f = c.getResult();
            if (f == juce::File{}) return;
            if (!importing && !f.hasFileExtension("m3u8")) f = f.withFileExtension("m3u8");
            if (importing) safe->processor.importM3U8(f);
            else safe->processor.exportM3U8(f);
        });
}

bool LautFunkPlaylistEditor::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (const auto& f : files)
        if (juce::File(f).hasFileExtension("mp3;wav;m3u8")) return true;
    return false;
}

void LautFunkPlaylistEditor::filesDropped(const juce::StringArray& paths, int, int)
{
    juce::Array<juce::File> files;
    for (const auto& path : paths)
    {
        const juce::File f(path);
        if (f.hasFileExtension("m3u8")) processor.importM3U8(f);
        else files.add(f);
    }
    processor.appendFiles(files);
    draggedOver = false;
    repaint();
}
