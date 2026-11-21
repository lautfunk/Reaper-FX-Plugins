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

## Installation der optionalen Lua-Brücke

1. Die Datei `LautFunk_Chaos_Bridge.lua` in `Scripts/LautFunk/` ablegen.
2. REAPER → **Actions → Show action list** → **New action → Load ReaScript** und die Lua-Datei auswählen.
3. Auf einer Spur mit MIDI Chaos Engine und nachgeschaltetem Zielinstrument die Aktion ausführen.
4. In der Brücke **USE SELECTED TRACK** wählen, anschließend optional **AUTO-MAP FARTSYNTH** oder die 16 Lanes manuell den Ziel-FX-Parametern zuweisen.
5. Für dauernde Host-Parametermodulation das Lua-Fenster offen lassen; die MIDI-Erzeugung funktioniert ohne Lua.

**Tipp:** In der Chaos Engine in **MODS** müssen die entsprechenden Spuren als HOST (Typ 7) aktiviert sein. Bei MIDI-CC-Zielen brauchst du die Lua-Brücke nicht.

Weitere Hilfe: [Bedienung](BEDIENUNGSANLEITUNG_DE.md) · [Fehlerbehebung](FEHLERBEHEBUNG_DE.md).

## Updates

Bestehende `LautFunk_MIDI_Chaos_Engine_v1.jsfx` ersetzen, aber vorher eine Sicherung machen. Gleicher Dateiname dient der Projektkompatibilität; vollständige Kompatibilität älterer Szenenspeicher ist noch nicht in REAPER bestätigt.

## Hilfe bei Problemen

Bei Syntaxfehlern die angegebene Zeile und REAPER-Version notieren. Bei Stille: Transport, MIDI-Kanalzuordnung, FX-Reihenfolge und Synthesizer-Audio prüfen. Bei hängenden Noten: Panic/All Notes Off betätigen.
