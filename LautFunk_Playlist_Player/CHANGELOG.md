# Änderungsverlauf – LautFunk Playlist Player & Soundboard

Dieses Changelog unterscheidet bereits veröffentlichte Fassungen von Entwicklungsständen. Ein erfolgreicher CI-Build ist keine öffentliche Freigabe.

## [2.3.0 RC] – in Entwicklung, noch nicht offiziell veröffentlicht

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
- Optionaler OSC-UDP-Listener auf \`127.0.0.1\`, Standardport 9001.
- Einstellbarer Port und Ein/Aus-Schalter im Soundboard.
- Anbindung an Bitfocus Companion/Stream Deck über Generic OSC.
- Separate VST3-ID, damit v2.1 installiert bleiben kann.

## [2.1.0 LIVE DEV] – unter REAPER praktisch getestet

### Neu
- Automatisches, abschaltbares Playlist-Ducking bei Soundboard-Wiedergabe.
- Einstellbare Ducking-Absenkung, Attack und Release.
- MIDI-Steuerung der 24 Pads, Soundbänke und Playlist.
- Soundboard-Ordnerimport für MP3/WAV; bei Bedarf neue Banken.
- Bankimport und -export als \`.lfsb\`.
- Tastaturkürzel für Pads und Stop All.

## [2.0.0 DEV] – erster Soundboard-Entwicklungsstand

### Neu
- Soundboard mit frei benennbaren 24-Pad-Bänken.
- 12er-/24er-Ansicht, One-Shot, Loop, Fades, gleichzeitig laufende Samples.
- Playlist-Gesamt- und Restlaufzeit.
- Eigene Plugin-ID, parallel zum stabilen Playlist Player v1.0.

## [1.0.0] – veröffentlicht als \`playlist-v1.0.0\`

- Ursprünglicher eigenständiger LautFunk Playlist Player VST3 für Windows und macOS.
- MP3/WAV-Wiedergabe, M3U8, Repeat, Shuffle, Titelverwaltung und Lautstärkeregelung.
