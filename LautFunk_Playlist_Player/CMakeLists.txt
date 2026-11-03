cmake_minimum_required(VERSION 3.22)
project(LautFunkPlaylistPlayer VERSION 2.3.2 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# You can supply a local JUCE checkout via -DJUCE_DIR=C:/path/to/JUCE.
if(DEFINED JUCE_DIR AND EXISTS "${JUCE_DIR}/CMakeLists.txt")
    add_subdirectory("${JUCE_DIR}" "${CMAKE_BINARY_DIR}/JUCE-build")
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/CMakeLists.txt")
    add_subdirectory(JUCE)
else()
    include(FetchContent)
    FetchContent_Declare(JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 9.0.4
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(JUCE)
endif()

juce_add_plugin(LautFunkPlaylistPlayer
    COMPANY_NAME "LautFunk"
    COMPANY_WEBSITE "https://lautfunk.de"
    BUNDLE_ID "de.lautfunk.playlistsoundboard"
    PLUGIN_MANUFACTURER_CODE Laut
    PLUGIN_CODE LfS3
    PLUGIN_NAME "LautFunk Playlist Player & Soundboard"
    PRODUCT_NAME "LautFunk Playlist Soundboard"
    DESCRIPTION "Independent music playlist and soundboard with optional routing, MIDI and OSC"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD FALSE
    VST3_CATEGORIES Instrument Sampler Stereo
    FORMATS VST3)

juce_generate_juce_header(LautFunkPlaylistPlayer)

target_sources(LautFunkPlaylistPlayer PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/SoundboardEngine.cpp
    Source/SoundboardEngine.h
    Source/OscControl.cpp
    Source/OscControl.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h)

target_compile_definitions(LautFunkPlaylistPlayer PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_USE_MP3AUDIOFORMAT=1)

target_link_libraries(LautFunkPlaylistPlayer PRIVATE
    juce::juce_audio_utils
    juce::juce_osc
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags)

if(MSVC)
    target_compile_options(LautFunkPlaylistPlayer PRIVATE /utf-8)
endif()
