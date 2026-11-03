#include "PluginEditor.h"
#include <algorithm>

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
    setSize(1080, 780);
    setResizable(true, true);
    setResizeLimits(950, 715, 1800, 1200);

    for (auto* b : { &playlistTab, &soundboardTab, &addButton, &importButton,
                     &exportButton, &removeButton, &upButton, &downButton,
                     &clearButton, &prevButton, &playButton, &pauseButton,
                     &stopButton, &nextButton, &newBank, &deleteBank,
                     &prevPage, &nextPage, &stopAllButton, &fadeAllButton,
                     &loadPadButton, &clearPadButton, &stopPadButton, &fadePadButton, &bankFileButton, &folderImportButton })
    {
        setActionButtonStyle(*b, b == &playButton || b == &soundboardTab);
        addAndMakeVisible(*b);
    }
    playlistTab.onClick = [this] { showMode(false); };
    soundboardTab.onClick = [this] { showMode(true); };

    list.setRowHeight(32);
    list.setMultipleSelectionEnabled(false);
    list.setColour(juce::ListBox::backgroundColourId, panel);
    list.setColour(juce::ListBox::outlineColourId, panelBright);
    list.setOutlineThickness(1);
    addAndMakeVisible(list);

    addButton.onClick = [this] { chooseFiles(); };
    importButton.onClick = [this] { choosePlaylist(true); };
    exportButton.onClick = [this] { choosePlaylist(false); };
    removeButton.onClick = [this] { const int row = list.getSelectedRow(); if (row >= 0) processor.removeTrack(row); };
    upButton.onClick = [this] { moveSelection(-1); };
    downButton.onClick = [this] { moveSelection(1); };
    clearButton.onClick = [this] { processor.clearPlaylist(); };
    prevButton.onClick = [this] { processor.previous(); };
    playButton.onClick = [this] {
        const int selected = list.getSelectedRow();
        if (processor.getCurrentIndex() < 0 && selected >= 0) processor.startTrack(selected);
        else processor.play();
    };
    pauseButton.onClick = [this] { processor.pause(); };
    stopButton.onClick = [this] { processor.stop(); };
    nextButton.onClick = [this] { processor.next(); };

    shuffleButton.setColour(juce::ToggleButton::textColourId, white);
    shuffleButton.setColour(juce::ToggleButton::tickColourId, teal);
    shuffleButton.onClick = [this] { processor.setShuffle(shuffleButton.getToggleState()); };
    addAndMakeVisible(shuffleButton);

    repeatBox.addItem("Repeat: AUS", 1);
    repeatBox.addItem("Repeat: ENDLOS", 2);
    repeatBox.addItem("Repeat: 1 TITEL", 3);
    repeatBox.onChange = [this] {
        processor.setRepeatMode(static_cast<LautFunkPlaylistProcessor::RepeatMode>(repeatBox.getSelectedId() - 1));
    };
    addAndMakeVisible(repeatBox);

    gainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 70, 23);
    gainSlider.setRange(-60.0, 6.0, 0.1);
    gainSlider.setTextValueSuffix(" dB");
    gainSlider.onValueChange = [this] {
        auto* prm = processor.volumeParam;
        prm->setValueNotifyingHost(prm->convertTo0to1((float) gainSlider.getValue()));
    };
    addAndMakeVisible(gainSlider);
    progressSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    progressSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    progressSlider.setRange(0.0, 1.0, 0.0001);
    progressSlider.onDragEnd = [this] { processor.seekSeconds(progressSlider.getValue() * processor.getLength()); };
    addAndMakeVisible(progressSlider);

    for (auto* l : { &nowPlaying, &timeLabel, &statusLabel, &gainLabel, &playlistStats,
                     &repeatStatus, &bankStatus, &padDetails })
    {
        l->setColour(juce::Label::textColourId, white);
        addAndMakeVisible(*l);
    }
    nowPlaying.setFont(juce::FontOptions(17.0f).withStyle("Bold"));
    timeLabel.setJustificationType(juce::Justification::centredRight);
    timeLabel.setColour(juce::Label::textColourId, muted);
    statusLabel.setColour(juce::Label::textColourId, muted);
    gainLabel.setText("LAUTSTÄRKE", juce::dontSendNotification);
    gainLabel.setColour(juce::Label::textColourId, muted);
    playlistStats.setFont(juce::FontOptions(14.0f).withStyle("Bold"));
    repeatStatus.setJustificationType(juce::Justification::centredRight);
    bankStatus.setColour(juce::Label::textColourId, muted);
    padDetails.setColour(juce::Label::textColourId, muted);

    bankBox.onChange = [this] {
        if (bankBox.getSelectedId() > 0)
        {
            currentBankId = bankBox.getSelectedId();
            processor.setMidiBank(currentBankId);
            selectedPad = -1;
            updatePadSelection();
            updateBoard();
        }
    };
    padViewBox.addItem("12 Pads", 1);
    padViewBox.addItem("24 Pads", 2);
    padViewBox.setSelectedId(1, juce::dontSendNotification);
    padViewBox.onChange = [this] {
        padCount = padViewBox.getSelectedId() == 2 ? 24 : 12;
        padPage = 0; selectedPad = -1;
        resized(); updateBoard();
    };
    for (auto* b : { &bankBox, &padViewBox })
    {
        b->setColour(juce::ComboBox::backgroundColourId, panel);
        b->setColour(juce::ComboBox::textColourId, white);
        b->setColour(juce::ComboBox::outlineColourId, panelBright);
        addAndMakeVisible(*b);
    }
    bankName.setColour(juce::TextEditor::backgroundColourId, panel);
    bankName.setColour(juce::TextEditor::textColourId, white);
    bankName.setColour(juce::TextEditor::outlineColourId, panelBright);
    bankName.setSelectAllWhenFocused(true);
    bankName.onReturnKey = [this] { applyBankName(); };
    bankName.onFocusLost = [this] { applyBankName(); };
    addAndMakeVisible(bankName);
    bankFileButton.onClick = [this] {
        juce::PopupMenu menu;
        menu.addItem(1, "Bank laden ...");
        menu.addItem(2, "Bank speichern ...");
        const juce::Component::SafePointer<LautFunkPlaylistEditor> safe(this);
        menu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(&bankFileButton),
            [safe](int choice) {
                if (safe == nullptr) return;
                if (choice == 1) safe->chooseBankFile(true);
                else if (choice == 2) safe->chooseBankFile(false);
            });
    };
    folderImportButton.onClick = [this] { chooseSampleFolder(); };
    newBank.onClick = [this] {
        const auto banks = processor.getSoundboard().getBanks();
        currentBankId = processor.getSoundboard().addBank("Bank " + juce::String(banks.size() + 1));
        processor.setMidiBank(currentBankId);
        lastBankSignature.clear(); updateBoard();
    };
    deleteBank.onClick = [this] {
        if (processor.getSoundboard().removeBank(currentBankId))
        {
            currentBankId = processor.getSoundboard().getBanks().front().id;
            processor.setMidiBank(currentBankId);
            lastBankSignature.clear(); selectedPad = -1; updateBoard();
        }
    };
    prevPage.onClick = [this] { padPage = 0; selectedPad = -1; updatePadSelection(); resized(); updateBoard(); };
    nextPage.onClick = [this] { padPage = 1; selectedPad = -1; updatePadSelection(); resized(); updateBoard(); };
    stopAllButton.onClick = [this] { processor.getSoundboard().stopAll(false); };
    fadeAllButton.onClick = [this] { processor.getSoundboard().stopAll(true); };

    for (int i = 0; i < (int) padButtons.size(); ++i)
    {
        auto& b = padButtons[(size_t)i];
        setActionButtonStyle(b);
        b.setTooltip("Linksklick: One-Shot starten | Rechtsklick: Menü / Einstellungen");
        b.onClick = [this, i] {
            const int slot = visiblePadToSlot(i);
            selectPad(slot);
            auto& engine = processor.getSoundboard();
            const auto banks = engine.getBanks();
            for (const auto& bank : banks)
                if (bank.id == currentBankId && bank.pads[(size_t)slot].file.existsAsFile())
                {
                    if (bank.pads[(size_t)slot].loop && engine.isPadActive(currentBankId, slot))
                        engine.stopPad(currentBankId, slot, false);
                    else engine.triggerPad(currentBankId, slot);
                    break;
                }
        };
        b.onRightClick = [this, i] { openPadMenu(visiblePadToSlot(i)); };
        addAndMakeVisible(b);
    }
    loadPadButton.onClick = [this] { if (selectedPad >= 0) assignSample(selectedPad); };
    clearPadButton.onClick = [this] {
        if (selectedPad >= 0) { processor.getSoundboard().clearPad(currentBankId, selectedPad); updateBoard(); }
    };
    stopPadButton.onClick = [this] {
        if (selectedPad >= 0) processor.getSoundboard().stopPad(currentBankId, selectedPad, false);
    };
    fadePadButton.onClick = [this] {
        if (selectedPad >= 0) processor.getSoundboard().stopPad(currentBankId, selectedPad, true);
    };
    loopPad.setColour(juce::ToggleButton::textColourId, white);
    loopPad.setColour(juce::ToggleButton::tickColourId, teal);
    loopPad.onClick = [this] { updateSelectedPad([this](SoundboardEngine::Pad& p) { p.loop = loopPad.getToggleState(); }); };
    addAndMakeVisible(loopPad);
    padGain.setRange(-60.0, 6.0, 0.5);
    padGain.setTextValueSuffix(" dB");
    padGain.setTextBoxStyle(juce::Slider::TextBoxRight, false, 72, 22);
    padGain.onValueChange = [this] {
        updateSelectedPad([this](SoundboardEngine::Pad& p) { p.gainDb = (float) padGain.getValue(); });
    };
    padFade.setRange(0.0, 10.0, 0.1);
    padFade.setTextValueSuffix(" s Fade");
    padFade.setTextBoxStyle(juce::Slider::TextBoxRight, false, 88, 22);
    padFade.onValueChange = [this] {
        updateSelectedPad([this](SoundboardEngine::Pad& p) { p.fadeSeconds = (float) padFade.getValue(); });
    };
    for (auto* slider : { &padGain, &padFade })
    {
        slider->setSliderStyle(juce::Slider::LinearHorizontal);
        addAndMakeVisible(*slider);
    }

    // Soundboard ducking is optional and remains separate from sample volume.
    duckEnabledButton.setColour(juce::ToggleButton::textColourId, white);
    duckEnabledButton.setColour(juce::ToggleButton::tickColourId, teal);
    duckEnabledButton.onClick = [this] {
        processor.duckEnabledParam->setValueNotifyingHost(
            duckEnabledButton.getToggleState() ? 1.f : 0.f);
    };
    addAndMakeVisible(duckEnabledButton);

    const auto configureDuck = [this](juce::Slider& slider,
                                      juce::AudioParameterFloat& param,
                                      const juce::String& suffix, int textWidth) {
        slider.setSliderStyle(juce::Slider::LinearHorizontal);
        slider.setTextBoxStyle(juce::Slider::TextBoxRight, false, textWidth, 22);
        slider.setRange(param.range.start, param.range.end, param.range.interval);
        slider.setTextValueSuffix(suffix);
        slider.setValue(param.get(), juce::dontSendNotification);
        slider.setColour(juce::Slider::thumbColourId, teal);
        slider.setColour(juce::Slider::trackColourId, teal);
        slider.setColour(juce::Slider::backgroundColourId, panelBright);
        slider.onValueChange = [&slider, &param] {
            param.setValueNotifyingHost(param.convertTo0to1((float) slider.getValue()));
        };
        addAndMakeVisible(slider);
    };
    configureDuck(duckDepthSlider, *processor.duckDepthParam, " dB", 66);
    configureDuck(duckAttackSlider, *processor.duckAttackParam, " ms", 76);
    configureDuck(duckReleaseSlider, *processor.duckReleaseParam, " ms", 78);
    duckDepthSlider.setTooltip("Ducking-Absenkung der Playlist-Musik in dB");
    duckAttackSlider.setTooltip("Wie schnell die Playlist leiser wird (Millisekunden)");
    duckReleaseSlider.setTooltip("Wie schnell die Musik nach Samples wieder ansteigt");

    showMode(false);
    updateControls();
    updateBoard();
    updatePadSelection();
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

void LautFunkPlaylistEditor::showMode(bool board)
{
    showingBoard = board;
    juce::Component* playlistComponents[] = {
        &list, &addButton, &importButton, &exportButton, &removeButton,
        &upButton, &downButton, &clearButton, &prevButton, &playButton,
        &pauseButton, &stopButton, &nextButton, &shuffleButton, &repeatBox,
        &gainSlider, &progressSlider, &nowPlaying, &timeLabel, &statusLabel,
        &gainLabel, &playlistStats, &repeatStatus
    };
    for (auto* c : playlistComponents) c->setVisible(!board);
    juce::Component* boardComponents[] = {
        &bankBox, &bankName, &padViewBox, &newBank, &deleteBank,
        &prevPage, &nextPage, &stopAllButton, &fadeAllButton,
        &loadPadButton, &clearPadButton, &stopPadButton, &fadePadButton,
        &loopPad, &padGain, &padFade, &bankStatus, &padDetails,
        &bankFileButton, &folderImportButton, &duckEnabledButton,
        &duckDepthSlider, &duckAttackSlider, &duckReleaseSlider
    };
    for (auto* c : boardComponents) c->setVisible(board);
    for (auto& button : padButtons) button.setVisible(board);
    setActionButtonStyle(playlistTab, !board);
    setActionButtonStyle(soundboardTab, board);
    resized(); repaint();
}

void LautFunkPlaylistEditor::paint(juce::Graphics& g)
{
    g.fillAll(bg);
    const int w = getWidth(), h = getHeight();
    g.setColour(teal);
    g.setFont(juce::FontOptions(12.0f).withStyle("Bold"));
    g.drawText("LAUTFUNK AUDIO LAB", 22, 14, w - 44, 20, juce::Justification::centredLeft);
    g.setColour(white);
    g.setFont(juce::FontOptions(26.0f).withStyle("Bold"));
    g.drawText("PLAYLIST PLAYER & SOUNDBOARD", 22, 36, w - 290, 35, juce::Justification::centredLeft);
    g.setColour(muted);
    g.setFont(juce::FontOptions(12.0f));
    g.drawText("VST3  |  2.0 DEV PREVIEW", w - 280, 37, 256, 30, juce::Justification::centredRight);

    g.setColour(panel);
    if (!showingBoard)
    {
        g.fillRoundedRectangle(16.f, 184.f, (float)(w - 32), (float)(h - 438), 10.f);
        g.fillRoundedRectangle(16.f, (float)(h - 242), (float)(w - 32), 105.f, 10.f);
        g.setColour(panelBright);
        g.fillRoundedRectangle(30.f, 222.f, (float)(w - 60), 3.f, 1.5f);
        g.setColour(teal);
        g.fillRoundedRectangle(30.f, 222.f, (float)((w - 60) * playlistProgress), 3.f, 1.5f);
        g.setColour(muted);
        g.setFont(juce::FontOptions(11.0f).withStyle("Bold"));
        g.drawText("AKTUELLER TITEL", 30, h - 234, w - 60, 18, juce::Justification::centredLeft);
    }
    else
    {
        g.fillRoundedRectangle(16.f, 188.f, (float)(w - 32), (float)(h - 416), 10.f);
        g.fillRoundedRectangle(16.f, (float)(h - 216), (float)(w - 32), 198.f, 10.f);
    }
    if (draggedOver)
    {
        g.setColour(teal.withAlpha(0.12f));
        g.fillRoundedRectangle(getLocalBounds().toFloat().reduced(8), 8);
        g.setColour(teal);
        g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(8), 8, 2);
    }
}

void LautFunkPlaylistEditor::resized()
{
    const int w = getWidth(), h = getHeight();
    playlistTab.setBounds(22, 87, 170, 37);
    soundboardTab.setBounds(202, 87, 184, 37);
    if (!showingBoard)
    {
        constexpr int gap = 8;
        const int weights[] = {124,118,146,114,66,72,90};
        constexpr int totalWeight = 730;
        const int usable = w - 44 - 6 * gap;
        juce::TextButton* buttons[] = { &addButton, &importButton, &exportButton,
                                        &removeButton, &upButton, &downButton, &clearButton };
        int x = 22;
        for (int i = 0; i < 7; ++i)
        {
            const int size = i == 6 ? (w - 22 - x) : (usable * weights[i] / totalWeight);
            buttons[i]->setBounds(x, 140, size, 36);
            x += size + gap;
        }
        playlistStats.setBounds(30, 191, w - 285, 32);
        repeatStatus.setBounds(w - 258, 191, 220, 32);
        list.setBounds(24, 228, w - 48, h - 491);
        nowPlaying.setBounds(30, h - 211, w - 306, 28);
        timeLabel.setBounds(w - 266, h - 211, 232, 28);
        progressSlider.setBounds(30, h - 175, w - 60, 28);
        const int btnW = 112, btnGap = 10;
        x = (w - (5 * btnW + 4 * btnGap)) / 2;
        for (auto* b : { &prevButton, &playButton, &pauseButton, &stopButton, &nextButton })
        { b->setBounds(x, h - 131, btnW, 42); x += btnW + btnGap; }
        statusLabel.setBounds(28, h - 85, w - 56, 20);
        repeatBox.setBounds(26, h - 58, 196, 34);
        shuffleButton.setBounds(235, h - 55, 134, 29);
        gainLabel.setBounds(w - 384, h - 53, 98, 24);
        gainSlider.setBounds(w - 283, h - 61, 255, 39);
        return;
    }
    bankBox.setBounds(22, 138, 220, 35);
    bankName.setBounds(252, 138, juce::jmax(170, w - 780), 35);
    newBank.setBounds(w - 490, 138, 104, 35);
    deleteBank.setBounds(w - 377, 138, 128, 35);
    padViewBox.setBounds(w - 240, 138, 218, 35);

    const int count = padCount;
    const int cols = count == 12 ? 3 : 4;
    const int rows = count / cols;
    const int left = 29, top = 198, gap = 9;
    const int width = (w - 58 - (cols - 1) * gap) / cols;
    const int height = (h - 433 - (rows - 1) * gap) / rows;
    for (int i = 0; i < 24; ++i)
    {
        const bool visible = i < count;
        auto& b = padButtons[(size_t) i];
        b.setVisible(visible);
        if (visible)
            b.setBounds(left + (i % cols) * (width + gap),
                        top + (i / cols) * (height + gap), width, height);
    }

    prevPage.setBounds(30, h - 220, 112, 32);
    nextPage.setBounds(151, h - 220, 112, 32);
    bankStatus.setBounds(275, h - 220, w - 570, 32);
    fadeAllButton.setBounds(w - 264, h - 220, 111, 33);
    stopAllButton.setBounds(w - 143, h - 220, 113, 33);

    padDetails.setBounds(30, h - 177, w - 405, 23);
    folderImportButton.setBounds(w - 367, h - 181, 174, 30);
    bankFileButton.setBounds(w - 185, h - 181, 155, 30);
    loadPadButton.setBounds(30, h - 144, 144, 34);
    clearPadButton.setBounds(184, h - 144, 122, 34);
    stopPadButton.setBounds(316, h - 144, 110, 34);
    fadePadButton.setBounds(436, h - 144, 110, 34);
    loopPad.setBounds(558, h - 144, 100, 34);
    padGain.setBounds(30, h - 101, (w - 75) / 2, 36);
    padFade.setBounds(45 + (w - 75) / 2, h - 101, (w - 75) / 2, 36);
    duckEnabledButton.setBounds(26, h - 58, 142, 31);
    const int leftDuck = 168;
    const int duckW = (w - leftDuck - 40) / 3;
    duckDepthSlider.setBounds(leftDuck, h - 60, duckW, 36);
    duckAttackSlider.setBounds(leftDuck + duckW + 5, h - 60, duckW, 36);
    duckReleaseSlider.setBounds(leftDuck + 2 * (duckW + 5), h - 60, duckW, 36);
}

int LautFunkPlaylistEditor::getNumRows() { return snapshot.size(); }

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
    const double sec = juce::isPositiveAndBelow(row, snapshotDurations.size()) ? snapshotDurations[row] : -1.0;
    g.setFont(juce::FontOptions(12.0f));
    g.drawText(sec >= 0.0 ? secondsToText(sec) : (sec < -1.5 ? "--:--" : "…"),
               width - 95, 0, 85, height, juce::Justification::centredRight);
}

void LautFunkPlaylistEditor::listBoxItemDoubleClicked(int row, const juce::MouseEvent&)
{ processor.startTrack(row); }

void LautFunkPlaylistEditor::moveSelection(int offset)
{
    const int row = list.getSelectedRow(), destination = row + offset;
    if (!juce::isPositiveAndBelow(destination, processor.getTrackFiles().size())) return;
    processor.moveTrack(row, destination);
    updateControls(); list.selectRow(destination);
}

juce::String LautFunkPlaylistEditor::secondsToText(double sec)
{
    const int value = juce::jmax(0, (int) sec);
    if (value >= 3600)
        return juce::String::formatted("%d:%02d:%02d", value / 3600, (value % 3600) / 60, value % 60);
    return juce::String::formatted("%02d:%02d", value / 60, value % 60);
}

void LautFunkPlaylistEditor::timerCallback()
{
    updateControls();
    if (showingBoard) updateBoard();
}

void LautFunkPlaylistEditor::updateControls()
{
    duckEnabledButton.setToggleState(processor.duckEnabledParam->get(), juce::dontSendNotification);
    if (!duckDepthSlider.isMouseButtonDown())
        duckDepthSlider.setValue(processor.duckDepthParam->get(), juce::dontSendNotification);
    if (!duckAttackSlider.isMouseButtonDown())
        duckAttackSlider.setValue(processor.duckAttackParam->get(), juce::dontSendNotification);
    if (!duckReleaseSlider.isMouseButtonDown())
        duckReleaseSlider.setValue(processor.duckReleaseParam->get(), juce::dontSendNotification);
    const auto rev = processor.getRevision();
    const auto index = processor.getCurrentIndex();
    if (rev != lastRevision)
    {
        const bool changedTrack = index != lastIndex;
        lastIndex = index; lastRevision = rev;
        snapshot = processor.getTrackFiles();
        snapshotDurations = processor.getTrackDurations();
        list.updateContent(); list.repaint();
        if (changedTrack && index >= 0) list.scrollToEnsureRowIsOnscreen(index);
        repeatBox.setSelectedId((int) processor.getRepeatMode() + 1, juce::dontSendNotification);
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
        progressSlider.setValue(duration > 0 ? processor.getPosition() / duration : 0.0, juce::dontSendNotification);
    if (!gainSlider.isMouseButtonDown())
        gainSlider.setValue(processor.volumeParam->get(), juce::dontSendNotification);
    statusLabel.setText(processor.getStatus(), juce::dontSendNotification);

    const auto stats = processor.getPlaylistStats();
    const auto remaining = processor.getRemainingTime();
    playlistProgress = remaining.progress;
    if (!showingBoard) repaint(25, 219, getWidth() - 50, 9);
    juce::String line = juce::String(stats.trackCount) + " TITEL  |  GESAMT " + secondsToText(stats.knownSeconds)
        + "  |  REST " + (remaining.approximate ? "ca. " : "") + secondsToText(remaining.seconds);
    if (stats.pendingDurations > 0) line += "  (" + juce::String(stats.pendingDurations) + " werden gelesen)";
    if (stats.unavailableDurations > 0) line += "  (" + juce::String(stats.unavailableDurations) + " ohne Dauer)";
    playlistStats.setText(line, juce::dontSendNotification);
    const auto repeat = processor.getRepeatMode();
    const bool endless = repeat == LautFunkPlaylistProcessor::RepeatMode::all;
    repeatStatus.setText(endless ? "BIS NÄCHSTER DURCHLAUF" :
                         repeat == LautFunkPlaylistProcessor::RepeatMode::one ? "1 TITEL WIEDERHOLEN" :
                         "BIS PLAYLIST-ENDE", juce::dontSendNotification);
    repeatStatus.setColour(juce::Label::textColourId, endless ? teal : muted);
}

void LautFunkPlaylistEditor::chooseFiles()
{
    chooser = std::make_unique<juce::FileChooser>("MP3/WAV zur Playlist hinzufügen", juce::File{}, "*.mp3;*.wav");
    const juce::Component::SafePointer<LautFunkPlaylistEditor> safe(this);
    chooser->launchAsync(juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectMultipleItems
        | juce::FileBrowserComponent::canSelectFiles,
        [safe](const juce::FileChooser& c) { if (safe != nullptr) safe->processor.appendFiles(c.getResults()); });
}

void LautFunkPlaylistEditor::choosePlaylist(bool importing)
{
    chooser = std::make_unique<juce::FileChooser>(
        importing ? "Playlist öffnen" : "Playlist speichern",
        juce::File::getSpecialLocation(juce::File::userDocumentsDirectory), "*.m3u8");
    const juce::Component::SafePointer<LautFunkPlaylistEditor> safe(this);
    chooser->launchAsync(importing
        ? juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles
        : juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::warnAboutOverwriting,
        [safe, importing](const juce::FileChooser& c) {
            if (safe == nullptr) return;
            auto f = c.getResult();
            if (f == juce::File{}) return;
            if (!importing && !f.hasFileExtension("m3u8")) f = f.withFileExtension("m3u8");
            if (importing) safe->processor.importM3U8(f);
            else safe->processor.exportM3U8(f);
        });
}

int LautFunkPlaylistEditor::visiblePadToSlot(int index) const
{ return padCount == 12 ? padPage * 12 + index : index; }

void LautFunkPlaylistEditor::selectPad(int slot)
{
    selectedPad = slot;
    updatePadSelection();
}

void LautFunkPlaylistEditor::updateBoard()
{
    const int externalBank = processor.getMidiBank();
    if (externalBank > 0 && externalBank != currentBankId)
    {
        currentBankId = externalBank;
        selectedPad = -1;
        updatePadSelection();
    }
    const auto banks = processor.getSoundboard().getBanks();
    if (banks.empty()) return;
    bool found = false;
    juce::String signature;
    for (const auto& b : banks)
    {
        signature += juce::String(b.id) + ":" + b.name + ";";
        if (b.id == currentBankId) found = true;
    }
    if (!found) { currentBankId = banks.front().id; selectedPad = -1; }
    if (signature != lastBankSignature || currentBankId != lastDisplayedBankId)
    {
        lastDisplayedBankId = currentBankId;
        lastBankSignature = signature;
        bankBox.clear(juce::dontSendNotification);
        for (const auto& b : banks) bankBox.addItem(b.name, b.id);
        bankBox.setSelectedId(currentBankId, juce::dontSendNotification);
        for (const auto& b : banks)
            if (b.id == currentBankId)
                bankName.setText(b.name, false);
    }
    const SoundboardEngine::Bank* selected = nullptr;
    for (const auto& b : banks) if (b.id == currentBankId) selected = &b;
    if (selected == nullptr) return;
    const int visible = padCount;
    for (int i = 0; i < visible; ++i)
    {
        const int slot = visiblePadToSlot(i);
        auto& button = padButtons[(size_t) i];
        const auto& pad = selected->pads[(size_t) slot];
        const bool active = processor.getSoundboard().isPadActive(currentBankId, slot);
        juce::String title = pad.name.isNotEmpty() ? pad.name : pad.file.getFileNameWithoutExtension();
        if (title.isEmpty()) title = "[Leer]";
        title = juce::String(slot + 1).paddedLeft('0', 2) + "  " + title;
        if (active) title += "   ▶";
        button.setButtonText(title);
        button.setColour(juce::TextButton::buttonColourId,
                         active ? juce::Colour(0xff235751) : slot == selectedPad ? juce::Colour(0xff294858) : panelBright);
        button.setColour(juce::TextButton::textColourOffId, active ? teal : white);
        button.setTooltip(pad.file.getFullPathName().isNotEmpty() ? pad.file.getFullPathName() : "Rechtsklick zum Laden");
    }
    bankStatus.setText("Bank " + juce::String(currentBankId) + " · Seite "
        + juce::String(padCount == 24 ? 1 : padPage + 1) + " · "
        + juce::String(processor.getSoundboard().activeCount()) + " aktiv",
        juce::dontSendNotification);
    prevPage.setEnabled(padCount == 12 && padPage != 0);
    nextPage.setEnabled(padCount == 12 && padPage != 1);
    deleteBank.setEnabled(banks.size() > 1);
}

void LautFunkPlaylistEditor::updatePadSelection()
{
    const auto banks = processor.getSoundboard().getBanks();
    for (const auto& b : banks)
        if (b.id == currentBankId && juce::isPositiveAndBelow(selectedPad, SoundboardEngine::padsPerBank))
        {
            const auto& p = b.pads[(size_t) selectedPad];
            const auto title = p.name.isNotEmpty() ? p.name : p.file.getFileName();
            padDetails.setText("SLOT " + juce::String(selectedPad + 1) + "  |  "
                + (title.isEmpty() ? "Kein Sample geladen" : title), juce::dontSendNotification);
            padGain.setValue(p.gainDb, juce::dontSendNotification);
            padFade.setValue(p.fadeSeconds, juce::dontSendNotification);
            loopPad.setToggleState(p.loop, juce::dontSendNotification);
            return;
        }
    padDetails.setText("Slot anklicken, um Sample-Einstellungen zu bearbeiten", juce::dontSendNotification);
}

void LautFunkPlaylistEditor::updateSelectedPad(std::function<void(SoundboardEngine::Pad&)> change)
{
    if (selectedPad < 0) return;
    const auto banks = processor.getSoundboard().getBanks();
    for (const auto& b : banks)
        if (b.id == currentBankId)
        {
            auto pad = b.pads[(size_t) selectedPad];
            change(pad);
            processor.getSoundboard().setPad(currentBankId, selectedPad, pad);
            return;
        }
}

void LautFunkPlaylistEditor::applyBankName()
{
    if (lastDisplayedBankId == currentBankId && bankName.getText().trim().isNotEmpty()
        && processor.getSoundboard().renameBank(currentBankId, bankName.getText()))
    {
        lastBankSignature.clear();
        updateBoard();
    }
}

void LautFunkPlaylistEditor::openPadMenu(int slot)
{
    selectPad(slot);
    juce::PopupMenu menu;
    menu.addItem(1, "Sample laden ...");
    menu.addItem(2, "Sample stoppen");
    menu.addItem(3, "Sample ausblenden (Fade-Out)");
    menu.addSeparator();
    menu.addItem(4, "Slot leeren");
    const juce::Component::SafePointer<LautFunkPlaylistEditor> safe(this);
    menu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(this),
        [safe, slot](int choice) {
            if (safe == nullptr) return;
            if (choice == 1) safe->assignSample(slot);
            else if (choice == 2) safe->processor.getSoundboard().stopPad(safe->currentBankId, slot, false);
            else if (choice == 3) safe->processor.getSoundboard().stopPad(safe->currentBankId, slot, true);
            else if (choice == 4) { safe->processor.getSoundboard().clearPad(safe->currentBankId, slot); safe->updateBoard(); }
        });
}

void LautFunkPlaylistEditor::chooseBankFile(bool importing)
{
    chooser = std::make_unique<juce::FileChooser>(
        importing ? "LautFunk Soundbank laden" : "LautFunk Soundbank speichern",
        juce::File::getSpecialLocation(juce::File::userDocumentsDirectory), "*.lfsb");
    const juce::Component::SafePointer<LautFunkPlaylistEditor> safe(this);
    const int bankId = currentBankId;
    chooser->launchAsync(importing
        ? (juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles)
        : (juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::warnAboutOverwriting),
        [safe, importing, bankId](const juce::FileChooser& dialog) {
            if (safe == nullptr) return;
            auto file = dialog.getResult();
            if (file == juce::File{}) return;
            if (importing)
            {
                const auto xml = juce::XmlDocument::parse(file);
                if (!xml) return;
                const auto state = juce::ValueTree::fromXml(*xml);
                const int newId = safe->processor.getSoundboard().importBank(state);
                if (newId > 0)
                {
                    safe->currentBankId = newId;
                    safe->processor.setMidiBank(newId);
                    safe->selectedPad = -1;
                    safe->lastBankSignature.clear();
                    safe->updateBoard();
                }
            }
            else
            {
                if (!file.hasFileExtension("lfsb")) file = file.withFileExtension("lfsb");
                const auto state = safe->processor.getSoundboard().exportBank(bankId);
                if (!state.isValid()) return;
                if (const auto xml = state.createXml())
                    file.replaceWithText(xml->toString());
            }
        });
}

void LautFunkPlaylistEditor::chooseSampleFolder()
{
    chooser = std::make_unique<juce::FileChooser>(
        "Ordner mit Soundboard-Samples auswählen",
        juce::File::getSpecialLocation(juce::File::userMusicDirectory));
    const juce::Component::SafePointer<LautFunkPlaylistEditor> safe(this);
    chooser->launchAsync(juce::FileBrowserComponent::openMode |
                         juce::FileBrowserComponent::canSelectDirectories,
        [safe](const juce::FileChooser& picker) {
            if (safe == nullptr) return;
            const auto folder = picker.getResult();
            if (folder.isDirectory()) safe->importSamplesFromFolder(folder);
        });
}

void LautFunkPlaylistEditor::importSamplesFromFolder(const juce::File& folder)
{
    juce::Array<juce::File> files;
    folder.findChildFiles(files, juce::File::findFiles, false, "*.wav;*.mp3");
    if (files.isEmpty())
    {
        juce::AlertWindow::showMessageBoxAsync(
            juce::MessageBoxIconType::InfoIcon, "Soundboard-Import",
            "In diesem Ordner wurden keine WAV- oder MP3-Dateien gefunden.");
        return;
    }
    std::sort(files.begin(), files.end(),
        [](const juce::File& a, const juce::File& b) {
            return a.getFileName().compareIgnoreCase(b.getFileName()) < 0;
        });

    auto& engine = processor.getSoundboard();
    int bankId = currentBankId;
    int filled = 0;
    int created = 0;
    const auto initialBanks = engine.getBanks();
    juce::String baseName = folder.getFileName();
    if (baseName.isEmpty()) baseName = "Samples";

    int fileIndex = 0;
    while (fileIndex < files.size())
    {
        const auto banks = engine.getBanks();
        const SoundboardEngine::Bank* bank = nullptr;
        for (const auto& b : banks)
            if (b.id == bankId) { bank = &b; break; }

        // A completely occupied current bank is extended by a fresh bank.
        // Existing slot assignments are never overwritten.
        bool hasSpace = false;
        if (bank != nullptr)
            for (const auto& pad : bank->pads)
                if (pad.file.getFullPathName().isEmpty()) { hasSpace = true; break; }

        if (!hasSpace)
        {
            ++created;
            bankId = engine.addBank(baseName + " " + juce::String(created + 1));
            continue;
        }
        for (int slot = 0; slot < SoundboardEngine::padsPerBank && fileIndex < files.size(); ++slot)
        {
            if (!bank->pads[static_cast<size_t>(slot)].file.getFullPathName().isEmpty())
                continue;
            SoundboardEngine::Pad pad;
            pad.file = files.getReference(fileIndex++);
            pad.name = pad.file.getFileNameWithoutExtension();
            if (engine.setPad(bankId, slot, pad))
                ++filled;
        }
        if (fileIndex < files.size())
        {
            ++created;
            bankId = engine.addBank(baseName + " " + juce::String(created + 1));
        }
    }
    lastBankSignature.clear();
    updateBoard();
    juce::AlertWindow::showMessageBoxAsync(
        juce::MessageBoxIconType::InfoIcon, "Soundboard-Import",
        juce::String(filled) + " Samples importiert. " +
        juce::String(created) + " zusätzliche Soundbank(en) angelegt.");
}

bool LautFunkPlaylistEditor::keyPressed(const juce::KeyPress& key)
{
    if (!showingBoard || bankName.hasKeyboardFocus(true) ||
        key.getModifiers().isCommandDown() ||
        key.getModifiers().isAltDown())
        return false;
    const int code = key.getKeyCode();
    if (code == juce::KeyPress::pageUpKey)
    { processor.selectMidiBankRelative(-1); updateBoard(); return true; }
    if (code == juce::KeyPress::pageDownKey)
    { processor.selectMidiBankRelative(1); updateBoard(); return true; }
    if (code == juce::KeyPress::escapeKey)
    { processor.getSoundboard().stopAll(false); return true; }
    const int mapped = juce::String("1234567890-=").indexOfChar(code);
    if (mapped >= 0)
    {
        const int slot = padCount == 12 ? padPage * 12 + mapped : mapped;
        processor.getSoundboard().triggerPad(currentBankId, slot);
        return true;
    }
    return false;
}

void LautFunkPlaylistEditor::assignSample(int slot)
{
    chooser = std::make_unique<juce::FileChooser>("Sample in Soundboard-Slot laden", juce::File{}, "*.wav;*.mp3");
    const juce::Component::SafePointer<LautFunkPlaylistEditor> safe(this);
    const int bankId = currentBankId;
    chooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
        [safe, bankId, slot](const juce::FileChooser& c) {
            if (safe == nullptr) return;
            const auto f = c.getResult();
            if (!f.existsAsFile() || !f.hasFileExtension("wav;mp3")) return;
            SoundboardEngine::Pad pad;
            pad.file = f;
            pad.name = f.getFileNameWithoutExtension();
            safe->processor.getSoundboard().setPad(bankId, slot, pad);
            safe->selectPad(slot);
            safe->updateBoard();
        });
}

bool LautFunkPlaylistEditor::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (const auto& f : files)
        if (juce::File(f).hasFileExtension("wav;mp3;m3u8")) return true;
    return false;
}

void LautFunkPlaylistEditor::filesDropped(const juce::StringArray& paths, int x, int y)
{
    if (showingBoard)
    {
        int index = -1;
        for (int i = 0; i < padCount; ++i)
            if (padButtons[(size_t)i].getBounds().contains(x, y)) { index = visiblePadToSlot(i); break; }
        if (index < 0) index = selectedPad;
        if (index >= 0)
        {
            int slot = index;
            for (const auto& name : paths)
            {
                const juce::File f(name);
                if (!f.existsAsFile() || !f.hasFileExtension("wav;mp3") || slot >= 24) continue;
                SoundboardEngine::Pad p;
                p.file = f; p.name = f.getFileNameWithoutExtension();
                processor.getSoundboard().setPad(currentBankId, slot++, p);
            }
            selectPad(index); updateBoard();
        }
    }
    else
    {
        juce::Array<juce::File> files;
        for (const auto& path : paths)
        {
            juce::File f(path);
            if (f.hasFileExtension("m3u8")) processor.importM3U8(f);
            else files.add(f);
        }
        if (!files.isEmpty()) processor.appendFiles(files);
    }
    draggedOver = false; repaint();
}
