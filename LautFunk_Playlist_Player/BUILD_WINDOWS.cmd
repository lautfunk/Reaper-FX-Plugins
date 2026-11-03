@echo off
setlocal
cd /d "%~dp0"
where cmake >nul 2>&1
if errorlevel 1 (
  echo ERROR: CMake nicht gefunden. Bitte CMake und Visual Studio 2022 C++ installieren.
  pause
  exit /b 1
)
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
if errorlevel 1 (
  echo CMake-Konfiguration fehlgeschlagen. Bitte die eigentliche Fehlermeldung oben pruefen.
  echo Nur bei einem Git-Downloadfehler: Internetzugang pruefen oder JUCE lokal bereitstellen.
  pause
  exit /b 1
)
cmake --build build --config Release --target LautFunkPlaylistPlayer_VST3
if errorlevel 1 (
  echo Build fehlgeschlagen. Bitte Fehlermeldungen pruefen.
  pause
  exit /b 1
)
echo.
echo Fertig. Suche LautFunk Playlist Soundboard.vst3 unter build\LautFunkPlaylistPlayer_artefacts\Release\VST3\.
echo Kopiere den kompletten .vst3-Ordner nach C:\Program Files\Common Files\VST3\
pause
