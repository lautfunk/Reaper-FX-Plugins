#include "OscControl.h"
#include "PluginProcessor.h"

#include <cmath>

LautFunkOscControl::LautFunkOscControl(LautFunkPlaylistProcessor& owner)
    : processor(owner)
{
    // File loading and sample triggers are not realtime-safe. The message
    // loop callback is required, rather than RealtimeCallback.
    receiver.addListener(this);
}

LautFunkOscControl::~LautFunkOscControl()
{
    stop();
    receiver.removeListener(this);
}

void LautFunkOscControl::stop()
{
    if (enabled)
        receiver.disconnect();
    socket.reset();
    enabled = false;
}

bool LautFunkOscControl::setEnabled(bool shouldEnable, int requestedPort)
{
    if (requestedPort < 1024 || requestedPort > 65535)
    {
        status = "OSC: Port muss zwischen 1024 und 65535 liegen";
        return false;
    }

    if (!shouldEnable)
    {
        stop();
        port = requestedPort;
        status = "OSC AUS";
        return true;
    }

    if (enabled && requestedPort == port)
        return true;

    stop();
    port = requestedPort;

    // Explicitly bind to IPv4 loopback. This does not expose the soundboard
    // to LAN or Internet devices; remote control needs a separate opt-in
    // transport in a future version.
    socket = std::make_unique<juce::DatagramSocket>(false);
    if (!socket->bindToPort(port, "127.0.0.1"))
    {
        status = "OSC: Port " + juce::String(port) + " belegt / nicht verfügbar";
        return false;
    }

    if (!receiver.connectToSocket(*socket))
    {
        socket.reset();
        status = "OSC: Empfang konnte nicht gestartet werden";
        return false;
    }

    enabled = true;
    status = "OSC AN: 127.0.0.1:" + juce::String(port);
    return true;
}

void LautFunkOscControl::oscMessageReceived(const juce::OSCMessage& message)
{
    if (!enabled)
        return;

    const juce::String address = message.getAddressPattern().toString();
    auto intArg = [&message](int fallback = -1) -> int {
        if (message.size() < 1)
            return fallback;
        const auto& argument = message[0];
        if (argument.isInt32())
            return argument.getInt32();
        if (argument.isFloat32())
        {
            const float value = argument.getFloat32();
            if (std::isfinite(value))
                return static_cast<int>(value);
        }
        return fallback;
    };
    auto floatArg = [&message](float fallback) -> float {
        if (message.size() < 1)
            return fallback;
        const auto& argument = message[0];
        if (argument.isFloat32())
            return argument.getFloat32();
        if (argument.isInt32())
            return static_cast<float>(argument.getInt32());
        return fallback;
    };

    auto& board = processor.getSoundboard();
    const int activeBank = processor.getMidiBank();

    if (address == "/lautfunk/pad/trigger" ||
        address == "/lautfunk/pad/stop" ||
        address == "/lautfunk/pad/fade")
    {
        // OSC uses 1-based slot numbers, 1..24.
        const int slot = intArg() - 1;
        if (!juce::isPositiveAndBelow(slot, SoundboardEngine::padsPerBank))
            return;

        if (address == "/lautfunk/pad/trigger")
            board.triggerPad(activeBank, slot);
        else if (address == "/lautfunk/pad/stop")
            board.stopPad(activeBank, slot, false);
        else
            board.stopPad(activeBank, slot, true);
        return;
    }

    if (address == "/lautfunk/bank/next")
        processor.selectMidiBankRelative(1);
    else if (address == "/lautfunk/bank/previous")
        processor.selectMidiBankRelative(-1);
    else if (address == "/lautfunk/bank/select")
    {
        // 1-based bank ordinal, NOT internal bank ID, so a controller may
        // use sequential button numbers even after deleting banks.
        const int ordinal = intArg();
        const auto banks = board.getBanks();
        if (ordinal >= 1 && ordinal <= static_cast<int>(banks.size()))
            processor.setMidiBank(banks[static_cast<size_t>(ordinal - 1)].id);
    }
    else if (address == "/lautfunk/all/stop")
        board.stopAll(false);
    else if (address == "/lautfunk/all/fade")
        board.stopAll(true);
    else if (address == "/lautfunk/playlist/play")
        processor.play();
    else if (address == "/lautfunk/playlist/pause")
        processor.pause();
    else if (address == "/lautfunk/playlist/toggle")
    {
        if (processor.isPlaying()) processor.pause();
        else processor.play();
    }
    else if (address == "/lautfunk/playlist/stop")
        processor.stop();
    else if (address == "/lautfunk/playlist/next")
        processor.next();
    else if (address == "/lautfunk/playlist/previous")
        processor.previous();
    else if (address == "/lautfunk/duck/enable")
    {
        const int value = intArg();
        if (value == 0 || value == 1)
            processor.duckEnabledParam->setValueNotifyingHost(value != 0 ? 1.0f : 0.0f);
    }
    else if (address == "/lautfunk/duck/depth")
    {
        const float depth = floatArg(-1.0f);
        if (std::isfinite(depth) && depth >= 0.0f && depth <= 30.0f)
        {
            auto* param = processor.duckDepthParam;
            param->setValueNotifyingHost(param->convertTo0to1(depth));
        }
    }
}
