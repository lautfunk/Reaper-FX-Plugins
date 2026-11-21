# Installation unter REAPER

## Dateien

| Datei im Repository | Ziel (relativ zum REAPER-Ressourcenordner) |
| --- | --- |
| `Effects/LautFunk/LautFunk_MIDI_Chaos_Engine_v1.jsfx` | `Effects/LautFunk/LautFunk_MIDI_Chaos_Engine_v1.jsfx` |
| `Scripts/LautFunk/LautFunk_Chaos_Bridge.lua` (optional) | `Scripts/LautFunk/LautFunk_Chaos_Bridge.lua` |

**Ressourcenordner finden:** REAPER → **Options → Show REAPER resource path in explorer/finder**. Unter Windows meist `%APPDATA%\\REAPER`, bei einer portablen REAPER-Installation jedoch der portable Ressourcenordner.

1. Falls nötig die Unterordner `LautFunk` unter `Effects` und `Scripts` anlegen.
2. JSFX in `Effects/LautFunk` kopieren, REAPER neu starten und im FX-Browser `MIDI Chaos Engine` suchen.
3. Die Engine **vor** einem Instrument in die FX-Kette einfügen. Beispiel: `MIDI Chaos Engine → LautFunk FartSynth 61 → Audioausgang`.
4. Optional Lua-Brücke über **Actions → Show action list → New action → Load ReaScript** laden und manuell starten. Die Lua-Brücke wird nur für die Steuerung weiterer FX-Host-Parameter benötigt.
5. Für POLYTRANCE ggf. MIDI-Kanal-/Bus-Empfang des Zielinstruments passend konfigurieren.

## Updates

Bestehende `LautFunk_MIDI_Chaos_Engine_v1.jsfx` ersetzen, aber vorher eine Sicherung machen. Gleicher Dateiname dient der Projektkompatibilität; vollständige Kompatibilität älterer Szenenspeicher ist noch nicht in REAPER bestätigt.

## Hilfe bei Problemen

Bei Syntaxfehlern die angegebene Zeile und REAPER-Version notieren. Bei Stille: Transport, MIDI-Kanalzuordnung, FX-Reihenfolge und Synthesizer-Audio prüfen. Bei hängenden Noten: Panic/All Notes Off betätigen.
