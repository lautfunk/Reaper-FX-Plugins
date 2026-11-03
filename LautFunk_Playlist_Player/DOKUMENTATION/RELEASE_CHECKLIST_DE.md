# Release-Checkliste – LautFunk Playlist Player & Soundboard

Diese Checkliste gilt für **stabile v2.3.x-Veröffentlichungen**. Die Version **v2.3.0** wurde am 3. November 2026 veröffentlicht und nach Angaben des Betreibers zuvor in REAPER geprüft. **v2.3.1** ergänzte die ursprünglichen Lizenzhinweise in den Downloadpaketen. Das folgende **Wartungsrelease v2.3.2** korrigiert falsch dargestellte Umlaute und Unicode-Symbole. Die Audioalgorithmen und die stabile VST3-Plugin-ID bleiben unverändert.

## 1. Vor jeder Veröffentlichung

1. Versionsnummer in `CMakeLists.txt`, Versionsanzeige und Changelog übereinstimmend setzen.
2. Die **dauerhafte Plugin-Identität** beibehalten: `PLUGIN_MANUFACTURER_CODE Laut`, `PLUGIN_CODE LfS3` und `BUNDLE_ID de.lautfunk.playlistsoundboard`. Ältere Entwicklungsvarianten mit eigenen IDs bleiben davon unberührt.
3. Das `main`-Repository über Pull Request aktualisieren; `main` ist gegen Löschung und Force Push geschützt.
4. Die JUCE-9-Lizenz des tatsächlichen Rechteinhabers und der beteiligten Framework-Entwickler überprüfen. Maßgeblich sind die [JUCE-9-EULA](https://juce.com/legal/juce-9-licence/) und die Angaben in [RECHT_LIZENZEN_DE.md](RECHT_LIZENZEN_DE.md). Die Angaben zur verfügbaren Starter-Lizenz stammen vom Betreiber; eine externe Prüfung des Lizenzkontos erfolgt nicht.
5. Versionshinweise und Installations- sowie Routingdokumentation auf die tatsächlich gebaute Version abstimmen.

## 2. Windows- und macOS-Builds

- **Windows x64:** Visual Studio 2022 und JUCE 9.0.4, VST3 in Release-Konfiguration.
- **macOS Universal:** Intel `x86_64` und Apple Silicon `arm64`, beide mit `lipo` prüfen; macOS-Zielversion 11.
- Beide Builds müssen **aus genau demselben Quellcode-Commit** stammen und erfolgreich abgeschlossen sein. Ein grüner CI-Build allein ersetzt keinen Praxistest in REAPER.
- Die macOS-Ausgabe ist derzeit **ad-hoc signiert und nicht Apple-notarisiert**. Dieser Umstand muss im Release und der Anleitung stehen.

## 3. Pflichtdateien in beiden Download-ZIPs

Jedes der beiden Pakete muss Folgendes enthalten:

- `LautFunk Playlist Soundboard.vst3` (vollständiges Bundle)
- `LICENSE` (LautFunk-eigener MIT-Code)
- `THIRD_PARTY_NOTICES.md` mit **Original-MIT-Lizenz des Ultraschall Soundboards** und **Copyright (c) 2014–2021 Daniel Lindenfelser**
- `README_DE.md` und `RELEASE_NOTES_DE.md`
- `CHANGELOG.md` und den Ordner `DOKUMENTATION`

Die Build-Pipeline überprüft die Existenz des VST3 und die Anwesenheit des ursprünglichen Lizenz-/Copyright-Textes in **beiden ZIPs**, bevor sie einen Release veröffentlicht.

## 4. Tag, Assets und Prüfsummen

Für v2.3.2 gilt:

```text
Tag: playlist-soundboard-v2.3.2
LautFunk-Playlist-Soundboard-v2.3.2-Windows-x64.zip
LautFunk-Playlist-Soundboard-v2.3.2-macOS-Universal.zip
SHA256SUMS.txt
```

- Der GitHub-Actions-Publish-Workflow erzeugt beide Plattformpakete und die gemeinsame `SHA256SUMS.txt`.
- **Nur nach beiden erfolgreichen Builds und Lizenzpaket-Prüfungen** darf der Publish-Job die dauerhaften Assets unter [GitHub Releases](https://github.com/lautfunk/Reaper-FX-Plugins/releases) anlegen.
- Die Veröffentlichung ist kein kurzlebiges Actions-Artefakt. GitHub ergänzt zum Release automatisch Quellcode-Archive (ZIP und tar.gz).
- Bereits vorhandene Releases werden **nicht automatisch überschrieben**.
- Die Windows-/macOS-Dateien werden nach der Veröffentlichung mit ihren SHA-256-Prüfsummen auf Integrität geprüft.

## 5. Praxis- und Regressionstests

Die ausführlichen Prüfpunkte stehen im [TESTPLAN_DE.md](TESTPLAN_DE.md), insbesondere:

1. Neue Plugin-Instanz in REAPER laden; Stereo-Mix 1/2 verwenden.
2. Optional getrennte Ausgänge (Musik 1/2, Soundboard 3/4) in einer Vierkanal-Spur prüfen.
3. Playlist, Soundboard-Pads, WAV/MP3, Ducking, MIDI und lokales OSC auf Funktion prüfen.
4. Projekt speichern, schließen und neu öffnen.
5. Bei einem Wechsel von v2.3.0 auf v2.3.1 ein Backup anlegen und die unveränderte Plugin-ID sicherstellen.
6. Bei v2.3.2 die Zeichenanzeige von **LAUTSTÄRKE** und weiteren Umlaut-Texten prüfen. Der UTF-8-Regressionstest muss für Windows und macOS erfolgreich sein.
7. Kein offizielles macOS-Praxiszertifikat und keine Tests anderer DAWs behaupten, wenn sie nicht durchgeführt wurden.

## 6. Nach dem Release

- Release-URL in der Repository-README und in `README_DE.md` aktuell halten.
- Bekannte Einschränkungen dokumentieren: kein integrierter Summen-Limiter, keine Mikrofon-Sidechain, macOS nicht notarisiert.
- Fehlerberichte über [GitHub Issues](https://github.com/lautfunk/Reaper-FX-Plugins/issues) sammeln.
- Zur rechtlichen Herkunft bei Bedarf die Historie und [THIRD_PARTY_NOTICES.md](../THIRD_PARTY_NOTICES.md) aktualisieren.
- Bei künftigen Wartungsreleases die **Plugin-ID unverändert** lassen, damit bestehende REAPER-Projekte kompatibel bleiben.

Diese Checkliste protokolliert die vorgesehenen Prüfungen; sie ersetzt weder individuelle Funktionstests noch die Kontrolle der Lizenzvoraussetzungen.
