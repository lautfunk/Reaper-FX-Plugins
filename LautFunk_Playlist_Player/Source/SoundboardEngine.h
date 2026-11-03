#pragma once
#include <JuceHeader.h>
#include <array>
#include <atomic>
#include <deque>
#include <memory>
#include <vector>

// Soundboard audio and bank state. All bank edits and triggers occur on JUCE's
// message thread. The audio callback only reads an immutable active-voice list.
class SoundboardEngine final
{
public:
    static constexpr int padsPerBank = 24;
    static constexpr int maxSimultaneousVoices = 24;

    struct Pad
    {
        juce::File file;
        juce::String name;
        float gainDb = -6.0f;
        bool loop = false;
        float fadeSeconds = 0.7f;
    };
    struct Bank
    {
        int id = 0;
        juce::String name;
        std::array<Pad, padsPerBank> pads;
    };

    explicit SoundboardEngine(juce::AudioFormatManager&, juce::TimeSliceThread&);
    ~SoundboardEngine();

    void prepare(double sampleRate, int maxBlockSize);
    void release();
    void mixInto(juce::AudioBuffer<float>& output, juce::AudioBuffer<float>& scratch);
    void timerTick();

    std::vector<Bank> getBanks() const;
    int addBank(const juce::String& preferredName);
    bool renameBank(int bankId, const juce::String& name);
    bool removeBank(int bankId);
    bool setPad(int bankId, int padIndex, const Pad& pad);
    bool clearPad(int bankId, int padIndex);
    bool triggerPad(int bankId, int padIndex);
    void stopPad(int bankId, int padIndex, bool fade);
    void stopAll(bool fade);
    bool isPadActive(int bankId, int padIndex) const;
    int activeCount() const;
    juce::String getLastError() const { return error; }

    juce::ValueTree saveState() const;
    void loadState(const juce::ValueTree&);

private:
    struct Voice
    {
        int bankId = 0;
        int padIndex = 0;
        juce::AudioTransportSource transport;
        std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
        juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> gain;
        std::atomic<bool> fadeOutRequested { false };
        std::atomic<bool> immediateStop { false };
        std::atomic<bool> finished { false };
        float fadeSeconds = 0.7f;
        bool loop = false;

        Voice(int b, int s) : bankId(b), padIndex(s) {}
        ~Voice();
    };
    using VoiceList = std::vector<std::shared_ptr<Voice>>;

    Bank* findBank(int id);
    const Bank* findBank(int id) const;
    void publishVoices(std::shared_ptr<VoiceList>);

    juce::AudioFormatManager& formats;
    juce::TimeSliceThread& readerThread;
    mutable juce::CriticalSection banksLock;
    std::vector<Bank> banks;
    int nextBankId = 1;
    std::shared_ptr<VoiceList> voices { std::make_shared<VoiceList>() };
    // Keep old snapshots alive briefly; released on the message thread,
    // rather than risking a voice/reader destructor in the audio callback.
    struct RetiredSnapshot { double timestampMs; std::shared_ptr<VoiceList> list; };
    std::deque<RetiredSnapshot> retiredSnapshots;
    std::atomic<double> hostSampleRate { 48000.0 };
    std::atomic<int> hostBlockSize { 512 };
    juce::String error;
};
