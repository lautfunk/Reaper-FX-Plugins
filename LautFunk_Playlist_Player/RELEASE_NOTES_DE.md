# LautFunk Playlist Player & Soundboard v2.3.2

**Kostenloses Open-Source-VST3 für Podcasts, Livestreams, Hörspiele und Musik.**

Der Player kombiniert einen unabhängigen Musik-Playlist-Player mit einem flexiblen Soundboard. Die selbst entwickelten LautFunk-Quellcodes stehen unter der **MIT-Lizenz**; die JUCE-Bibliothek unterliegt ihren eigenen Lizenzbedingungen.

## Neu in v2.3.2 – Zeichenkodierung in der Oberfläche behoben

Die Beschriftung **LAUTSTÄRKE** und weitere Texte mit Umlauten wurden in den bisherigen Versionen gelegentlich falsch als „Ã“ mit Kästchen dargestellt. Ursache war die Interpretation normaler C++-Textliterale als ASCII durch JUCE.

- Alle **17 betroffenen Stellen** in den Plugin-C++-Quellen verwenden jetzt `juce::String::fromUTF8` und explizite, plattformunabhängige UTF-8-Byte-Escapes. Das betrifft auch Menüs, Dateidialoge, Statusmeldungen und Unicode-Symbole.
- Ein automatisierter Regressionstest stellt sicher, dass die UI-Strings sowohl unter Windows als auch unter macOS korrekt kodiert sind.
- Die **VST3-Plugin-ID `LfS3` bleibt erhalten**, ebenso Musik-Playlist, 24-Pad-Soundboard, Ducking, MIDI, OSC und Stereo-/Mehrkanalrouting. Es gibt **keine Änderung der Audioalgorithmen**.
- Die vollständige MIT-Lizenz und `THIRD_PARTY_NOTICES.md` mit Original-MIT-Lizenz und Copyright des Ultraschall Soundboards liegen weiterhin beiden Downloadpaketen bei.
- Die früheren Releases [v2.3.1](https://github.com/lautfunk/Reaper-FX-Plugins/releases/tag/playlist-soundboard-v2.3.1) und [v2.3.0](https://github.com/lautfunk/Reaper-FX-Plugins/releases/tag/playlist-soundboard-v2.3.0) bleiben verfügbar.

## Funktionen

- **Playlist:** WAV/MP3, M3U8 laden und speichern, Play/Pause/Stop, Titelsprung, Shuffle, Repeat, Lautstärkeregelung, Gesamt- und Restlaufzeit.
- **Soundboard:** Beliebig viele Bänke mit jeweils 24 Pads, 12er-/24er-Ansicht, parallele Samples, Loop, Fade, Stop All, Fade All.
- **Ordnerimport:** WAV/MP3-Dateien auf freie Pads verteilen; bei Platzmangel zusätzliche Bänke anlegen.
- **Soundbänke:** Als `.lfsb` importieren/exportieren (Dateipfade, keine eingebetteten Audiodateien).
- **Musik-Ducking:** Optional, ein-/ausschaltbar; Absenkung, Attack und Release regelbar.
- **MIDI:** Sample-Pads und Playlist-Befehle vom Host steuern.
- **OSC / Stream Deck:** Opt-in-Steuerung ausschließlich lokal auf `127.0.0.1`, über Bitfocus Companion (Generic OSC) nutzbar.
- **Audio-Routing:** Standardmäßig gemeinsamer Stereo-Ausgang **1/2** ohne Zusatzkonfiguration. Optional Musik **1/2** und Soundboard **3/4** für Hosts mit Multi-Out-Unterstützung.

## Download und Installation

**Windows x64:** `LautFunk-Playlist-Soundboard-v2.3.2-Windows-x64.zip`

Den enthaltenen VST3-Ordner nach `C:\Program Files\Common Files\VST3\` kopieren und in REAPER oder einer anderen VST3-fähigen DAW scannen.

**macOS Universal (Intel + Apple Silicon):** `LautFunk-Playlist-Soundboard-v2.3.2-macOS-Universal.zip`

Das VST3-Bundle nach `~/Library/Audio/Plug-Ins/VST3/` kopieren. **Wichtig:** Das bereitgestellte macOS-Paket ist lediglich *ad-hoc signiert und nicht Apple-notarisiert*. macOS kann deshalb Sicherheitswarnungen anzeigen oder den Start blockieren.

In **beiden Downloadpaketen** liegen die **deutsche Bedienungsanleitung**, Installations- und Routing-Hilfe, **Changelog**, die LautFunk-**MIT-Lizenz** und **THIRD_PARTY_NOTICES.md** einschließlich des vollständigen ursprünglichen Ultraschall-MIT-Lizenztextes. Die `SHA256SUMS.txt` unter den Release-Dateien enthält die SHA-256-Prüfsummen beider ZIPs.

## Quellcode / Lizenz

Der **vollständige LautFunk-C++-Quellcode** sowie CMake-Konfiguration und Buildskripte liegen im Repository unter `LautFunk_Playlist_Player/`. Von GitHub werden für dieses Release außerdem automatisch die Quellcode-Archive **Source code (zip)** und **Source code (tar.gz)** angeboten.

- **Eigene LautFunk-Quellen:** MIT, siehe `LICENSE`.
- **Ultraschall Soundboard:** Funktionale Inspiration, ursprünglich MIT (Copyright © 2014–2021 Daniel Lindenfelser); vollständige Herkunfts- und Lizenzhinweise unter `THIRD_PARTY_NOTICES.md`.
- **JUCE 9.0.4:** separate JUCE-Lizenz; der Entwickler gibt an, die kostenlose JUCE-Starter-Lizenz zu verwenden. Deren Rechte gehen nicht durch die MIT-Lizenz des LautFunk-Codes auf Dritte über.
- **Bitfocus Companion / Stream Deck:** keine offizielle Partnerschaft.

## Bekannte Grenzen

- Samples und Musik werden ausschließlich über **Dateipfade** referenziert; verschobene Dateien müssen neu zugewiesen werden.
- Mehrere laute Samples können clippen: noch **kein eingebauter Summen-Limiter** und kein LUFS-Auto-Abgleich. Für Livestreams die Summe begrenzen.
- Ducking betrifft die **Playlist**, nicht Mikrofone; kein Mikrofon-Sidechain-Ducking.
- OSC nur lokal, standardmäßig deaktiviert; **kein bidirektionales Stream-Deck-Feedback**.
- Optionaler Ausgang 3/4 muss in der DAW hörbar geroutet werden, sonst bleiben Samples auf diesem Ausgang stumm; bei Bedarf auf Standard-Stereo zurückschalten.
- Windows-Funktion in REAPER einschließlich finaler Plugin-ID vom Betreiber getestet; andere Hosts und macOS sollten gesondert geprüft werden.
- Wegen der neuen stabilen Plugin-ID werden frühere DEV-Versionen in bestehenden DAW-Projekten **nicht automatisch ersetzt**.

## Hilfe und Feedback

Bitte Fehler mit Betriebssystem, DAW-Version, Plugin-Version, Routing-Modus und reproduzierbaren Schritten als [GitHub Issue](https://github.com/lautfunk/Reaper-FX-Plugins/issues) melden. Die [ausführliche Dokumentation](https://github.com/lautfunk/Reaper-FX-Plugins/blob/main/LautFunk_Playlist_Player/README_DE.md) und der [Testplan](https://github.com/lautfunk/Reaper-FX-Plugins/blob/main/LautFunk_Playlist_Player/DOKUMENTATION/TESTPLAN_DE.md) stehen im Repository.

**Veröffentlichung:** kostenlos und quelloffen. Keine Garantie oder Gewährleistung über die MIT-Lizenz hinaus.
