#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"

# Universal VST3 fuer Apple Silicon + Intel, macOS 11 oder neuer.
cmake -S . -B build-macos -G Xcode \
  '-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64' \
  -DCMAKE_OSX_DEPLOYMENT_TARGET=11.0 \
  -DCMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED=NO
cmake --build build-macos --config Release \
  --target LautFunkPlaylistPlayer_VST3 --parallel 2

printf '\nBuild abgeschlossen. VST3 hier:\n'
find build-macos/LautFunkPlaylistPlayer_artefacts/Release/VST3 -maxdepth 1 -name '*.vst3' -print
