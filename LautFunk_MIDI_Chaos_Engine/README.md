# LautFunk MIDI Chaos Engine 61 — v1.4.1 POLYTRANCE + SPEED UI

**Status: BETA (v1.4.1) – erfolgreicher Anwender-Praxistest in REAPER gemeldet; detaillierte Tests einzelner Funktionen und Plattformen stehen noch aus.** JSFX (EEL2) mit optionaler Lua-ReaScript-Brücke für REAPER. **Kein VST3 und kein Klangerzeuger.** Die Engine erzeugt MIDI-Nachrichten für nachfolgende Synthesizer.

## Funktionen

- Eigene dunkle LautFunk-GUI mit ausgeblendeten Standard-JSFX-Reglern.
- Global sichtbare **GLOBAL NOTE SPEED**-Bedienung mit Sekundenmodus und musikalischer Tempo-Synchronisierung (z. B. 1/4, 1/8, 1/16, Triolen und punktierte Werte).
- 61-Tasten-Matrix, Velocity-/Gate-Werte, Wahrscheinlichkeit, Swing, Humanize und Panic/Note-Off-Verwaltung.
- CHAOS: zufällige und mathematisch-chaotische Modelle.
- MUSIC: Skalen, Dur-/Moll- und erweiterte Akkorde, Akkordfolgen und Arpeggio-Sequenzen.
- HYPNOTIC/SUSPENSE: polymetrische Muster, offene Harmonien, Phrygisch, Orgelpunkt, Ratchets, Kanon und langsame Motiventwicklung.
- POLYTRANCE: dreistimmiges E-phrygisches 16:7:5-Step-Muster und FLOW mit 32-Takt-Entwicklung; getrennte MIDI-Kanäle für Stimmen.
- 16 Modulationsquellen für MIDI-CC u. a.; optional REAPER-FX-Parametersteuerung über die Lua-Brücke.

## Schnellstart

1. Im REAPER-Menü **Options → Show REAPER resource path** öffnen.
2. `Effects/LautFunk/LautFunk_MIDI_Chaos_Engine_v1.jsfx` aus diesem Repository in den REAPER-Ressourcenordner unter `Effects/LautFunk/` kopieren.
3. Optional `Scripts/LautFunk/LautFunk_Chaos_Bridge.lua` in `Scripts/LautFunk/` kopieren und über **Actions → Show action list → New action → Load ReaScript** hinzufügen.
4. Auf derselben REAPER-Spur **MIDI Chaos Engine vor den Synthesizer** (z. B. [FartSynth 61](../LautFunk_FartSynth_61_v1.0.jsfx)) setzen.
5. Wiedergabe starten und die globale Geschwindigkeitssteuerung oben in der GUI einstellen.

## Anleitungen (Deutsch)

- [**Bedienungsanleitung** – alle Reiter, globale Geschwindigkeit, MIDI-Workflow und Modulation](DOKUMENTATION/BEDIENUNGSANLEITUNG_DE.md)
- [**Installation** – Dateiablage, JSFX und optionale Lua-Brücke](DOKUMENTATION/INSTALLATION_DE.md)
- [**Musikalische Beispiele** – Techno, Trance, Goa, Psytrance und Ambient](DOKUMENTATION/BEISPIELE_PRESETS_DE.md)
- [**Fehlerbehebung** – kein Ton, Tempo-Sync, MIDI-Kanäle, Lua und hängende Noten](DOKUMENTATION/FEHLERBEHEBUNG_DE.md)
- [**Testplan und bestätigter Teststatus**](DOKUMENTATION/TESTPLAN_DE.md)
- [**Changelog und Versionshistorie**](CHANGELOG.md)


## Technische Grenzen

Die MIDI-Steuerung von Filter, Hüllkurven, Glide usw. hängt vom angesteuerten Synthesizer ab. Die Lua-Brücke kann nur veröffentlichte REAPER-FX-Parameter zuordnen und muss während der Host-Modulation laufen. MPE-Unterstützung ist instrumentabhängig. Ein eigenständiges Audio-Gate und universelle herstellerspezifische SysEx-Profile sind **nicht** enthalten.

**Testhinweis:** Der Entwickler/Anwender hat am 21.11.2026 berichtet, dass das Plug-in in REAPER erfolgreich funktioniert. Konkrete Einzeltests (z. B. Lua-Brücke, alle 14 GUI-Reiter, 560-Step-Zyklus und Plattformen) wurden nicht separat bestätigt. Für die Beta weiterhin Projektkopien und Backups empfehlen.

Lizenz: [MIT](../LICENSE).
