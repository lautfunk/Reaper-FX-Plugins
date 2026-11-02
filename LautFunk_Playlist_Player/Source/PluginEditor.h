#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

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
    void filesDropped(const juce::StringArray&, int x, int y) override;

private:
    int getNumRows() override;
    void paintListBoxItem(int row, juce::Graphics&, int width, int height, bool selected) override;
    void listBoxItemDoubleClicked(int row, const juce::MouseEvent&) override;
    void timerCallback() override;

    void chooseFiles();
    void choosePlaylist(bool import);
    void setActionButtonStyle(juce::TextButton&, bool primary = false);
    void updateControls();
    void moveSelection(int offset);
    static juce::String secondsToText(double);

    LautFunkPlaylistProcessor& processor;
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
    std::unique_ptr<juce::FileChooser> chooser;
    juce::Array<juce::File> snapshot;
    juce::Array<double> snapshotDurations;
    int64_t lastRevision = -1;
    int lastIndex = -1;
    bool draggedOver = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LautFunkPlaylistEditor)
};
