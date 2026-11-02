#pragma once
#include <JuceHeader.h>
#include <atomic>

class LautFunkPlaylistProcessor final : public juce::AudioProcessor,
                                          private juce::Timer,
                                          private juce::AsyncUpdater
{
public:
    enum class RepeatMode : int { off = 0, all = 1, one = 2 };

    LautFunkPlaylistProcessor();
    ~LautFunkPlaylistProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    bool isBusesLayoutSupported(const BusesLayout&) const override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}
    void getStateInformation(juce::MemoryBlock&) override;
    void setStateInformation(const void*, int) override;

    void appendFiles(const juce::Array<juce::File>&);
    bool importM3U8(const juce::File&);
    bool exportM3U8(const juce::File&) const;
    void removeTrack(int index);
    void moveTrack(int source, int destination);
    void clearPlaylist();
    void startTrack(int index);
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    void seekSeconds(double seconds);
    void setRepeatMode(RepeatMode);
    void setShuffle(bool);

    struct PlaylistStats
    {
        int trackCount = 0;
        int pendingDurations = 0;
        int unavailableDurations = 0;
        double knownSeconds = 0.0;
    };

    juce::Array<juce::File> getTrackFiles() const;
    juce::Array<double> getTrackDurations() const;
    PlaylistStats getPlaylistStats() const;
    int getCurrentIndex() const;
    int64_t getRevision() const { return revision.load(); }
    bool isPlaying() const { return playingWanted.load(); }
    RepeatMode getRepeatMode() const { const juce::ScopedLock lock(playlistLock); return repeatMode; }
    bool getShuffle() const { const juce::ScopedLock lock(playlistLock); return shuffle; }
    double getPosition() const { return transport.getCurrentPosition(); }
    double getLength() const { return transport.getLengthInSeconds(); }
    juce::String getStatus() const { return status; }

    juce::AudioParameterFloat* volumeParam = nullptr;

private:
    void timerCallback() override;
    void handleAsyncUpdate() override;
    bool loadIndex(int index, bool autoStart);
    void advanceAtEnd();

    mutable juce::CriticalSection playlistLock;
    juce::Array<juce::File> tracks;
    juce::Array<double> trackDurations; // seconds; -1 = pending, -2 = unavailable
    int currentIndex = -1;
    RepeatMode repeatMode = RepeatMode::all;
    bool shuffle = false;
    juce::Array<int> playedShuffleIndices; // Message-thread-only shuffle cycle.
    juce::String status = "Bereit";
    std::atomic<int64_t> revision { 0 };
    std::atomic<bool> playingWanted { false };

    juce::AudioFormatManager formats;
    juce::TimeSliceThread readerThread { "LautFunk Playlist Streaming" };
    juce::AudioTransportSource transport;
    std::unique_ptr<juce::AudioFormatReaderSource> fileSource;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> gain;

    juce::CriticalSection pendingLock;
    juce::ValueTree pendingState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LautFunkPlaylistProcessor)
};
