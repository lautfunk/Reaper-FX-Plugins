# Testplan v1.4.1 BETA – Teiltest durch Anwender gemeldet

- [x] **Anwenderbericht vom 21.11.2026:** Plug-in wurde in REAPER getestet; Rückmeldung: „es funktioniert wunderbar“. Bestätigt das grundsätzliche Laden und Funktionieren im praktischen Einsatz, ohne alle Unterfunktionen einzeln zu belegen.
- [ ] Exakte REAPER-Version und Betriebssystem des Testlaufs dokumentieren; Fehlerfreiheit aller Konfigurationen separat prüfen.
- [ ] Dark-UI in verschiedenen Fenstergrößen und DPI-Skalierungen prüfen; keine Standard-JSFX-Regler sichtbar.
- [ ] GLOBAL NOTE SPEED in Sekunden- und Tempo-Sync-Modus testen; Divisionen, Triolen und punktierte Noten wechseln.
- [ ] Bei 120/140 BPM kontrollieren, ob alle POLYTRANCE-Stimmen mit globaler Geschwindigkeit mitlaufen.
- [ ] MIDI-Ausgabe mit FartSynth und mindestens einem anderen Synth testen.
- [ ] 16:7:5-Phasenverschiebung über 560 Steps prüfen; FLOW-Reset nach 32 Takten unabhängig untersuchen.
- [ ] CHAOS, MUSIC, HYPNOTIC, SUSPENSE, STEP LAB und CASCADE einzeln testen.
- [ ] Wahrscheinlichkeiten, Gate-Längen, Ratchets, MPE-artiges Routing und MIDI-Notenabschaltung prüfen.
- [ ] Lua-Brücke auf Windows, macOS und Linux testen; Host-Parameterzuordnung dokumentieren.
- [ ] Projekt speichern/laden, ältere Szenen importieren, Transport stoppen, Tempo ändern, Panic auslösen.
- [ ] CPU-Auslastung und MIDI-Eventdichte bei extremen Einstellungen prüfen.

**Beta-Status:** Erfolgreicher allgemeiner Praxistest laut Anwender. Alle übrigen Kästchen sind bewusst offen, bis dafür separate Testergebnisse vorliegen. Kein Stable-Release ohne gezielte Regressionstests.
