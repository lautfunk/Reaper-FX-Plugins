# LautFunk MIDI Chaos Engine 61 — v1.4.1 POLYTRANCE + SPEED UI

**Status: Entwicklungs-/Testversion (DEV).** JSFX (EEL2) mit optionaler Lua-ReaScript-Brücke für REAPER. **Kein VST3 und kein Klangerzeuger.** Die Engine erzeugt MIDI-Nachrichten für nachfolgende Synthesizer.

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

Weiterführend: [Installation](DOKUMENTATION/INSTALLATION_DE.md) · [Testplan](DOKUMENTATION/TESTPLAN_DE.md) · [Changelog](CHANGELOG.md).

## Technische Grenzen

Die MIDI-Steuerung von Filter, Hüllkurven, Glide usw. hängt vom angesteuerten Synthesizer ab. Die Lua-Brücke kann nur veröffentlichte REAPER-FX-Parameter zuordnen und muss während der Host-Modulation laufen. MPE-Unterstützung ist instrumentabhängig. Ein eigenständiges Audio-Gate und universelle herstellerspezifische SysEx-Profile sind **nicht** enthalten.

**Testhinweis:** Quellcode und Paketstruktur sind statisch geprüft. Weder EEL2-Kompilierung noch MIDI-/Audio-Verhalten in REAPER sind hier vollständig verifiziert. Bitte bestehende Projekte sichern und zunächst mit einer Kopie testen.

Lizenz: [MIT](../LICENSE).
