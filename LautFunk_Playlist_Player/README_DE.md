# LautFunk Playlist Player v1.0 – VST3 für REAPER

## Was ist das?

Ein **virtuelles Instrument, das eine MP3/WAV-Playlist als Stereo-Audio ausgibt**. Es wird wie ein VSTi auf eine REAPER-Spur geladen. Kein ReaScript, keine Audio-Items, keine Aufnahme und keine laufende Projekt-Wiedergabe nötig – solange REAPER das Plugin bei gestopptem Transport mit Audiobuffern versorgt.

**Status:** Quellcode-Version v1.0. Die Vorversion v0.1.1 wurde vom Anwender unter Windows erfolgreich kompiliert und in REAPER als funktionsfähig gemeldet. **Die neuen Änderungen in v1.0 sind hier noch nicht unter Windows kompiliert oder in REAPER getestet.** Das Paket enthält keine Windows-Binärdatei.

## Funktionen von v1.0

- MP3- und WAV-Dateien hinzufügen: mehrere Dateien auswählen oder per Drag-and-drop hineinziehen
- Playlist im Plugin, Doppelklick startet einen Titel
- Abspielen, Pause, Stop, vorheriger/nächster Titel
- Titel verschieben (Hoch/Runter), entfernen oder Playlist leeren
- Normale Reihenfolge / Zufallswiedergabe
- **Repeat/Endlos:** Aus, gesamte Playlist in Endlosschleife oder einzelnen Titel wiederholen. Werkseinstellung: ENDLOS. Ein hervorgehobener Status zeigt den aktiven Modus.
- Lautstärke in dB, als VST3-Parameter für REAPER automatisierbar (Werkseinstellung −12 dB)
- **Gesamtspielzeit der Playlist:** Dauer aller geladenen MP3-/WAV-Titel, inklusive Stundenanzeige bei langen Listen. Die Dauer jedes Titels erscheint rechts in der Liste.
- Titelanzahl und Hinweis auf noch zu lesende bzw. nicht auswertbare Dateien.
- Überarbeitete Oberfläche mit getrennten Bereichen für Listenübersicht, aktuellen Titel, Transport, Status und Einstellungen.
- Zeit- und Fortschrittsanzeige; im Song springen
- Playlist als `.m3u8` speichern bzw. einlesen (auch relative Pfade beim Import)
- Wiederherstellen der Liste nach Speichern/Neuladen des REAPER-Projekts (Dateipfade werden gespeichert)
- Audio-Streaming über Lese-Thread und Read-ahead, um nicht alle Musikdateien in den RAM laden zu müssen
- Automatischer Titelwechsel auch bei geschlossenem Plugin-Fenster
- Unterstützt unterschiedliche MP3-/WAV-Sampleraten über JUCE-Transport
- Dunkle LautFunk-Bedienoberfläche

**Was noch nicht enthalten ist:** Crossfade, Ducking beim Sprechen, Titel-Suchfeld, MP3-Tag-/Cover-Anzeige, unabhängige Audioausgabe außerhalb REAPERs, garantierte lückenlose Übergänge oder eine fertig signierte Installationsdatei. Der automatische Titelwechsel erfolgt über einen 20-Hz-Timer; dadurch können kurze Pausen zwischen Titeln entstehen.

## Windows: Kompilieren

Voraussetzungen:

1. Windows 10/11 mit REAPER 64-Bit.
2. [Visual Studio 2022 Community](https://visualstudio.microsoft.com/vs/community/) oder Build Tools 2022, mit **Desktopentwicklung mit C++**.
3. [CMake 3.22 oder neuer](https://cmake.org/download/) und Git.
4. Internet beim ersten Build, damit CMake automatisch **JUCE 9.0.4** herunterlädt. Alternativ ein lokales JUCE-Checkout in einem Ordner `JUCE` neben der `CMakeLists.txt` bereitstellen.

### Von v0.1.1 auf v1.0 aktualisieren (schnellster Weg)

1. REAPER beenden. Die bestehenden VST3-Dateien und den v0.1.1-Projektordner optional sichern.
2. Im **bereits erfolgreich gebauten** Projektordner `C:\LautFunk_Playlist_Player_VST3_v0.1.1\` die Dateien `CMakeLists.txt`, `BUILD_WINDOWS.cmd`, `README_DE.md` und den vollständigen Unterordner `Source` durch die entsprechenden Dateien aus v1.0 ersetzen.
3. **Den vorhandenen `build`-Ordner stehen lassen**, solange du den Projektpfad nicht geändert hast. So kann JUCE aus dem vorherigen Build wiederverwendet werden.
4. `BUILD_WINDOWS.cmd` ausführen. Nach Erfolg REAPER beenden und den neuen vollständigen `.vst3`-Ordner in `C:\Program Files\Common Files\VST3\` ersetzen. REAPER starten und neu scannen.

Alternativ v1.0 frisch in einen **kurzen, unveränderlichen Pfad** wie `C:\LFPlayer\` entpacken und `BUILD_WINDOWS.cmd` doppelklicken. Verschiebst du einen Projektordner mit vorhandenem `build`, musst du den `build`-Ordner löschen, damit CMake keine alten absoluten Pfade verwendet.

Die Eingabeaufforderung zeigt eventuelle Compilerfehler an. Alternativ im Terminal:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release --target LautFunkPlaylistPlayer_VST3
```

Der Output liegt anschließend im Projekt-Buildordner unter `LautFunkPlaylistPlayer_artefacts/Release/VST3/` (genauen Pfad im Build-Log prüfen). Den **vollständigen Ordner** `LautFunk Playlist Player.vst3` nach

```text
C:\Program Files\Common Files\VST3\
```

kopieren. Falls der VST3-Eintrag nicht angezeigt wird, in REAPER **Options → Preferences → Plug-ins → VST** einen erneuten Scan durchführen.

Bei fehlender Internetverbindung beim JUCE-Download kann der Build nicht starten; alternativ [JUCE](https://github.com/juce-framework/JUCE/releases/tag/9.0.4) manuell herunterladen und den entpackten Quellcode im Projekt-Unterordner `JUCE` ablegen.

## REAPER: Einrichten für Livestreams ohne Aufnahme

1. Neue leere Spur `LAUTFUNK BACKGROUND MUSIC` erstellen.
2. Im FX-Browser `VSTi: LautFunk Playlist Player` als Instrument laden. Es werden **keine MIDI-Items** benötigt.
3. REAPER unter **Options → Preferences → Audio → Playback** öffnen und **Run FX when stopped** aktivieren.
4. Darauf achten, dass REAPERs Audiogerät im Stop-Zustand geöffnet bleibt. Wenn die Musik nicht zu hören ist: `Flush FX on stop`, Auto-Bypass auf Stille und Track-FX-Bypass kontrollieren.
5. MP3/WAV-Dateien per Drag-and-drop hineinziehen oder `+ Dateien` wählen.
6. Im Plugin auf **PLAY** klicken. REAPER muss nicht aufnehmen. Der globale REAPER-Transport kann gestoppt bleiben.
7. Die Spur über Track-Fader, Sends und Audio-Hardware-Ausgänge zum Stream-Mix/OBS/Loopback routen. Sonstige Effekte **hinter** dem Instrument in der FX-Kette ergänzen.

### Empfohlenes Routing

```text
Mic / Voice Track  ────┐
                      ├──► Stream-Bus ───► OBS / Stream-Ausgang
Music Track:          │
Playlist Player VST3 ─┘
          │
   EQ / Ducking (optional)
```

Falls du zur Aufnahme innerhalb REAPERs arbeitest, ändert sich daran nichts: Die Musikspur ist ein normales Instrument. Sie muss **nicht** record-armed sein.

### Live-Betrieb: Sicherheit

- Vor echtem Livestream ein längeres MP3 und WAV testen, Playlist-Ende prüfen, Projekt speichern und wieder öffnen.
- Bei geladenen Live-Projekten REAPER-Audioengine und Plugin nicht durch globale Stop-/Pause-Aktionen anhalten, falls `Run FX when stopped` deaktiviert ist.
- Titeldateien nicht während des Streams verschieben/umbenennen. VST3 speichert Pfade, nicht die Musikdaten.
- Ein Track kann +6 dB Gain erreichen; dies ist kein Brickwall-Limiter. Für Schutz vor Übersteuerungen nach dem Plugin einen Limiter im Musikbus einsetzen.
- Bei mehreren Musikquellen auf Routing-Rückkopplungen achten.

## Bedienung

| Element | Funktion |
|---|---|
| + Dateien / Drag & Drop | MP3/WAV hinzufügen |
| M3U8 laden / speichern | Playlists importieren/exportieren |
| Doppelklick in Liste | Gewählten Titel starten |
| Hoch / Runter | Titel verschieben |
| Entfernen / Leeren | Eintrag oder ganze Liste löschen |
| PLAY / PAUSE / STOP | Nur Player-Transport, nicht REAPER |
| `|<` / `>|` | Vorheriger/nächster Titel |
| Zufall | Zufällige Titelreihenfolge; bei Repeat Aus ohne Wiederholung innerhalb der Runde |
| Repeat: AUS / ENDLOS / 1 TITEL | Ausschalten, gesamte Playlist endlos oder denselben Titel wiederholt abspielen |
| GESAMTSPIELZEIT | Summe der Dauern aller geladenen Titel; während des Einlesens zunächst vorläufig |
| Zeitangabe je Titel | Songdauer in der Playliste; fehlende bzw. nicht lesbare Dateien sind markiert |
| Fortschrittsbalken | Abspielposition setzen |
| Lautstärke (dB) | Player-Ausgabepegel, REAPER-automatisierbar |

## Technische Architektur

- JUCE 9.0.4 / C++17 / CMake, VST3-Format
- Synth/Instrument ohne Eingang und mit Stereo-Ausgang
- `AudioFormatManager` mit WAV/MP3, `AudioFormatReaderSource`, `AudioTransportSource` (Sampleratenanpassung), `TimeSliceThread` (Read-ahead)
- Playlist- und Bedienungslogik auf dem Message-Thread; keine Dateizugriffe in `processBlock`
- Dauererkennung: maximal ein noch nicht eingelesener Eintrag pro 20-Hz-Timerdurchlauf, über `AudioFormatReader::lengthInSamples / sampleRate`. Werte werden für die Liste zwischengespeichert und beim Verschieben, Entfernen oder Laden von Playlists synchron gehalten. Dabei kann das Auslesen sehr langsamer oder nicht erreichbarer Dateien die Bedienoberfläche kurz blockieren; die Echtzeit-Audiobearbeitung öffnet keine Dateien.
- Volumenparameter mit 25-ms-Smoothing gegen Regler-Klicks
- Playlist-Persistenz im REAPER-Projekt als Plugin-State; nach Projektladen kein automatischer Start
- Audio ist vollständig REAPER-geroutet, kein eigenes Windows-Audiogerät

## Lizenzen und Quellen

Der **JUCE-Frameworkcode ist nicht Teil dieses ZIPs**. Bei Verwendung oder Weitergabe bitte die aktuellen JUCE-9-Lizenzbedingungen prüfen (AGPLv3 bzw. passende kommerzielle Lizenz): https://juce.com/get-juce/

Referenzen:
- https://juce.com/tutorials/tutorial_playing_sound_files/
- https://docs.juce.com/develop/classjuce_1_1AudioTransportSource.html
- https://github.com/juce-framework/JUCE/releases/tag/9.0.4
- https://www.reaper.fm/guides/ReaperTroubleshootingGuide.pdf

## Stand

**v0.1 – 02.11.2026:** Erste Quellcode-Version.


## Korrektur v0.1.1 (2. November 2026)

Die CMake-Projektdefinition aktiviert jetzt neben C++ auch die Sprache C:

```cmake
project(LautFunkPlaylistPlayer VERSION 0.1.1 LANGUAGES C CXX)
```

Dies behebt die JUCE-9-Konfigurationsmeldung `A C compiler is required to build targets that depend on JUCE` bei einer zuvor nur mit `LANGUAGES CXX` konfigurierten Anwendung. Der Compiler war dabei nicht das Problem. Das Build-Skript meldet bei Konfigurationsfehlern nicht mehr irrefuehrend einen fehlenden Internetzugang.

Nach Austausch der Projektdateien kann `BUILD_WINDOWS.cmd` erneut ausgefuehrt werden. Falls noch ein alter CMake-Cache stoert, den Ordner `build` loeschen und das Skript erneut starten.

Hinweis: v0.1.1 korrigiert die CMake-Konfiguration; ein vollstaendiger Windows-VST3-Build und REAPER-Hoertest wurden in dieser Umgebung noch nicht ausgefuehrt.

## Neu in Version 1.0 (2. November 2026)

- **Gesamtdauer:** Automatisches Summieren aller Songlängen; die Dauer wird anhand der Dateimetadaten ermittelt. Die Berechnung funktioniert unabhängig davon, welcher Song gerade läuft.
- **Dauer je Titel:** In jeder Zeile der Playlist wird nun auch die Titelspielzeit angezeigt.
- **Endlosmodus deutlich sichtbar:** Die Auswahl `Repeat: ENDLOS` wiederholt nach dem letzten Song den ersten. Oben wird `ENDLOS AKTIV` hervorgehoben. `Repeat: AUS` beendet die Liste am Ende, `Repeat: 1 TITEL` wiederholt nur einen Song.
- **Überarbeitete GUI:** Angepasste Größen und Abstände; insbesondere sind die Transporttasten, die Statuszeile und die Bedienelemente unten voneinander getrennt.
- **Versionsnummer:** 1.0.0 in CMake und `VERSION 1.0` in der Oberfläche. VST3-Plugin-ID bleibt identisch, damit bestehende REAPER-Projekte die aktualisierte Version wiederfinden.
- **Unverändert:** MP3/WAV-Wiedergabe, getrennte Player-Steuerung, Playlist-Persistenz, M3U8, Shuffle, REAPER-Automation des Lautstärkeparameters, Spurenrouting, keine Aufnahme erforderlich.

### Praxistest nach dem Build

1. 3 MP3-/WAV-Titel laden und die Gesamtdauer mit den Einzeldauern vergleichen.
2. `Repeat: ENDLOS` wählen, zum letzten Titel springen und auf den automatischen Neustart am Listenanfang achten.
3. `Repeat: AUS` wählen und prüfen, ob die Playlist nach dem letzten Titel stoppt.
4. `Repeat: 1 TITEL` prüfen, danach `Zufall` zusammen mit Endlos testen.
5. Plugin-Fenster verkleinern und vergrößern; kontrollieren, ob die Statuszeile die Transporttasten nicht überdeckt.
6. Projekt speichern, REAPER neu öffnen und die gespeicherte Wiederholungseinstellung prüfen.

**Validierung:** Die Änderungen wurden auf Quellcode-Konsistenz und GUI-Geometrie geprüft. Ein nativer JUCE/Windows-Build der v1.0 war hier nicht möglich. Deshalb erst testen, bevor du diese Fassung in einem produktiven Livestream einsetzt.
