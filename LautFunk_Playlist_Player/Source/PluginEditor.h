#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <array>

class LautFunkPlaylistEditor final : public juce::AudioProcessorEditor,
                                     private juce::ListBoxModel,
                                     private juce::Timer,
                                     public juce::FileDragAndDropTarget
{
public:
    explicit LautFunkPlaylistEditor(LautFunkPlaylistProcessor&);
    ~LautFunkPlaylistEditor() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    bool isInterestedInFileDrag(const juce::StringArray&) override;
    void filesDropped(const juce::StringArray&, int, int) override;

private:
    struct PadButton : juce::TextButton
    {
        std::function<void()> onRightClick;
        void mouseDown(const juce::MouseEvent& e) override
        {
            if (e.mods.isPopupMenu()) { if (onRightClick) onRightClick(); return; }
            juce::TextButton::mouseDown(e);
        }
    };

    int getNumRows() override;
    void paintListBoxItem(int row, juce::Graphics&, int, int, bool) override;
    void listBoxItemDoubleClicked(int row, const juce::MouseEvent&) override;
    void timerCallback() override;
    void setActionButtonStyle(juce::TextButton&, bool primary = false);
    void chooseFiles();
    void choosePlaylist(bool import);
    void updateControls();
    void moveSelection(int offset);
    static juce::String secondsToText(double);

    void showMode(bool soundboard);
    int visiblePadToSlot(int index) const;
    void updateBoard();
    void updatePadSelection();
    void selectPad(int index);
    void openPadMenu(int index);
    void assignSample(int slot);
    void updateSelectedPad(std::function<void(SoundboardEngine::Pad&)> change);
    void applyBankName();

    LautFunkPlaylistProcessor& processor;
    bool showingBoard = false;
    int currentBankId = 1;
    int selectedPad = -1;
    int padCount = 12;
    int padPage = 0;
    juce::String lastBankSignature;
    int lastDisplayedBankId = -1;

    juce::TextButton playlistTab { "PLAYLIST" }, soundboardTab { "SOUNDBOARD" };
    juce::ListBox list { "Playlist", this };
    juce::TextButton addButton { "+ Dateien" }, importButton { "M3U8 laden" },
                     exportButton { "M3U8 speichern" }, removeButton { "Entfernen" },
                     upButton { "Hoch" }, downButton { "Runter" }, clearButton { "Leeren" };
    juce::TextButton prevButton { "|<" }, playButton { "PLAY" },
                     pauseButton { "PAUSE" }, stopButton { "STOP" }, nextButton { ">|" };
    juce::ToggleButton shuffleButton { "Zufall" };
    juce::ComboBox repeatBox;
    juce::Slider gainSlider, progressSlider;
    juce::Label nowPlaying, timeLabel, statusLabel, gainLabel, playlistStats, repeatStatus;

    juce::ComboBox bankBox, padViewBox;
    juce::TextEditor bankName;
    // ASCII-only UTF-8 escapes avoid mojibake on Windows source-code code pages.
    juce::TextButton newBank { "+ Bank" },
                     deleteBank { juce::String::fromUTF8("Bank l\\xC3\\xB6schen") };
    std::array<PadButton, 24> padButtons;
    juce::TextButton prevPage { "< Seite" }, nextPage { "Seite >" },
                     stopAllButton { "STOP ALL" }, fadeAllButton { "FADE ALL" },
                     loadPadButton { "Sample laden" }, clearPadButton { "Slot leeren" },
                     stopPadButton { "Stop Pad" }, fadePadButton { "Fade Pad" };
    juce::ToggleButton loopPad { "Loop" };
    juce::Slider padGain, padFade;
    juce::Label bankStatus, padDetails;

    std::unique_ptr<juce::FileChooser> chooser;
    juce::Array<juce::File> snapshot;
    juce::Array<double> snapshotDurations;
    double playlistProgress = 0.0;
    int64_t lastRevision = -1;
    int lastIndex = -1;
    bool draggedOver = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LautFunkPlaylistEditor)
};
