# Bedienungsanleitung – LautFunk MIDI Chaos Engine 61 v1.4.1 BETA

## 1. Was ist das Plug-in?
Die **MIDI Chaos Engine 61** ist ein generatives MIDI-JSFX für **REAPER**. Es erzeugt Noten, rhythmische Muster, Velocity- und Modulationsdaten. **Kein eigener Klang:** Setze dahinter einen Synthesizer, z. B. LautFunk FartSynth 61 oder ein anderes Instrument. Die dunkle LautFunk-Oberfläche ersetzt die normalen JSFX-Regler; REAPERs eigene FX-Fensterleiste bleibt erhalten.

**Getesteter Stand:** Der Anwender hat am 21.11.2026 gemeldet, dass die v1.4.1 in REAPER funktioniert. Nicht jede hier aufgeführte Unterfunktion wurde einzeln nachgewiesen. [Testplan](TESTPLAN_DE.md).

## 2. Schnellstart in fünf Schritten
1. Eine REAPER-Spur anlegen, **MIDI Chaos Engine → Synthesizer** als FX-Reihenfolge wählen.
2. Den Transport starten. Im Plug-in gegebenenfalls oben **RUNNING** aktivieren.
3. In der immer sichtbaren Kopfleiste **GLOBAL NOTE SPEED → SYNC → 1/16** wählen.
4. Unter **MUSIC** einen Modus wählen oder unter **POLY** mit **LOAD E-PHRYGIAN** starten.
5. Am Synthesizer kontrollieren, ob die benötigten MIDI-Kanäle empfangen werden. Für sofortiges Stoppen **PANIC** verwenden.

## 3. Dauerhaft sichtbare obere Leiste
- **GLOBAL NOTE SPEED:** Hauptsteuerung für den zeitlichen Abstand neuer Noten. Ist auf jedem der 14 Reiter sichtbar.
- **SYNC:** Geschwindigkeit aus REAPER-BPM plus einem Notenwert (z. B. 1/8, 1/16, 1/32).
- **SEC:** Freies Intervall in Sekunden unabhängig vom musikalischen Notenraster.
- **− / +:** Geschwindigkeitseinstellung schrittweise ändern.
- **Wertfeld:** Direkte Einstellung des aktuellen Werts per Maus.
- **EDIT:** Öffnet die ausführliche Seite **SPEED**.
- **RUNNING / STOPPED:** MIDI-Generierung aktivieren oder anhalten.
- **RESEED:** Zufallsfolgen neu initialisieren.
- **PANIC:** Laufende Noten abschalten; hilft gegen hängende MIDI-Noten.

Bei **SYNC** richtet sich die Clock nach dem Projekttempo. Bei **SEC** wird ein absoluter Zeitabstand verwendet. Die einzelnen Engines können eigene Multiplikatoren haben; ihre individuellen Werte beeinflussen die tatsächlich gehörten Notenabstände.

## 4. SPEED: Sekunden, BPM und Notenteilung
Auf **SPEED** kann man zwischen **SECONDS** und **SYNC TO TEMPO** umschalten. Der Regler **NOTE INTERVAL (SECONDS)** reicht von 0,05 bis 8 Sekunden. Bei Tempo-Sync gibt es folgende Raster:

| Auswahl | Rhythmus |
| --- | --- |
| 4 BARS / 2 BARS / 1 BAR | Mehrere Takte bzw. ein Takt je Grundschritt |
| 1/2, 1/4, 1/8, 1/16, 1/32, 1/64 | Binäre Notenteilungen |
| 1/8 T, 1/16 T, 1/32 T | Triolen |
| 1/8 D, 1/16 D, 1/32 D | Punktierte Noten |

Beispiel **140 BPM, 1/16**: Grundschritt rund 107 ms (60/140/4). **1/8** ist doppelt so lang, **1/32** halb so lang. Unter **ENGINES** wird pro Engine ein Geschwindigkeitsmultiplikator eingestellt: **Steps/beat 4 = 1×, 8 = 2×, 2 = 0,5×** (siehe Anzeige im SPEED-Reiter).

## 5. Die 14 Reiter

| Reiter | Aufgabe |
| --- | --- |
| **HOME** | Überblick und zentrale Generator-Einstellungen / Chaos-Autopilot |
| **ENGINES** | Vier eigenständige Erzeuger, Rhythmik, Dichte, Polyrhythmik |
| **MODS** | 16 Modulationsspuren, MIDI-CC, Pitch, Pressure, RPN/NRPN, HOST-Lua |
| **KEYS** | 61-Tasten-Wahrscheinlichkeitsmatrix |
| **ROUTING** | MIDI-Bus, Kanalverteilung und MIDI-Eingang |
| **SCENES** | Speicherung/Abruf und Übergang zwischen Szenen |
| **SPEED** | Globale Geschwindigkeit in Sekunden oder Tempowerten |
| **MUSIC** | CHAOS/MUSIC/HYBRID/HYPNOTIC, Genre, Tonart, Akkorde, Voicings |
| **HYPNO** | Hypnotische Motive, Evolution, Arpeggios und Phrasen |
| **STEPS** | Polymetrische Pitch-/Gate-Patterns und programmierbare Steps |
| **CASCADE** | Langsame Transposition und harmonische Spannung |
| **SUSPENSE** | Offene Harmonien, Orgelpunkt, phrygische Reibung, Kanon, Ratchets |
| **POLY** | Drei getrennte MIDI-Spuren, E-Phrygisch 16:7:5, Step-Bearbeitung |
| **FLOW** | Acht editierbare Abschnitte zu je vier Takten, Makros, Phasenverwaltung |

## 6. CHAOS, MUSIC, HYBRID und HYPNOTIC
Im Reiter **MUSIC** sind diese vier Spielweisen direkt wählbar:
- **CHAOS:** Zufällige und mathematisch-chaotische Muster.
- **MUSIC:** Harmonisch orientierte Tonwahl und Akkorde.
- **HYBRID:** Musikalische Struktur mit kontrollierter Abweichung.
- **HYPNOTIC:** Kleine, wiedererkennbare Motive mit langsamer Variation.

Dort kannst du die Genres **FREE, TECHNO, TRANCE, GOA, PSYTRANCE, AMBIENT, ACID 303, BERLIN** auswählen. Die Auswahl des Genres allein reicht nicht: Erst **APPLY GENRE + 4 LAYERS** aktiviert die vorgeschlagene vierstimmige Struktur (Bass, Arp, Lead, Pad auf MIDI-Kanälen 1–4). Nicht jede Synthesizer-Instanz kann mehrere Kanäle gleichzeitig mit unterschiedlichen Sounds spielen.

Weitere Musikfelder: **KEY MODE, PROGRESSION, BARS / CHORD, CHORD COUNT, CHORD QUALITY, VOICING, INVERSION, COMPLEXITY, HARMONIC SURPRISE, OCTAVE MOVES, ADD 9TH**. Bei der Wahl sehr komplexer Akkorde auf ein passendes polyphones Zielinstrument achten.

## 7. Hypnotische Sequenzen und Akkordarbeit
- **HYPNO:** Wähle Motivbewegung, Phrasen-Evolution und Arpeggio-Verhalten.
- **STEPS:** Getrennte Pitch- und Gate-Längen ermöglichen 7:9- oder 5:7-Polymetrik.
- **CASCADE:** Ein langsamer Transpositionslauf verschiebt das schnelle Motiv; Tonleitern und harmonische Quantisierung beeinflussen die Wirkung.
- **SUSPENSE:** Statt klassischer Kadenzen bevorzugt diese Seite offene Sus-/Quart-Harmonien und Tonalität mit geringem Auflösungsdruck.

Nicht jeder Parameter wirkt in jeder Betriebsart. Bei einem unerwarteten Ergebnis zuerst den Modus und die Aktivierungs-Schalter des betreffenden Bereichs kontrollieren.

## 8. POLYTRANCE: drei Spuren mit 16:7:5
Auf **POLY** die Schaltfläche **LOAD E-PHRYGIAN** betätigen und **POLY RUN** aktivieren. Die Preset-Tonleiter ist **E–F–G–A–B–C–D**. Die drei Spuren sind:
1. **TRACK 1 / ANCHOR:** 16 Steps mit tiefem E-Orgelpunkt und phrygischer Spannung.
2. **TRACK 2 / 7-STEP:** Eine siebenschrittige Gegenstimme.
3. **TRACK 3 / 5-STEP:** Kurze, höhere Akzente.

Die Muster treffen sich nach **kgV(16,7,5) = 560 Sechzehnteln = 35 Takten im 4/4-Takt**, solange alle drei Spuren im selben 16tel-Raster laufen und nicht vorzeitig zurückgesetzt werden. Unter **POLY** gibt es zusätzlich **REFERENCE, DRIFT, SPIRAL, SHADOW, GOA 3+3+2, AMBIENT ORBIT und E-GRAVITY**.

**MIDI-Kanäle:** Die drei Stimmen können auf getrennten Kanälen liegen. Für drei unterschiedliche Instrumente in REAPER gegebenenfalls MIDI-Routing auf getrennte Tracks einrichten.

## 9. FLOW: 32 Takte Arrangement
**FLOW** ist ein unabhängiger 32-Takt-Arrangementplan mit acht Phasen: Takte 1–4, 5–8, …, 29–32. Pro Phase sind u. a. **Cutoff, Presence, Space/Send, Tension, Track 1 Length und Track 2 Transpose** einstellbar. Darüber hinaus:
- **MACRO A: PRESSURE:** Dichte/Druck-Charakter.
- **MACRO B: SPACE:** räumliche Veränderung.
- **560 FREE:** Polymetrische Phase läuft frei weiter.
- **32-BAR RESET:** gezielter Neustart nach 32 Takten.
- **CC OUTPUT ON/OFF:** Versand von MIDI-CC an einen passend zugeordneten Synthesizer.
- **1/2 SPEED, 1x SPEED, 2x SPEED:** zusätzlicher Geschwindigkeitsfaktor für POLY.
- **PHRYGIAN LOCK:** Bindung an das verwendete Tonmaterial.

**Wichtig:** 32 Takte Arrangement und 35 Takte voller 16:7:5-Polymeter-Zyklus sind bewusst unterschiedliche Perioden. **560 FREE** ermöglicht die lange Überlagerung.

## 10. MODS und optionale Lua-Brücke
Im Reiter **MODS** können Modulationsspuren MIDI-Nachrichten erzeugen. **HOST (Typ 7)** steuert dagegen erst über die gesonderte Lua-Brücke einen REAPER-FX-Parameter.

Für HOST-Modulation:
1. ReaScript nach [Installationsanleitung](INSTALLATION_DE.md) einrichten.
2. Auf der Zielspur das Script ausführen, **USE SELECTED TRACK** wählen.
3. Bis zu 16 Lanes einem Ziel-FX und Parameter zuordnen; für den FartSynth steht **AUTO-MAP FARTSYNTH** zur Verfügung.
4. Lua-Fenster während dieser Art von Steuerung geöffnet lassen.

MIDI-CC, Pitch-Bend und Pressure funktionieren nur, wenn das angeschlossene Instrument die Nachrichten auswertet. Ein per MIDI gesendetes Glide/Portamento benötigt ein kompatibles Zielinstrument.

## 11. Szenen und Speicherung
Mit **SCENES** kannst du unterschiedliche Konfigurationen anlegen und zwischen ihnen wechseln. REAPER-Projekte vor großen Änderungen speichern. Bei Upgrades dieselbe JSFX-Datei ersetzen, aber vorher ein Backup der alten Datei und des Projekts anlegen; vollständige Kompatibilität aller früheren Szenen ist nicht separat getestet.

## 12. Sicherheits- und Performance-Hinweise
- Bei unerwartetem Tonhalten **PANIC** verwenden und Synthesizer-MIDI-Zuweisungen prüfen.
- Extrem kurze Notenabstände plus Ratchets können große MIDI-Ereignismengen erzeugen.
- Bei mehrkanaligem POLY-Routing auf die passenden Kanalempfänger achten.
- Die Engine erzeugt MIDI: Delay, Hall, echtes Audio-Gating und Klangformung stammen aus dem angeschlossenen Instrument bzw. nachfolgenden Effekten.

Weitere Dokumente: [Beispiele](BEISPIELE_PRESETS_DE.md) · [Fehlerbehebung](FEHLERBEHEBUNG_DE.md) · [Tests](TESTPLAN_DE.md).
