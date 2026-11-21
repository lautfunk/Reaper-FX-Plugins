# Musikalische Beispiele – Chaos Engine 61 v1.4.1 BETA

Alle Beispiele sind **Startwerte zum Experimentieren**, keine garantiert unverändert klingenden Presets. Klang und MIDI-Auswertung hängen vom verwendeten Synthesizer ab.

## 1. Hypnotischer Techno / Berlin
- REAPER: **132–140 BPM**, **GLOBAL NOTE SPEED: SYNC → 1/16**.
- **MUSIC → HYPNOTIC**, Genre **BERLIN** oder **TECHNO**, anschließend **APPLY GENRE + 4 LAYERS**.
- Tonalität bewusst reduzieren (z. B. E-Phrygisch, Grundton plus kleine Sekunde und Quinte).
- **STEPS:** Pitch-Länge 7, Gate-Länge 9; mehrere stumme Steps lassen.
- **SUSPENSE:** Orgelpunkt, offene Harmonien, sparsame Ratchets.
- Filter-Cutoff über langsame Modulation bewegen; stabile Grundton-Anker beibehalten.

## 2. Psytrance-Bass und Sequenz
- REAPER: **138–148 BPM**, **SYNC → 1/16**.
- **MUSIC → PSYTRANCE**, Genre anwenden.
- Monophon und kurze Gates für rollenden Bass; der typische Kick–Bass–Bass–Bass-Puls wird erst vollständig, wenn die Kickspur entsprechend programmiert ist.
- Tiefe Grundtöne stabil halten; wenige helle Füllnoten mit geringer Probability.
- Über **CASCADE** nur zurückhaltende melodische Verschiebungen einsetzen.

## 3. Goa / Acid 303
- REAPER: **135–145 BPM**, **SYNC → 1/16** oder gelegentliche 1/32.
- **MUSIC → GOA** bzw. **ACID 303**, Genre anwenden.
- Phrygisch oder harmonisch Moll als Ausgangspunkt, Grundton, Quinte, Halbton-Reibung.
- **SUSPENSE:** Ratchets und Richtungswechsel punktuell einsetzen.
- Für echtes 303-Glide und Resonanzmodulation passende MIDI-CC-Ziele bzw. Host-Parameter über Lua nutzen.

## 4. Uplifting Trance / Arpeggio
- REAPER: **132–140 BPM**, **SYNC → 1/8** oder **1/16**.
- **MUSIC → TRANCE**, Genre anwenden.
- Beispielharmonie in A-Moll: **Am–F–C–G** (i–VI–III–VII), als musikalische Vorstellung.
- Akkord-Voicings, Oktavlagen und Inversionen variieren; in **HYPNO** den Arpeggiator arbeiten lassen.
- Über **CASCADE** langsame Transposition; mit zwei Lead-Stimmen Call & Response ausprobieren.

## 5. Schwebender Ambient
- REAPER: **70–100 BPM**, **SYNC → 1/2**, **1 BAR** oder **SEC → 2–6 Sekunden**.
- **MUSIC → AMBIENT**, Genre anwenden.
- Breite, offene Akkorde: z. B. **Am9 – Fmaj7 – Cadd9 – Gsus2**.
- Notenlängen und Releasestufen am Synthesizer großzügig wählen.
- Modulationsraten eher langsam, geringe Notendichte, unaufdringliche Velocity.
- Hall und Delay sind Effekte des nachgeschalteten Instruments oder Effekt-Routings.

## 6. E-Phrygian 16:7:5 POLYTRANCE
- **140 BPM, SYNC → 1/16**.
- **POLY → LOAD E-PHRYGIAN → POLY RUN**.
- Track 1 = 16 Steps, Track 2 = 7, Track 3 = 5.
- Drei getrennte MIDI-Kanäle bei Mehrinstrument-Routing; Ausgangsinstrumente passend konfigurieren.
- **FLOW → FLOW ON → 560 FREE**: 32-Takt-Arrangement kann sich entfalten, ohne die 35-Takt-Phasenwiederholung zwingend abzuschneiden.
- **MACRO A: PRESSURE** erhöht musikalischen Druck; **MACRO B: SPACE** variiert räumliche Anmutung, sofern CC/FX zugeordnet sind.

> Hinweis: Notennamen und Tempoempfehlungen sind bewusst musikalische Vorschläge; der genaue Klang hängt von Tonart-/Skalenmodus, gewähltem Instrument und weiteren Einstellungen ab.
