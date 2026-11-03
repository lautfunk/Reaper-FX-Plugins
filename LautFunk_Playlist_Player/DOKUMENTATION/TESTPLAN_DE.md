# Testplan – stabile v2.3-Produktlinie (v2.3.1)

Die v2.3.0-Funktionen wurden vom Projektbetreiber in REAPER getestet und freigegeben. **v2.3.1 enthält nur Versions-, Dokumentations- und Paketänderungen; die Audio-Algorithmen und die Plugin-ID bleiben unverändert.** Ein grüner GitHub-Actions-Build bestätigt die Kompilierung und die verpackten Dateien, aber nicht alle Praxis- oder Sicherheitsfälle. Die nachfolgende Liste ist ein wiederverwendbarer Prüfplan; nicht abgehakte Punkte sind keine behaupteten abgeschlossenen Tests.

## A. Automatisierte Builds

- [ ] Windows x64 mit Visual Studio 2022 und JUCE 9.0.4 kompiliert.
- [ ] macOS Universal kompiliert; `lipo` bestätigt `arm64` und `x86_64`.
- [ ] Beide VST3-ZIP-Dateien als CI-Artefakte vorhanden.
- [ ] ZIP-Dateien enthalten das erwartete VST3-Bundle und die dokumentierten Lizenz-, Herkunfts- und Handbuchdateien.
- [ ] Versionsname und Plugin-ID sind passend zur geplanten Freigabe.
- [ ] SHA256-Prüfsummen der Freigabe-Dateien dokumentiert.

## B. Basisfunktion

- [ ] Plugin in frischem REAPER-Projekt ohne Fehlermeldung öffnen.
- [ ] Ein Sample starten, ohne dass die REAPER-Timeline läuft; Host-Audio-Verarbeitung bei Stop prüfen.
- [ ] WAV, MP3 und M3U8 laden; Playlist importieren/exportieren.
- [ ] Pause, Stop, Next/Previous, Seek, Repeat-Modi und Shuffle testen.
- [ ] Restlaufzeit und Gesamtdauer mit mehreren Titeln vergleichen.
- [ ] Funktion nach Projekt speichern, schließen und neu öffnen prüfen.
- [ ] Fehlende/verschobene Dateien erzeugen keinen Absturz.

## C. Soundboard

- [ ] 24 Pads in einer Bank befüllen.
- [ ] 12er-Ansicht: alle 24 Slots über Seite 1 und 2 erreichbar.
- [ ] 24er-Ansicht: alle 24 Slots vorhanden.
- [ ] Mehrere Samples gleichzeitig starten und stoppen; max. 24 Stimmen beachten.
- [ ] Zwischen Banken wechseln, ohne laufende Samples abzubrechen.
- [ ] Loop, Einzelsample-Fade, Fade All und Stop All testen.
- [ ] Ordner mit 30 Dateien importieren: zusätzliche Bank, keine Überschreibung vorhandener Pads.
- [ ] `.lfsb` exportieren/importieren und Audio-Dateipfade prüfen.

## D. Ducking

- [ ] Ducking EIN: Musik wird während Samples leiser.
- [ ] Ducking AUS: Musik bleibt beim Sample unverändert.
- [ ] Attack 1/35/500 ms und Release 20/650/3000 ms sinnvoll hörbar.
- [ ] Tiefe 0/12/30 dB; keine abrupten Pegelsprünge.
- [ ] Ducking nur auf Musik, nicht auf die Samples.
- [ ] Zustand bleibt nach Speichern und Wiederöffnen erhalten.

## E. MIDI / OSC

- [ ] MIDI Note 36 startet Pad 1, Note 59 Pad 24.
- [ ] MIDI Note 60/84 stoppt/fadet Pad 1.
- [ ] Bankwechsel und Playlistbefehle per MIDI funktionieren.
- [ ] OSC standardmäßig AUS.
- [ ] OSC lokal EIN: UDP 127.0.0.1:9001; Companion-Taste löst Sample aus.
- [ ] OSC-Bankwechsel und Ducking-Befehl funktionieren.
- [ ] Bei zwei Plugin-Instanzen mit gleichem OSC-Port erscheint nachvollziehbare Meldung.
- [ ] OSC nach Ausschalten nicht mehr erreichbar.
- [ ] Kein unerwarteter Netzwerk-Listener auf 0.0.0.0 oder fremden Interfaces.

## F. NEU: Audioausgänge

**Zuerst in einem Testprojekt, nicht in einer Live-Sendung.**

- [ ] Ohne Änderungen: **Stereo-Mix aktiv**, Musik und Soundboard gemeinsam auf 1/2.
- [ ] Getrennt-Modus wählbar, wenn REAPER Spur mit 4 Kanälen und zweiten VST3-Bus bereitstellt.
- [ ] Im getrennten Modus Musik ausschließlich über 1/2.
- [ ] Im getrennten Modus Samples ausschließlich über 3/4.
- [ ] Kein doppeltes Sample auf 1/2.
- [ ] Soundboard kann via REAPER Receive 3/4 → 1/2 separat gemischt werden.
- [ ] Ducking funktioniert auch bei getrennten Ausgängen.
- [ ] Beim Wechsel zurück auf Standard sind beide Quellen wieder auf 1/2.
- [ ] Ohne verfügbaren zweiten Bus wird nicht versehentlich Stille ausgegeben.
- [ ] **Grenzfall:** Bus aktiviert, aber nicht geroutet – der Warnhinweis erscheint.
- [ ] Mehrfach zwischen beiden Modi umschalten (inkl. während Sample aktiv), ohne Absturz.
- [ ] Routingzustand mit Projekt speichern und wiederherstellen; nach Host-Neuladen erneut prüfen.
- [ ] Mehr als eine Plugin-Instanz in einem Projekt getestet.

## G. Weitere Host- und Performanceprüfungen

- [ ] Windows x64 REAPER getestet.
- [ ] macOS Intel und/oder Apple Silicon tatsächlich getestet; beide Architekturen kompiliert allein reicht nicht.
- [ ] Mindestens eine weitere DAW unter Windows oder macOS auf Stereo getestet.
- [ ] Zweite DAW nur als Multi-Output-kompatibel deklarieren, wenn Routing dort tatsächlich geprüft.
- [ ] CPU und Audio-Dropouts bei 24 gleichzeitigen Samples kontrolliert.
- [ ] Wechsel der Samplerate (44,1/48/96 kHz) und Puffergrößen (64/256/1024) ohne Absturz.
- [ ] Ausgeblendete Sample-Voices geben Ressourcen wieder frei.
- [ ] Summe auf Clipping prüfen und in Anleitung auf externe Limiter hinweisen.

## H. Lizenz / Download / Freigabe

- [ ] JUCE-9-Starter-Lizenz berechtigt alle tatsächlichen JUCE-Framework-Entwickler.
- [x] MIT-Lizenz für eigenen LautFunk-Code vom Betreiber bestätigt; vollständige `LICENSE` im Plugin-Verzeichnis vorhanden.
- [ ] `THIRD_PARTY_NOTICES.md` enthält die ursprüngliche MIT-Lizenz des Ultraschall Soundboards einschließlich Copyright (c) 2014–2021 Daniel Lindenfelser; weitere Drittrechte und Marken geprüft.
- [ ] README, Installation und REAPER-Routing-Anleitung entsprechen dem finalen Binary.
- [ ] GitHub-Release-Tag und Download-Artefakte passen zu Version und Plugin-ID.
- [ ] ZIPs mit `LICENSE`, `THIRD_PARTY_NOTICES.md`, Handbuch und Changelog veröffentlicht; SHA256SUMS.txt auf beide ZIP-Dateien geprüft.
- [ ] Beim macOS-Paket tatsächlichen Signierungs-/Notarisierungsstand dokumentiert.
- [ ] Update-/Rückfallanleitung und bekannte Einschränkungen enthalten.

## Fehlerbericht-Vorlage

```text
Plugin-Version / GitHub-Commit:
Windows/macOS-Version:
REAPER-Version / andere DAW:
Sample-Rate und Buffer:
Stereo-Mix oder getrennte Ausgänge:
Anzahl REAPER-Spurkanäle:
Schritte zum Reproduzieren:
Erwartetes Ergebnis:
Tatsächliches Ergebnis:
Screenshot / Log:
```
