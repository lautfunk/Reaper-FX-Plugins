# Änderungsverlauf – LautFunk Playlist Player & Soundboard

Dieses Changelog unterscheidet bereits veröffentlichte Fassungen von Entwicklungsständen. Ein erfolgreicher CI-Build ist keine öffentliche Freigabe.

## [2.3.2] – Korrektur der Zeichenkodierung in der Plugin-Oberfläche

- Behoben: Bei Beschriftungen mit Umlauten, etwa **LAUTSTÄRKE**, wurden statt Ä/ä/ö/ü teilweise **Ã** und ein Kästchen angezeigt.
- Alle **17 betroffenen Unicode-Textliterale** in `PluginEditor.cpp`, `PluginProcessor.cpp` und `OscControl.cpp` explizit als UTF-8 mit compilerunabhängigen Byte-Escapes an `juce::String::fromUTF8` übergeben.
- Ein automatisierter UTF-8-Regressionstest überwacht Sonderzeichen, Textbeschriftungen und Symbole auf beiden Plattformen.
- **Keine Änderung an DSP, Audio-Routing, MIDI, OSC oder Plugin-ID.** Die stabile VST3-ID `LfS3` bleibt wie in v2.3.0 und v2.3.1.
- Windows x64 und macOS Universal weiterhin mit MIT-Lizenz und Original-Ultraschall-Herkunftshinweisen im ZIP.

## [2.3.1] – Wartungsrelease: Herkunft und Dokumentation

- **Kein neuer Funktionsumfang und keine Änderungen an den Audio-Algorithmen.** Weiterhin dieselbe VST3-Plugin-ID `LfS3` wie bei v2.3.0.
- Die Windows- und macOS-ZIP-Pakete enthalten jetzt `THIRD_PARTY_NOTICES.md` einschließlich der ursprünglichen MIT-Lizenz des Ultraschall Soundboards (Copyright © 2014–2021 Daniel Lindenfelser).
- Veröffentlichungsstatus, Installationshinweise, Testplan und Herkunftsnachweis konsistent aktualisiert.
- Offizieller Release mit Windows-x64- und macOS-Universal-Builds sowie SHA-256-Prüfsummen. Die macOS-Ausgabe bleibt ad-hoc signiert und nicht Apple-notarisiert.

## [2.3.0] – stabile Veröffentlichung

- Getestete Playlist-/Soundboard-Funktionen, optionale Ausgangsbusse, MIDI und OSC.
- Windows-x64- und macOS-Universal-VST3, deutsche Dokumentation, vollständiger Quellcode und MIT-Lizenz.
- Endgültige Plugin-ID für zukünftige Updates; frühere Entwicklerfassungen bleiben eigenständige Plugins.

## [2.3.0-rc1] – geprüfter Release-Kandidat

- VST3 mit künftig dauerhaftem Produktnamen `LautFunk Playlist Player & Soundboard` und eigener Plugin-ID vorbereitet.
- Veröffentlichungs-Pakete mit deutscher Anleitung, Versionshistorie, MIT-Lizenz und SHA-256-Prüfsummen vorgesehen.
- VST3-Dateiname auf `LautFunk Playlist Soundboard.vst3` vereinfacht (macOS-Shell-Kompatibilität); DAW-Anzeigename bleibt `LautFunk Playlist Player & Soundboard`.

### Routing-Funktionen (übernommen aus v2.3 RC)

### Neu
- **Optionales, getrenntes Stereo-Routing**: Playlist über Out 1/2, Soundboard über Out 3/4.
- **AUDIO-ROUTING**-Menü zur Wahl zwischen **Standard: gemeinsamer Stereo-Mix** und **Erweitert: getrennte Ausgänge**.
- Zweiter VST3-Ausgang standardmäßig deaktiviert; wenn die DAW das Aktivieren verweigert, bleibt der Stereo-Mix erhalten.
- Statusanzeige und Hinweise, dass der zweite Ausgang in der DAW hörbar geroutet werden muss.
- Deutsche Installations-, REAPER-Routing-, Test- und Release-Dokumentation.

### Technische Einschränkungen
- Ein aktivierter zweiter Ausgang kann trotz erfolgreicher Busaktivierung in der DAW unverbunden sein. Hier kann der Benutzer zum Stereo-Mix zurückschalten.
- Keine automatische Prüfung des physischen DAW-Routings.
- Keine Notarisierung des macOS-Testpakets.
- Eigenständige RC-Plugin-ID; keine automatische Migration älterer Plugin-Instanzen.

## [2.2.0 OSC DEV] – Entwicklerbuild

### Neu
- Lokale OSC-Steuerung für Soundboard-Pads, Bankwechsel, Playlist und Ducking.
- Optionaler OSC-UDP-Listener auf `127.0.0.1`, Standardport 9001.
- Einstellbarer Port und Ein/Aus-Schalter im Soundboard.
- Anbindung an Bitfocus Companion/Stream Deck über Generic OSC.
- Separate VST3-ID, damit v2.1 installiert bleiben kann.

## [2.1.0 LIVE DEV] – unter REAPER praktisch getestet

### Neu
- Automatisches, abschaltbares Playlist-Ducking bei Soundboard-Wiedergabe.
- Einstellbare Ducking-Absenkung, Attack und Release.
- MIDI-Steuerung der 24 Pads, Soundbänke und Playlist.
- Soundboard-Ordnerimport für MP3/WAV; bei Bedarf neue Banken.
- Bankimport und -export als `.lfsb`.
- Tastaturkürzel für Pads und Stop All.

## [2.0.0 DEV] – erster Soundboard-Entwicklungsstand

### Neu
- Soundboard mit frei benennbaren 24-Pad-Bänken.
- 12er-/24er-Ansicht, One-Shot, Loop, Fades, gleichzeitig laufende Samples.
- Playlist-Gesamt- und Restlaufzeit.
- Eigene Plugin-ID, parallel zum stabilen Playlist Player v1.0.

## [1.0.0] – veröffentlicht als `playlist-v1.0.0`

- Ursprünglicher eigenständiger LautFunk Playlist Player VST3 für Windows und macOS.
- MP3/WAV-Wiedergabe, M3U8, Repeat, Shuffle, Titelverwaltung und Lautstärkeregelung.
