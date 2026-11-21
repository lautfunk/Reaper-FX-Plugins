# Fehlerbehebung – MIDI Chaos Engine 61 v1.4.1 BETA

## Das Plug-in erscheint nicht in REAPER
- REAPER-Menü **Options → Show REAPER resource path** öffnen.
- Die JSFX-Datei muss unter `Effects/LautFunk/LautFunk_MIDI_Chaos_Engine_v1.jsfx` liegen, **nicht** im VST3-Ordner und nicht in `Scripts`.
- REAPER neu starten und im FX-Browser nach „MIDI Chaos Engine“ suchen.

## Es ist kein Ton zu hören
- Die Engine produziert **nur MIDI**, kein Audio. Einen Synthesizer **hinter** die Engine in derselben FX-Kette einsetzen.
- Transport starten; Schalter **RUNNING** aktivieren; Panikmodus nicht aktiv lassen.
- Im Instrument MIDI-Kanal/Bus kontrollieren; besonders POLY hat unabhängige MIDI-Kanäle.
- Bei Einsatz mehrerer Instrument-Tracks Routing prüfen.

## Der Tempo-Regler ist nicht zu finden
- **GLOBAL NOTE SPEED** ist dauerhaft oben sichtbar, auf jedem Reiter.
- **SYNC** für musikalische Werte, **SEC** für Sekunden.
- Über **EDIT** bzw. Reiter **SPEED** lassen sich alle Divisionen auswählen.
- Bei unerwarteter Geschwindigkeit unter **ENGINES** die individuellen Multiplikatoren prüfen und bei POLY/FLOW den Faktor **1/2, 1x oder 2x** beachten.

## Das E-Phrygian-Preset läuft nicht
- Unter **POLY** ausdrücklich **LOAD E-PHRYGIAN** anklicken und **POLY RUN** einschalten.
- Unter **FLOW** ggf. **FLOW ON** wählen und Reset-Modus prüfen.
- Sind die drei Zielkanäle am Synthesizer empfangsbereit?

## MIDI-FX-Parameter reagieren nicht
- MIDI-CC benötigt einen Synthesizer mit passender CC-Zuordnung.
- Für andere Hostparameter: **Lua-Brücke** über REAPER Action List starten, **USE SELECTED TRACK** wählen und FX-Parameter zuordnen.
- Auf der **MODS**-Seite muss die Zielspur auf Typ **HOST (7)** stehen. Script offen lassen.

## Noten hängen / hohe Last
- **PANIC** betätigen.
- Ratchets, Polyphonie und Notendichte reduzieren, die Grundgeschwindigkeit erhöhen.
- Bei mehrkanaligem Routing alle beteiligten Instrumente kontrollieren.

## Syntaxfehler / Absturz
- Fehlermeldung, angezeigte Zeile, REAPER-Version und Betriebssystem notieren.
- Prüfen, dass die aktuelle JSFX-Datei und nicht eine ältere v1.0-Datei geladen wurde.
- Fehler bitte als [GitHub Issue](https://github.com/lautfunk/Reaper-FX-Plugins/issues) mit Schritten zur Reproduktion melden.

Siehe auch [Installation](INSTALLATION_DE.md) und [Bedienungsanleitung](BEDIENUNGSANLEITUNG_DE.md).
