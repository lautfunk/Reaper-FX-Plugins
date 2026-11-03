#pragma once

#include <JuceHeader.h>
#include <memory>

class LautFunkPlaylistProcessor;

/**
 * Optional localhost-only OSC receiver for Stream Deck / Bitfocus Companion.
 *
 * Disabled by default. Messages are dispatched on the JUCE message thread,
 * never on the audio callback. Each VST3 instance owns its own UDP socket.
 * Only one instance can use a particular port at once.
 */
class LautFunkOscControl final
    : private juce::OSCReceiver::Listener<juce::OSCReceiver::MessageLoopCallback>
{
public:
    explicit LautFunkOscControl(LautFunkPlaylistProcessor& owner);
    ~LautFunkOscControl() override;

    bool setEnabled(bool enabled, int port);
    bool isEnabled() const noexcept { return enabled; }
    int getPort() const noexcept { return port; }
    juce::String getStatus() const { return status; }

private:
    void oscMessageReceived(const juce::OSCMessage& message) override;
    void stop();

    LautFunkPlaylistProcessor& processor;
    std::unique_ptr<juce::DatagramSocket> socket;
    juce::OSCReceiver receiver { "LautFunk OSC localhost" };
    bool enabled = false;
    int port = 9001;
    juce::String status { "OSC AUS" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LautFunkOscControl)
};
