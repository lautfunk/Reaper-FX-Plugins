# Installation – LautFunk Playlist Player & Soundboard

Stand: **v2.3.1** (stabiles Wartungsrelease, unveränderte Plugin-ID gegenüber v2.3.0).

## Unterstützte Pakete

- **Windows x64 VST3** – gebaut mit Visual Studio 2022.
- **macOS Universal VST3** – enthält Intel (x86_64) und Apple Silicon (arm64), Build-Ziel macOS 11+.

Es gibt aktuell weder einen VST2- noch einen AU-, CLAP- oder eigenständigen Standalone-Build.

## Windows

1. Die Windows-x64-ZIP-Datei der [offiziellen v2.3.1-Veröffentlichung](https://github.com/lautfunk/Reaper-FX-Plugins/releases/tag/playlist-soundboard-v2.3.1) herunterladen und **einmal** entpacken. Die enthaltenen Dateien `LICENSE` und `THIRD_PARTY_NOTICES.md` mitlesen.
2. Den **gesamten** Ordner `LautFunk Playlist Soundboard.vst3` nach

   ```text
   C:\Program Files\Common Files\VST3\
   ```

   kopieren.
3. REAPER oder die gewünschte VST3-fähige DAW (neu) starten und, falls nötig, den VST3-Scan ausführen.
4. Auf einer neuen Spur das Plugin laden. Im **AUDIO-ROUTING**-Menü **Standard: Stereo-Mix** belassen.
5. Im Playlist-Tab eine WAV- oder MP3-Datei laden oder im Soundboard-Tab ein Sample zuweisen und starten.

> Nicht nur eine DLL aus einem `.vst3`-Bundle kopieren: Die gesamte Ordnerstruktur ist erforderlich.

## macOS

1. Das **macOS-Universal-VST3** herunterladen und ZIP entpacken.
2. `LautFunk Playlist Soundboard.vst3` in

   ```text
   ~/Library/Audio/Plug-Ins/VST3/
   ```

   kopieren; alternativ systemweit nach `/Library/Audio/Plug-Ins/VST3/`.
3. Die DAW neu starten und VST3-Scan durchführen.

**Wichtig:** Auch die offizielle macOS-v2.3.1 ist **nur ad-hoc signiert und nicht Apple-notarisiert**. Gatekeeper kann eine Sicherheitswarnung anzeigen oder das VST3 blockieren. Lade ausschließlich von der offiziellen Release-Seite herunter und prüfe die Herkunft, bevor du eine etwaige Ausnahme in den macOS-Sicherheitseinstellungen zulässt.

## Erstkonfiguration

- **Stereo-Mix** ist der Standard. Musik und Einspieler laufen über dieselben beiden Kanäle.
- **Ducking** kann im Soundboard-Tab aktiviert/deaktiviert und mit Attack/Release/Absenkung angepasst werden.
- **OSC** ist bei Neuinstallation **ausgeschaltet** und bei Aktivierung ausschließlich lokal (`127.0.0.1`, Standardport 9001) erreichbar.
- **MIDI** muss über die jeweilige DAW an das Plugin geliefert werden.
- Wenn trotz gestarteter Playlist bei gestopptem DAW-Transport nichts zu hören ist, die Host-Option zur Plugin-Verarbeitung im Stoppzustand prüfen (REAPER: *Run FX when stopped*).

## Mit alten DEV-Fassungen

Die älteren v2.0-, v2.1-, v2.2- und Routing-/RC-Entwicklungsfassungen verwenden **andere Plugin-IDs** als die stabile Produktlinie. **v2.3.0 und v2.3.1 haben dagegen dieselbe Plugin-ID**: Ein Austausch der VST3-Datei aktualisiert die stabile Installation. Vorher ein REAPER-Projekt-Backup anfertigen; ältere DEV-/RC-Effekte werden nicht automatisch ersetzt.

Vor dem Wechsel: REAPER-Projekt sichern, alte Plugin-Presets exportieren und Audiodateipfade prüfen.

## Deinstallation

Die jeweilige `.vst3`-Bundle-Datei bzw. den entsprechenden Bundle-Ordner aus dem VST3-Verzeichnis entfernen. Das entfernt **nicht** die externen WAV/MP3-Dateien und **nicht** die REAPER-Projekte, in denen Plugins referenziert werden.

## Lizenz

Der selbst entwickelte LautFunk-Quellcode ist unter **MIT** verfügbar. Den Downloadpaketen liegen `LICENSE` und `THIRD_PARTY_NOTICES.md` bei; letztere enthält den vollständigen ursprünglichen MIT-Lizenztext des Ultraschall Soundboards. JUCE 9.0.4 hat gesonderte Lizenzbedingungen; siehe `DOKUMENTATION/RECHT_LIZENZEN_DE.md`.

## Hinweise zur Audioqualität

Der Soundboard-Mix hat derzeit keinen eingebauten True-Peak-Limiter oder automatischen LUFS-Abgleich. Bei mehreren gleichzeitigen lauten Samples kann es zu Übersteuerungen kommen. Für Livestream und Podcast die Summenpegel beobachten und gegebenenfalls einen Limiter hinter das Plugin setzen.
