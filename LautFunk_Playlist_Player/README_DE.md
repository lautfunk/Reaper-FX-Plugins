# LautFunk Playlist Player & Soundboard v2.0 – Entwicklungsfassung

**Status:** DEV PREVIEW – Quellcode, noch nicht offiziell veröffentlicht oder in REAPER auf Windows/macOS validiert.

Diese Version baut auf dem getesteten LautFunk Playlist Player v1.0 auf. Sie ist **kein Ersatz für eine stabile Live-Installation**. V1.0 und die DEV-Fassung besitzen unterschiedliche Plugin-IDs; beide können parallel installiert werden.

Im ZIP liegen drei kleine, eigens erzeugte `TEST_SAMPLES/*.wav` zum Ausprobieren der Pads.

## Neu: Playlist-Restzeit

Im Playlist-Modus werden angezeigt:

- Anzahl der Titel und Gesamtspielzeit
- **REST**: verbleibende Zeit ab der aktuellen Position bis zum Ende des aktuellen Playlist-Durchlaufs
- Ein dünner Fortschrittsbalken für diesen Durchlauf
- Bei `Repeat: ENDLOS`: verbleibende Zeit bis zum nächsten Playlist-Neustart
- Bei `Repeat: 1 TITEL`: Restlaufzeit des aktuellen Titels
- Bei Shuffle: aktuelle Titelrestzeit plus Länge noch nicht gespielter Titel dieses Zufallsdurchlaufs

Falls eine Dateilänge noch eingelesen wird oder nicht verfügbar ist, steht vor der Restzeit „ca.“. Die Anzeige berücksichtigt manuelles Vorspulen, Überspringen und das Verschieben von Titeln.

## Neu: Soundboard

Oben `SOUNDBOARD` anklicken. Der Musikplayer arbeitet im Hintergrund weiter; beide Funktionen sind unabhängig und werden im selben Stereo-VST3-Ausgang gemischt.

### Soundbänke

- Standardmäßig zwei Bänke: **Jingles** und **Reaktionen**.
- Über **+ Bank** beliebig viele weitere Bänke hinzufügen.
- Die aktuelle Bank im Dropdown auswählen.
- Die Bank im Textfeld daneben umbenennen (Enter drücken oder Feld verlassen).
- **Bank löschen** entfernt die ausgewählte Bank, solange mindestens eine Bank erhalten bleibt.
- Beim Wechsel der Bank laufen gestartete Samples weiter.
- Bänke und Pad-Einstellungen werden mit dem REAPER-Projekt bzw. FX-Preset gespeichert.

### 12 oder 24 Pads

- **12 Pads**: zwölf größere Pads auf Seite 1, zwölf weitere auf Seite 2.
- **24 Pads**: alle 24 Slots einer Bank kompakt auf einer Seite.
- Der Wechsel 12/24 entfernt oder verschiebt keine Sample-Belegung.
- **< Seite / Seite >** wechselt in der 12er-Ansicht zwischen Slots 1–12 und 13–24.

### Samples zuordnen

1. Einen freien Slot anklicken, damit er ausgewählt wird.
2. **Sample laden** betätigen und eine WAV- oder MP3-Datei auswählen.
3. Alternativ eine oder mehrere WAV-/MP3-Dateien direkt auf Pads ziehen. Weitere Dateien füllen die nachfolgenden Slots derselben Bank, soweit Platz vorhanden ist.
4. Rechtsklick auf einen Pad öffnet ein Menü mit Laden, Stoppen, Ausblenden und Leeren.

### Einspieler starten und beenden

- **Linksklick auf einen belegten Pad:** Sample von Anfang an starten. Kein Autoplay, kein automatischer Wechsel zum nächsten Pad.
- Mehrere unterschiedliche Samples können gleichzeitig spielen (maximal 24 gleichzeitig aktive Stimmen).
- Beim erneuten Klick auf einen normalen One-Shot wird derselbe Einspieler zusätzlich neu gestartet (Layering).
- **Loop:** Der ausgewählte Pad spielt in Schleife. Zweiter Klick auf diesen Pad stoppt seine laufenden Loops.
- **Stop Pad:** nur die Einspieler des ausgewählten Slots sofort stoppen.
- **Fade Pad:** Einspieler des ausgewählten Slots mit eingestellter Fade-Zeit ausblenden.
- **STOP ALL:** alle laufenden Soundboard-Samples sofort stoppen (Playlist-Musik bleibt unbeeinflusst).
- **FADE ALL:** alle laufenden Soundboard-Samples sanft ausblenden (Playlist-Musik bleibt unbeeinflusst).

### Pegel und Fade

- **Gain (dB)**: Startlautstärke für neue Wiedergaben des ausgewählten Pads, Standard −6 dB.
- **Fade (s)**: individuelle Ausblendzeit bei `Fade Pad`/`FADE ALL`, Standard 0,7 Sekunden.
- **Loop**: für ausgewählten Pad ein-/ausschalten; gilt für neu gestartete Wiedergaben.
- Änderungen an Gain, Loop und Fade gelten für künftige Starts, nicht rückwirkend für laufende Samples.

## Was die DEV-Fassung noch nicht bietet

- Kein Sidechain-/Sprach-Ducking, kein automatisches Musikbett-Ducking
- Noch keine MIDI-, OSC- oder Stream-Deck-Zuweisung
- Kein Hold-to-Play, keine separaten VST3-Ausgangsbusse
- Keine eigene Bankdatei für Import/Export außerhalb des REAPER-Projekts
- Kein individueller Sample-Namenseditor (Dateiname wird angezeigt)
- Kein automatischer LUFS-Abgleich und kein Peak-Limiter für die Soundboard-Summe
- Keine nahtlosen Playlist-Crossfades

Diese Punkte sind für spätere Entwicklungsstufen vorgesehen.

## Technische Hinweise

- Soundboard-Samples werden beim Start von der Festplatte über JUCE `AudioTransportSource` mit Read-Ahead gestreamt. Das Laden/Öffnen einer Datei erfolgt im UI-Thread, nicht im Audio-Callback.
- Der Datenzugriff erfolgt über eine unveränderliche Momentaufnahme laufender Stimmen. Für eine offizielle Veröffentlichung sind noch ausführliche Echtzeit-, Stress- und Hosttests vorgesehen.
- Bei vielen gleichzeitig lauten Samples kann die Summe **übersteuern**. Für den Livebetrieb einen geeigneten Limiter auf den REAPER-Bus legen und die Pegel kontrollieren.
- REAPER muss Effekte bei gestopptem Transport verarbeiten (z. B. `Run FX when stopped`), damit der Player ohne gestartete REAPER-Wiedergabe hörbar ist.
- In REAPER werden absolute Dateipfade im Projekt gespeichert. Verschwinden oder verschieben sich Dateien, müssen diese neu zugewiesen werden.
- Eine Bank-/Pad-Änderung schreibt zunächst den Zustand im aktuellen REAPER-Projekt. Projekt speichern, um sie zu behalten.
- Diese Entwicklungsfassung ist **noch nicht erfolgreich kompiliert oder auf Windows/macOS getestet**.

## Bauen

Die Datei `GITHUB_SETUP_DE.md` im ZIP beschreibt einen separaten Git-Entwicklungsbranch mit einem eigenen GitHub-Actions-Workflow für Windows x64 und macOS Universal. Der offizielle Release `playlist-v1.0.0` wird dadurch nicht berührt.

## Ursprung

Die getrennte Bank-/Pad-Bedienung ist funktional vom [Ultraschall Soundboard](https://github.com/Ultraschall/ultraschall-soundboard) inspiriert. Der Soundboard-Code in diesem Verzeichnis wurde neu geschrieben und enthält keine aus Ultraschall kopierten Quellcodedateien.
