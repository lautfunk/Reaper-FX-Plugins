# Installation – LautFunk Playlist Player & Soundboard

Stand: **v2.3 ROUTING RC** (Release-Kandidat, keine freigegebene stabile Version).

## Unterstützte Pakete

- **Windows x64 VST3** – gebaut mit Visual Studio 2022.
- **macOS Universal VST3** – enthält Intel (x86_64) und Apple Silicon (arm64), Build-Ziel macOS 11+.

Es gibt aktuell weder einen VST2- noch einen AU-, CLAP- oder eigenständigen Standalone-Build.

## Windows

1. Die Windows-x64-ZIP-Datei aus dem freigegebenen GitHub Release oder einem Test-Workflow herunterladen.
2. Falls von GitHub Actions: ZIP zunächst entpacken; darin liegt noch ein zweites ZIP, das ebenfalls entpackt werden muss.
3. Den **gesamten** Ordner \`LautFunk Playlist Soundboard ROUTING RC.vst3\` nach

   \`\`\`text
   C:\Program Files\Common Files\VST3\
   \`\`\`

   kopieren.
4. REAPER oder die gewünschte VST3-fähige DAW (neu) starten und, falls nötig, den VST3-Scan ausführen.
5. Auf einer neuen Spur das Plugin laden. Im **AUDIO-ROUTING**-Menü **Standard: Stereo-Mix** belassen.
6. Im Playlist-Tab eine WAV- oder MP3-Datei laden oder im Soundboard-Tab ein Sample zuweisen und starten.

> Nicht nur eine DLL aus einem \`.vst3\`-Bundle kopieren: Die gesamte Ordnerstruktur ist erforderlich.

## macOS

1. Das **macOS-Universal-VST3** herunterladen und ZIP entpacken.
2. \`LautFunk Playlist Soundboard ROUTING RC.vst3\` in

   \`\`\`text
   ~/Library/Audio/Plug-Ins/VST3/
   \`\`\`

   kopieren; alternativ systemweit nach \`/Library/Audio/Plug-Ins/VST3/\`.
3. Die DAW neu starten und VST3-Scan durchführen.

**Wichtig:** Die macOS-Builds der Testreihe sind **ad-hoc signiert, nicht Apple-notarisiert**. Gatekeeper kann die Nutzung einschränken. Für eine allgemein zugängliche macOS-Veröffentlichung sollte eine Apple-Developer-ID-Signierung und Notarisierung erfolgen, bevor man den Build als problemlos installierbar bewirbt.

## Erstkonfiguration

- **Stereo-Mix** ist der Standard. Musik und Einspieler laufen über dieselben beiden Kanäle.
- **Ducking** kann im Soundboard-Tab aktiviert/deaktiviert und mit Attack/Release/Absenkung angepasst werden.
- **OSC** ist bei Neuinstallation **ausgeschaltet** und bei Aktivierung ausschließlich lokal (\`127.0.0.1\`, Standardport 9001) erreichbar.
- **MIDI** muss über die jeweilige DAW an das Plugin geliefert werden.
- Wenn trotz gestarteter Playlist bei gestopptem DAW-Transport nichts zu hören ist, die Host-Option zur Plugin-Verarbeitung im Stoppzustand prüfen (REAPER: *Run FX when stopped*).

## Mit alten DEV-Fassungen

v2.0, v2.1, v2.2 und v2.3 RC verwenden **unterschiedliche Plugin-IDs**. Sie können parallel installiert werden. Ein bereits bestehender Projekt-Effekt wird deshalb **nicht automatisch** auf eine neuere Version aktualisiert.

Vor dem Wechsel: REAPER-Projekt sichern, alte Plugin-Presets exportieren und Audiodateipfade prüfen.

## Deinstallation

Die jeweilige \`.vst3\`-Bundle-Datei bzw. den entsprechenden Bundle-Ordner aus dem VST3-Verzeichnis entfernen. Das entfernt **nicht** die externen WAV/MP3-Dateien und **nicht** die REAPER-Projekte, in denen Plugins referenziert werden.

## Hinweise zur Audioqualität

Der Soundboard-Mix hat derzeit keinen eingebauten True-Peak-Limiter oder automatischen LUFS-Abgleich. Bei mehreren gleichzeitigen lauten Samples kann es zu Übersteuerungen kommen. Für Livestream und Podcast die Summenpegel beobachten und gegebenenfalls einen Limiter hinter das Plugin setzen.
