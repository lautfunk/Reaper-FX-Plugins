# LautFunk Playlist Player & Soundboard

**Stabile Veröffentlichung v2.3.0 · Kostenlos · Open Source (MIT).**

Dauerhafter Download: [GitHub Release v2.3.0](https://github.com/lautfunk/Reaper-FX-Plugins/releases/tag/playlist-soundboard-v2.3.0).

VST3-Name der vorgesehenen stabilen Produktlinie: **LautFunk Playlist Soundboard.vst3**. Angezeigter Plugin-Name in der DAW: **LautFunk Playlist Player & Soundboard**. Dieses neue Plugin hat eine eigene, langfristig beizubehaltende Plugin-ID und kann neben den bisherigen DEV-/RC-Versionen installiert werden.

Ein VST3 für Podcasts, Livestreams und Musikprogramme: Playlist und Soundboard in einem Plugin, ohne den DAW-Transport zwingend starten zu müssen. Entwickelt mit **C++17, JUCE 9.0.4 und CMake**.

> **Sicherer Standard:** Beim ersten Start laufen Playlist und Soundboard gemeinsam über den **Stereoausgang 1/2**. Zusätzliche Kanäle, externes Routing, OSC oder ein Stream Deck sind nicht erforderlich.

## Einstieg

- [Windows/macOS installieren](DOKUMENTATION/INSTALLATION_DE.md)
- [REAPER: Stereo-Modus und optionales Routing auf 3/4](DOKUMENTATION/REAPER_ROUTING_DE.md)
- [Systematische Tests vor einer Veröffentlichung](DOKUMENTATION/TESTPLAN_DE.md)
- [Release-Checkliste und GitHub-Veröffentlichung](DOKUMENTATION/RELEASE_CHECKLIST_DE.md)
- [MIT-Lizenz (LautFunk-eigene Quellen)](LICENSE) und [JUCE-/Drittanbieter-Lizenzhinweise](DOKUMENTATION/RECHT_LIZENZEN_DE.md)
- [Änderungsverlauf](CHANGELOG.md)

## Funktionsumfang

### Playlist

- WAV/MP3 laden, abspielen, pausieren, stoppen, Titel vor/zurück, Spulen.
- M3U8 importieren/exportieren, Titel entfernen und Reihenfolge verändern.
- Repeat aus / ganze Liste / ein Titel und Shuffle.
- Gesamtspielzeit, Restzeit des Durchlaufs und Fortschrittsanzeige; unbekannte Längen als Näherung.
- Unabhängige Playlist-Lautstärke.

### Soundboard

- Beliebig viele **Soundbänke mit je 24 Pads**.
- Umschaltbare Ansichten: 12 große Pads auf zwei Seiten oder 24 kompakte Pads.
- WAV und MP3 pro Pad, gleichzeitiges Abspielen mehrerer Samples (Engine-Limit 24 Stimmen).
- One-Shot, Loop, individuelle Pad-Pegel und Fade-Out.
- STOP ALL, FADE ALL, Stop/Fade für einzelne Pads.
- **Ordner importieren:** WAV-/MP3-Dateien des ausgewählten Ordners alphabetisch auf freie Pads verteilen; bei Bedarf weitere Soundbänke anlegen. Belegte Pads bleiben unverändert. Keine automatische Unterordnersuche.
- **Bank-Datei:** Bank-Konfiguration als `.lfsb` speichern oder laden. Die Dateien enthalten **Pfade**, nicht das Audiomaterial selbst.

### Ducking

**Musik-Ducking** im Soundboard ein- oder ausschalten. Wenn ein Sample läuft, wird die **Playlist-Musik** abgesenkt und anschließend weich wieder angehoben. Die Samples bleiben unverändert.

- Absenkung: **0–30 dB**, Standard 12 dB.
- Attack: **1–500 ms**, Standard 35 ms.
- Release: **20–3000 ms**, Standard 650 ms.

**Kein Mikrofon- oder Sidechain-Ducking** – das ist eine andere, noch nicht implementierte Funktion.

### Optionale Audioausgänge – NEU in v2.3 RC

Über die Schaltfläche **AUDIO-ROUTING** im oberen Bereich:

| Modus | Playlist | Soundboard | Zusätzliche Einrichtung |
| --- | --- | --- | --- |
| **Standard: Stereo-Mix** | Out 1/2 | Out 1/2 | Nein |
| **Erweitert: Getrennt** | Out 1/2 | Out 3/4 | Ja, nur wenn DAW weitere Ausgänge unterstützt |

Der zweite Stereo-Bus ist standardmäßig deaktiviert. Wenn ihn der Host nicht aktiviert, wird der gemeinsame Stereo-Mix beibehalten. **Wichtig:** Ein aktivierter Bus ist nicht automatisch auf eine hörbare Spur geroutet. Wenn der Soundboard-Ton nach dem Umschalten fehlt, in der DAW Ausgang 3/4 zuweisen oder auf **Standard** zurückschalten.

Ducking funktioniert in beiden Modi, da es vor der Trennung auf die Playlist angewendet wird. Bei getrennten Ausgängen wird das Soundboard **nicht gleichzeitig auf Out 1/2 gespiegelt**, um Doppelungen zu vermeiden.

### MIDI

MIDI-Nachrichten aus der DAW steuern die aktuelle Soundbank:

| Ereignis | Aktion |
| --- | --- |
| Note 36–59 | Pads 1–24 starten |
| Note 60–83 | Pads 1–24 stoppen |
| Note 84–107 | Pads 1–24 ausblenden |
| Program Change 0–N | Bank nach Index auswählen |
| CC 110 / 111 (Wert mindestens 64) | Bank vorherige / nächste |
| CC 112 / 113 | Stop All / Fade All |
| CC 114–117 | Playlist Play/Pause, nächster/vorheriger Titel, Stop |

MIDI-Noten werden über ihre **Notennummer** angegeben; Oktavnamen unterscheiden sich je nach DAW. MIDI-Steuerung ist nicht samplegenau.

### Lokale OSC-/Stream-Deck-Steuerung

OSC im Soundboard über **OSC lokal** aktivieren. Standard: `127.0.0.1:9001` per UDP. Die Funktion ist zunächst **aus** und nur auf demselben Rechner erreichbar. Bei mehreren gleichzeitig aktivierten Plugin-Instanzen muss jede einen eigenen Port erhalten.

Mit **Bitfocus Companion → Generic OSC** kann ein Stream Deck beispielsweise:

| OSC-Adresse | Argument | Wirkung |
| --- | --- | --- |
| `/lautfunk/pad/trigger` | Integer 1–24 | Sample starten |
| `/lautfunk/pad/stop` | Integer 1–24 | Sample sofort stoppen |
| `/lautfunk/pad/fade` | Integer 1–24 | Sample ausblenden |
| `/lautfunk/bank/next` | keines | Nächste Bank |
| `/lautfunk/bank/previous` | keines | Vorherige Bank |
| `/lautfunk/bank/select` | Integer 1–N | Bank nach Position wählen |
| `/lautfunk/all/stop` | keines | Alle Samples stoppen |
| `/lautfunk/all/fade` | keines | Alle Samples ausblenden |
| `/lautfunk/playlist/play` | keines | Playlist starten |
| `/lautfunk/playlist/pause` | keines | Playlist pausieren |
| `/lautfunk/playlist/toggle` | keines | Play/Pause umschalten |
| `/lautfunk/playlist/stop` | keines | Playlist stoppen |
| `/lautfunk/playlist/next` | keines | Nächster Titel |
| `/lautfunk/playlist/previous` | keines | Vorheriger Titel |
| `/lautfunk/duck/enable` | Integer 0 / 1 | Ducking aus / ein |
| `/lautfunk/duck/depth` | Float 0–30 | Ducking-Absenkung |

Beispiel für Pad 1: Adresse `/lautfunk/pad/trigger`, OSC-Typ **Integer**, Wert **1**.

Derzeit **keine OSC-Rückmeldung** an Stream-Deck-Tasten und keine Steuerung über das LAN; ein direkter Elgato-Plugin-Treiber ist nicht enthalten.

### Tastatur

Bei fokussiertem Soundboard: Tasten **1–0, - und =** für die zwölf sichtbaren Pads, **Bild hoch/runter** für Bankwechsel und **Escape** für STOP ALL. Das hängt von der Tastaturweiterleitung der DAW ab.

## Projekte, Dateipfade und Datensicherung

Die VST3-Einstellungen werden mit der DAW-Projektdatei gespeichert. Audio wird **nicht** ins Projekt eingebettet; verschobene WAV/MP3-Dateien müssen neu zugewiesen werden. Vor Aufnahme oder Livestream ein Preset/Projekt speichern, die Pfade prüfen und das Routing testen.

Mehrere parallele DEV-/RC-Versionen tragen **unterschiedliche Plugin-IDs**. Die DAW ersetzt eine alte Instanz daher **nicht automatisch** durch den neuen Kandidaten. Der endgültige öffentliche Produktname und die langfristig stabile Plugin-ID werden vor dem Release festgelegt.

## Systemanforderungen und Grenzen

- **VST3-Host**, Windows x64 oder macOS Universal (Intel und Apple Silicon); für macOS wird macOS 11 als Build-Ziel verwendet. Tatsächliche Host-Kompatibilität muss getestet werden.
- JUCE 9.0.4 wird bei der CMake-Konfiguration bezogen, falls keine lokale JUCE-Kopie bereitgestellt wird.
- Für Musik bei gestopptem DAW-Transport muss der Host weiterhin Plugin-Audio verarbeiten (z. B. REAPERs *Run FX when stopped*).
- Viele laute gleichzeitige Samples können die Summe übersteuern; ein Peak-Limiter im DAW-Ausgang wird empfohlen.
- Kein eingebauter LUFS-Angleich, Peak-Limiter, Mikrofon-Sidechain oder bidirektionales OSC-Feedback.
- Der CI-Build bestätigt die Kompilierung, **nicht** die Praxisfunktion in verschiedenen DAWs.
- Mac-Builds aus GitHub Actions sind bisher nur **ad-hoc signiert, nicht Apple-notarisiert**.

## Status und Lizenzhinweis

Diese Fassung ist ein **Stabile Version 2.3.0** (Veröffentlichung mit Windows-/macOS-Paketen, Dokumentation und vollständigem Quellcode). Vor einem öffentlichen Binary-Release sind die Tests und die JUCE-Lizenzprüfung in der [Release-Checkliste](DOKUMENTATION/RELEASE_CHECKLIST_DE.md) verbindlich zu klären.

Das Programm verwendet JUCE 9, dessen Module unter **AGPLv3 oder einer kommerziellen JUCE-Lizenz** bereitgestellt werden. Für einen nicht unter AGPLv3 veröffentlichten Build kann eine kommerzielle Lizenz erforderlich sein. Der LautFunk-eigene Quellcode ist **MIT-lizenziert** ([LICENSE](LICENSE)); JUCE 9 hat eigene Lizenzbedingungen. Siehe [Lizenzprüfung](DOKUMENTATION/RECHT_LIZENZEN_DE.md).

## Hintergrund

Die Bank-/Pad-Bedienung ist in ihrer Funktion vom [Ultraschall Soundboard](https://github.com/Ultraschall/ultraschall-soundboard) inspiriert. Der hier verwendete Soundboard-C++-Code wurde eigenständig erstellt und enthält keine aus dem Ultraschall-Projekt übernommenen Quelldateien.
