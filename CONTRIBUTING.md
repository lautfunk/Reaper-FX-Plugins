# Mitmachen bei LautFunk Audio-Plugins

Das Projekt ist **kostenlos** und der von LautFunk selbst entwickelte Code steht unter der [MIT-Lizenz](LICENSE). Issues, Fehlerberichte, Dokumentationskorrekturen und Pull Requests sind willkommen.

## Projektaufbau

- `LautFunk_*.jsfx`: eigenständige REAPER-JSFX-Effekte und -Instrumente.
- `LautFunk_Render_Ziele.lua`: optionales REAPER-ReaScript für SoftGuard.
- `LautFunk_Playlist_Player/Source/`: C++-/JUCE-Quellcode des VST3.
- `LautFunk_Playlist_Player/CMakeLists.txt`: Builds mit JUCE 9.0.4.
- `LautFunk_Playlist_Player/DOKUMENTATION/`: Handbuch, Installation, Routing und Testplan.
- `.github/workflows/`: reproduzierbare GitHub-Actions-Builds.

## Beiträge

1. Vor neuen Funktionen möglichst ein GitHub Issue eröffnen.
2. Änderungen auf einem eigenen Branch entwickeln.
3. Bei JSFX möglichst bestehende Slider-Nummern und Preset-Kompatibilität bewahren.
4. Bei VST3 die langfristig stabile Plugin-ID und die Grundeinstellung **gemeinsamer Stereoausgang 1/2** beibehalten.
5. Neue Funktionen nur optional einschalten, wenn sie Netzwerkzugriff oder komplexe DAW-Routings erfordern.
6. Unter Windows und möglichst macOS kompilieren; das Verhalten in REAPER testen.
7. README/Changelog/Anleitung und bei Audio-Routing den Testplan aktualisieren.
8. Pull Request mit Beschreibung, Testschritten und gegebenenfalls Screenshots eröffnen.

## Lizenz und Rechte

Mit dem Einsenden eigener Änderungen bestätigst du, dass du die entsprechenden Rechte besitzt, sie dem Projekt unter **MIT** zur Verfügung zu stellen. Bitte keine fremden Audiodateien, Samples, proprietäre SDK-Dateien, geschützte Grafiken oder nicht passend lizenzierte Codeausschnitte einreichen.

**Wichtig:** Die MIT-Lizenz unserer C++-Dateien ersetzt nicht die Bedingungen des **JUCE 9**-Frameworks. Wer JUCE-basierte Software erstellt oder weitergibt, muss eigenständig eine zu seinem Verwendungszweck passende JUCE-Lizenz nutzen. Keine privaten Lizenzdaten oder Tokens in Pull Requests hochladen.

## Fehlerberichte

Bitte Betriebssystem, REAPER-/DAW-Version, Plugin-Version, Sample-Rate/Buffer, Audio-Routing-Modus, Reproduktionsschritte und erwartetes/tatsächliches Verhalten angeben. Für den VST3 ist eine [Testcheckliste](LautFunk_Playlist_Player/DOKUMENTATION/TESTPLAN_DE.md) vorhanden.

Veröffentlichte Downloads gibt es unter [GitHub Releases](https://github.com/lautfunk/Reaper-FX-Plugins/releases); kurzlebige GitHub-Actions-Builds dienen nur der Entwicklung.
