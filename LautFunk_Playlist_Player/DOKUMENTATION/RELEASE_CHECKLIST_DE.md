# Veröffentlichung – vom Release-Kandidaten zum stabilen GitHub Release

Der aktuelle Entwicklungsstand ist **v2.3.0 ROUTING RC** im Branch \`dev/playlist-v2-routing\`. Er ist **noch keine freigegebene Version**. Die stabil getestete v2.1 und der erfolgreiche v2.2-OSC-Build bleiben davon unberührt.

## 1. Technischer Freeze

1. Beide Windows-/macOS-Builds des **gleichen Git-Commits** müssen grün sein.
2. Checkliste [TESTPLAN_DE.md](TESTPLAN_DE.md) möglichst vollständig abhaken; insbesondere:
   - Stereo funktioniert ohne Mehrkanal-Setup;
   - getrenntes Routing in REAPER mit 4 Kanälen;
   - sicherer Rückweg von getrennt nach Stereo;
   - Ducking in beiden Modi;
   - Projekt speichern, schließen, wieder öffnen;
   - Sample-Ordner, MIDI und OSC weiterhin ohne Regression.
3. Benutzeroberfläche auf deutsche Umlaute, abgeschnittene Texte und Skalierung testen.
4. Falls nötig, kleine RC-Fixes auf dem Entwicklungsbranch; anschließend beide Binaries neu bauen.

## 2. Lizenzentscheidung

Der Betreiber gibt an, mit den Plugins **0 € Einnahmen** zu erzielen und sämtliche Plugins kostenlos zum Download anzubieten. Eine kostenlose **JUCE-9-Starter-Lizenz** liegt nach eigener Auskunft vor.

Vor der Freigabe:
- JUCE-9-Starter-EULA auf die konkrete Verwendung und die entwickelnden Personen prüfen.
- **Ausdrücklich festlegen**, ob der eigene LautFunk-Quellcode unter eine Open-Source-Lizenz gestellt wird oder lediglich die Binärdateien kostenfrei genutzt werden dürfen.
- Dazu eine passende \`LICENSE\`-Datei und einen verständlichen Hinweis im Release einfügen. **Keine Lizenz ohne ausdrückliche Auswahl des Betreibers erfinden.**
- Die Hinweise in [RECHT_LIZENZEN_DE.md](RECHT_LIZENZEN_DE.md) beachten.

## 3. Stabile Produktidentität

Bisher haben die DEV-Fassungen unterschiedliche VST3-Plugin-IDs und Namen, damit sie parallel installiert werden können. Für das öffentliche Release eine **dauerhafte Produkt-ID** und einen finalen Namen festlegen.

**Achtung:** Spätere Änderungen der Plugin-ID sind für die DAW eine *andere Plugin-Instanz*. Bereits bestehende REAPER-Projekte werden deshalb möglicherweise nicht automatisch migriert. Für die stabile Produktlinie muss die ID über künftige Updates hinweg gleich bleiben.

Empfohlener Name: **LautFunk Playlist Player & Soundboard**
Vorgeschlagener erster Release-Tag der neuen Produktlinie: **\`playlist-soundboard-v2.3.0\`**.

Diese Namen sind Vorschläge; die konkrete Datei ist noch nicht veröffentlicht.

## 4. Release-Pakete

Für ein öffentliches Release **keine kurzlebigen GitHub-Actions-Artifacts als einzigen Download** verwenden, sondern dauerhafte Assets im GitHub Release:

\`\`\`text
LautFunk-Playlist-Soundboard-v2.3.0-Windows-x64.zip
LautFunk-Playlist-Soundboard-v2.3.0-macOS-Universal.zip
LautFunk-Playlist-Soundboard-v2.3.0-SHA256SUMS.txt
\`\`\`

Jedes ZIP soll das VST3-Bundle enthalten und auf die Dokumentation im Repository verweisen. Optional ein zusätzliches ZIP mit Schnellstart-/Installations-PDF und Beispielsamples, **wenn deren Nutzungsrechte geklärt sind**.

Builds für Windows und macOS sollten mit **einem einheitlichen Quellcode-Commit** erzeugt sein. SHA256-Checksummen liefern eine einfache Integritätsprüfung.

## 5. macOS-Signierung

GitHub Actions erstellt bisher **ad-hoc signierte**, nicht Apple-notarisierte macOS-Binaries. Eine echte, breit zugängliche Mac-Veröffentlichung erfordert eine klare Entscheidung:

- Developer-ID-Signierung und Notarisierung einrichten; oder
- das Paket transparent als **nicht notarisiert** kennzeichnen und auf mögliche Sicherheitsabfragen hinweisen.

Keine notarisierten Downloads versprechen, bevor dieser Schritt tatsächlich durchgeführt wurde.

## 6. GitHub-Release erstellen

Nach Freigabe durch den Betreiber:
1. Finalen geprüften Commit auf den für Veröffentlichungen vorgesehenen Stand bringen.
2. Finale Plugin-ID, Versionsnummer und Änderungsverlauf setzen.
3. Den Quellstand als Git-Tag markieren.
4. CI-Binaries für **genau diesen Tag** bauen und prüfen.
5. Release auf https://github.com/lautfunk/Reaper-FX-Plugins/releases/new anlegen.
6. Tag, Titel, deutsche Beschreibung, Windows-/macOS-ZIPs und SHA256-Datei einfügen.
7. Release veröffentlichen und die dauerhaften Downloadlinks im Repository-README ergänzen.

**Wichtig:** Dieser Schritt wird nicht automatisch durch die Erstellung des RC-Zweigs ausgelöst; er erfolgt erst nach Tests, Lizenzentscheidung und ausdrücklicher Freigabe.

## 7. Release-Text (Vorschlag)

\`\`\`markdown
# LautFunk Playlist Player & Soundboard v2.3.0

Kostenloses VST3 für Podcast, Livestream und Musikproduktion.
Playlist, Soundboard mit 24 Pads je Bank, WAV/MP3-Import,
automatisches Musik-Ducking, MIDI und lokale OSC-Steuerung.

**Neu:** Optionales getrenntes Stereo-Routing.
Standardmäßig bleiben Musik und Einspieler gemeinsam auf Out 1/2;
getrennte Ausgänge 1/2 und 3/4 sind ein Expertenmodus.

**Downloads:** Windows x64, macOS Universal (Intel + Apple Silicon).
Bitte die Installationsanleitung vor der Verwendung lesen.

**Hinweis:** Audiodateien werden nur über externe Dateipfade referenziert.
Ein eingebauter Peak-Limiter und Mikrofon-Sidechain sind nicht enthalten.
Weitere bekannte Einschränkungen stehen in der Dokumentation.

[Hier finale Lizenzangabe und tatsächlichen Mac-Signierungsstatus ergänzen.]
\`\`\`

## 8. Nach der Veröffentlichung

- Fehlerberichte und Nutzerfragen als GitHub Issues sammeln.
- Eine eigene Bugfix-Reihe, z. B. v2.3.1, starten.
- Funktionswünsche separat planen, ohne die stabile Plugin-ID zu ändern.
- Vor Livestream-Einsatz nach jedem Update die Projekteinstellungen und Audioausgänge prüfen.
