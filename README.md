# LautFunk – Audio-Plugins für REAPER und VST3-Hosts

**Kostenlose Open-Source-Audiowerkzeuge für Podcasts, Livestreams, Hörspiele, Musikproduktion und Sounddesign.** Das Repository enthält zwei unterschiedliche Plugin-Arten: direkt in REAPER nutzbare **JSFX** sowie den separat installierbaren **Playlist Player & Soundboard (VST3)**.

Die von LautFunk selbst entwickelten Quellen stehen unter der **[MIT-Lizenz](LICENSE)**. Sie dürfen verwendet, verändert und weitergegeben werden – auch kommerziell, sofern Lizenz- und Urheberrechtshinweise erhalten bleiben. LautFunk stellt die eigenen Plugins selbst **kostenlos** bereit und erzielt nach eigener Angabe damit **0 € Einnahmen**. Externe Frameworks wie JUCE haben **eigene Lizenzbedingungen**.

**Direkt zu den wichtigsten Bereichen:** [Plugin-Übersicht](#enthaltene-plugins) · [Playlist Player & Soundboard](#playlist-soundboard-vst3) · [JSFX-Installation](#installation) · [VST3-Installation](LautFunk_Playlist_Player/DOKUMENTATION/INSTALLATION_DE.md) · [Quellcode und Lizenz](#quellcode-und-lizenz) · [GitHub Releases](https://github.com/lautfunk/Reaper-FX-Plugins/releases)

**Veröffentlichungsstatus:** Der [Playlist Player v1.0](https://github.com/lautfunk/Reaper-FX-Plugins/releases/tag/playlist-v1.0.0) ist bereits veröffentlicht. Der erweiterte **Playlist Player & Soundboard v2.3.0-rc1** befindet sich derzeit in der Freigabeprüfung; dies ist **noch keine offizielle v2.3-Version**. Die [Release-Kandidaten](https://github.com/lautfunk/Reaper-FX-Plugins/actions) werden als GitHub-Actions-Artefakte bereitgestellt.

---

<a id="inhaltsverzeichnis"></a>

## Inhaltsverzeichnis

- [Enthaltene Plugins](#enthaltene-plugins)
- [Playlist Player & Soundboard (VST3)](#playlist-soundboard-vst3)
- [Quellcode und Lizenz](#quellcode-und-lizenz)
- [Releases und Versionen](#releases-und-versionen)
- [LautFunk Digital Glitch](#digital-glitch)
  - [Glitch-Arten](#glitch-arten)
  - [Pitch-Modulation](#glitch-pitch)
  - [Presets](#glitch-presets)
- [LautFunk Voice Scrambler](#voice-scrambler)
  - [Frequenzinversion](#scrambler-frequenzinversion)
  - [Zwei Scrambler-Verfahren](#scrambler-verfahren)
  - [Old Radio](#scrambler-old-radio)
  - [Automatische Rauschsperre](#scrambler-squelch)
  - [Hold to Talk](#scrambler-hold-to-talk)
  - [Presets](#scrambler-presets)
  - [Clean Decode](#scrambler-clean-decode)
- [LautFunk Voice Transformer v1.0](#voice-transformer)
  - [Neu in 1.0](#vt-neu)
  - [Installation und erster Test](#vt-erster-test)
  - [Einmessung](#vt-einmessung)
  - [Profile und Klangregler](#vt-profile)
  - [Qualität und Latenz](#vt-qualitaet)
  - [Prüfung und Grenzen](#vt-pruefung)
  - [Fachliche Grundlage](#vt-grundlage)
- [LautFunk SoftGuard v1.1](#softguard)
  - [Funktionsprinzip und Soft Knee](#softguard-prinzip)
  - [Sprecher- und Master-Modus](#softguard-modi)
  - [Bedienelemente](#softguard-bedienung)
  - [Empfohlener Podcast-Workflow](#softguard-workflow)
  - [Installation und Render-Skript](#softguard-installation)
  - [Messung und technische Grenzen](#softguard-grenzen)
- [LautFunk FartSynth 61 v1.0](#fartsynth)
  - [Modus „ALLE 12“](#fartsynth-alle-12)
  - [Modus „EIN CHARAKTER“](#fartsynth-ein-charakter)
  - [FartSynth-Regler](#fartsynth-regler)
  - [MIDI-Steuerung](#fartsynth-midi)
  - [Technische Prüfung](#fartsynth-pruefung)
- [JSFX-Installation](#installation)
- [Typische JSFX-Installationspfade](#installationspfade)
- [Plugins in REAPER laden](#plugins-laden)
- [Anforderungen](#anforderungen)
- [Einsatzbereiche](#einsatzbereiche)
- [Über LautFunk](#ueber-lautfunk)

<a id="enthaltene-plugins"></a>

## Enthaltene Plugins

| Plugin | Typ | Verwendung | Quellcode / Anleitung |
| --- | --- | --- | --- |
| **Digital Glitch v1.2** | JSFX | Stutter, Bitcrushing, Glitch-Events und Pitch-Effekte | [JSFX](LautFunk_Digital_Glitch.jsfx) · [Details](#digital-glitch) |
| **Voice Scrambler v2.2** | JSFX | Sprachverfremdung durch Frequenzinversion und Radiocharakter | [JSFX](LautFunk_Voice_Scrambler_v2.2.jsfx) · [Details](#voice-scrambler) |
| **Voice Transformer v1.0** | JSFX | Echtzeit-Veränderung von Pitch, Formanten und Stimmcharakter | [JSFX](LautFunk_Voice_Transformer_v1.0.jsfx) · [Details](#voice-transformer) |
| **SoftGuard v1.1** | JSFX + optionales Lua-ReaScript | Sanfte Sprecherpegel-Regelung und Soft-Knee-Limiter | [JSFX](LautFunk_SoftGuard.jsfx) · [Render-Skript](LautFunk_Render_Ziele.lua) · [Details](#softguard) |
| **FartSynth 61 v1.0** | JSFX | MIDI-Synthesizer mit 61 Tasten und zwölf Klangcharakteren | [JSFX](LautFunk_FartSynth_61_v1.0.jsfx) · [Details](#fartsynth) |
| **Playlist Player & Soundboard** | **VST3** | Musikplaylist, Soundbänke, Ducking, MIDI, lokale OSC-Steuerung, optional getrennte Ausgänge | [C++-Quellcode](LautFunk_Playlist_Player/Source) · [VST3-Anleitung](LautFunk_Playlist_Player/README_DE.md) |

**Unterschied:** JSFX-Dateien werden direkt im REAPER-Effektverzeichnis installiert und brauchen **kein VST3**. Der Playlist Player & Soundboard ist ein **eigenständiges VST3**, dessen Installation über den VST3-Ordner erfolgt. Er ist auch für weitere VST3-Hosts konzipiert; die tatsächlich bestätigte Funktionskompatibilität richtet sich nach den dokumentierten Tests.

<a id="playlist-soundboard-vst3"></a>

## LautFunk Playlist Player & Soundboard (VST3)

Der Playlist Player & Soundboard vereint eine eigenständig abspielende WAV-/MP3-Playlist mit einem Soundboard mit **24 Pads je Bank**. Beliebig viele Bänke, 12er-/24er-Ansicht, Loop, Fades, Ordnerimport, Bankdateien und Restlaufzeit unterstützen Podcast- und Live-Produktion. Die Sample-Wiedergabe bleibt auch beim Bankwechsel aktiv.

**Musik-Ducking** lässt sich ein- und ausschalten: Samples senken die Playlist-Musik einstellbar ab, anschließend steigt sie mit einstellbarem Release wieder an. MIDI und **lokales OSC** (optional, standardmäßig deaktiviert) können die Pads und die Playlist steuern; Stream Deck ist über **Bitfocus Companion/Generic OSC** möglich.

**Audioausgänge:** Im Normalbetrieb werden Musik und Samples **gemeinsam auf Stereo 1/2** ausgegeben. Der optionale Expertenmodus führt Musik über 1/2 und Samples über 3/4; dafür ist DAW-Mehrkanalrouting erforderlich. Ohne dieses Routing nutzt man weiterhin den Stereo-Mix.

**Versionen:** Die ursprüngliche Playlist-v1.0 ist über [GitHub Releases](https://github.com/lautfunk/Reaper-FX-Plugins/releases/tag/playlist-v1.0.0) verfügbar. Die v2.3 mit Soundboard und separaten Ausgängen wurde in REAPER als Routing-Testfassung erprobt. Die endgültig benannte **v2.3.0-rc1** wird vor einem öffentlichen Release separat geprüft. Die zwischenzeitlichen Entwicklungsfassungen behalten ihre abweichenden Plugin-IDs und sind **keine automatischen Upgrades** älterer REAPER-Projekte.

Dokumente: [Benutzerhandbuch](LautFunk_Playlist_Player/README_DE.md) · [Installation für Windows/macOS](LautFunk_Playlist_Player/DOKUMENTATION/INSTALLATION_DE.md) · [Routing in REAPER](LautFunk_Playlist_Player/DOKUMENTATION/REAPER_ROUTING_DE.md) · [MIDI/OSC-Befehle](LautFunk_Playlist_Player/README_DE.md#lokale-osc--stream-deck-steuerung) · [Changelog](LautFunk_Playlist_Player/CHANGELOG.md) · [Testplan](LautFunk_Playlist_Player/DOKUMENTATION/TESTPLAN_DE.md) · [Release-Checkliste](LautFunk_Playlist_Player/DOKUMENTATION/RELEASE_CHECKLIST_DE.md).

<a id="quellcode-und-lizenz"></a>

## Quellcode und Lizenz

**Alle eigenen Quelldateien stehen im Repository**, damit andere den Code prüfen, verbessern und weiterentwickeln können: die fünf [JSFX-Skripte](#enthaltene-plugins), das [Lua-ReaScript](LautFunk_Render_Ziele.lua) und das [C++-/JUCE-Projekt](LautFunk_Playlist_Player) mit [Source-Verzeichnis](LautFunk_Playlist_Player/Source) sowie CMake- und Buildskripten.

- **LautFunk-eigener Code:** [MIT-Lizenz](LICENSE), mit SPDX-Hinweisen in den JSFX- und Lua-Dateien. Lizenztext und Urheberrechtsvermerk müssen bei Kopien oder wesentlichen Teilen erhalten bleiben.
- **JUCE 9.0.4:** Eigenständige Bedingungen von [JUCE](https://juce.com/legal/juce-9-licence/). Für die VST3-Entwicklung wird nach Auskunft des Projekts die kostenlose **JUCE-Starter-Lizenz** genutzt. Die MIT-Lizenz des LautFunk-Codes überträgt **keine** JUCE-Lizenz an Dritte.
- **Weitere Rechte:** Marken, Logos, Audiosamples, fremde Codebibliotheken und sonstige Drittinhalte sind nur erfasst, soweit die jeweiligen Rechte dies erlauben. Siehe [Lizenz- und Drittanbieterhinweise](LautFunk_Playlist_Player/DOKUMENTATION/RECHT_LIZENZEN_DE.md).
- **Beiträge:** Pull Requests und nachvollziehbare GitHub-Issues sind willkommen. Bei fremden Codebeiträgen müssen die Beitragenden berechtigt sein, sie unter MIT bereitzustellen.

**MIT erlaubt ausdrücklich auch kommerzielle Weiterverwendung durch andere**; dass LautFunk seine Plugins kostenlos bereitstellt, schränkt diese Rechte nicht ein.

<a id="releases-und-versionen"></a>

## Releases und Versionen

Öffentliche, dauerhaft verfügbare Downloads stehen unter **[GitHub Releases](https://github.com/lautfunk/Reaper-FX-Plugins/releases)**. Entwicklungsstände unter **[GitHub Actions](https://github.com/lautfunk/Reaper-FX-Plugins/actions)** sind zeitlich begrenzte Test-Artefakte und sollten nicht als stabile Veröffentlichung bezeichnet werden.

| Version | Status | Hinweis |
| --- | --- | --- |
| Playlist Player **v1.0.0** | Veröffentlicht | Windows x64 und macOS Universal als VST3 |
| Playlist Player & Soundboard **v2.0–v2.2 DEV** | Entwicklungsfassungen | Soundbänke, Ducking, MIDI und OSC schrittweise ergänzt |
| Playlist Player & Soundboard **v2.3.0-rc1** | Release-Kandidat | Optional getrennte Ausgänge; finale Plugin-ID, Dokumentation und Buildpakete in Prüfung |
| **v2.3.0** | Noch nicht veröffentlicht | Erst nach Abschluss der Release-Checkliste und Prüfung der finalen Pakete |

**macOS-Hinweis:** Die bisherigen GitHub-Testpakete sind ad-hoc signiert und **nicht Apple-notarisiert**. Das wird bei einem öffentlichen Release transparent angegeben.

---

<a id="digital-glitch"></a>

# LautFunk Digital Glitch

## Digitale Fehler als kreativer Audioeffekt

**LautFunk Digital Glitch** erzeugt kontrolliertes digitales Chaos.

Stimmen, Musik und andere Audiosignale können damit so klingen, als würden sie über eine beschädigte Datenverbindung übertragen, aus einem fehlerhaften Audiopuffer abgespielt oder von einem instabilen Computersystem verarbeitet.

Der Effekt liegt dabei nicht permanent über dem gesamten Signal.

Stattdessen entstehen einzelne **Glitch-Ereignisse**, die abhängig von den gewählten Einstellungen ausgelöst werden. Zwischen diesen Ereignissen bleibt das ursprüngliche Signal erhalten.

Über den **Wet/Dry-Regler** lässt sich bestimmen, wie stark der Effekt während eines Glitches gegenüber dem Originalsignal hervortritt.

<a id="glitch-arten"></a>

## Glitch-Arten

### Stutter

Kurze Abschnitte des Audiosignals werden mehrfach wiederholt.

Dadurch entstehen Effekte, die an einen digitalen Schluckauf oder einen hängen gebliebenen Audiopuffer erinnern.

### Buffer Freeze

Ein kleiner Ausschnitt des Signals wird eingefroren und während des Glitches wiederholt.

Das Ergebnis erinnert beispielsweise an:

- abgestürzte Audiotreiber
- beschädigte Streams
- eingefrorene Audiopuffer
- instabile digitale Übertragungen

### Bitcrush Burst

Während eines Glitch-Ereignisses wird die digitale Auflösung des Signals reduziert.

Dadurch kann das Audio:

- körniger
- rauer
- digital verzerrt
- zunehmend zerstört

klingen.

### Sample-Rate Glitch

Die effektive Abtastrate wird während eines Glitches verändert.

Dadurch entstehen unter anderem:

- roboterhafte Stimmen
- digitale Artefakte
- Aliasing
- Lo-Fi-Strukturen
- ungewöhnliche digitale Verzerrungen

### Packet Dropout

Teile des Signals verschwinden oder werden durch bereits vorhandene Audioabschnitte ersetzt.

Der Effekt kann an:

- schlechte Internetverbindungen
- VoIP-Aussetzer
- beschädigte Streams
- verlorene Datenpakete
- fehlerhafte Funkübertragungen

erinnern.

## Glitch-Häufigkeit

Die Häufigkeit der Glitch-Ereignisse lässt sich über einen sehr großen Bereich einstellen.

Möglich sind einzelne, selten auftretende Fehler ebenso wie nahezu permanentes digitales Chaos.

Die maximale Rate beträgt:

**bis zu 1.200 Glitch-Ereignisse pro Minute**

Bei extremen Einstellungen kann praktisch unmittelbar nach einem Glitch bereits das nächste Ereignis beginnen.

## Glitch-Dauer

Die Dauer eines einzelnen Glitches kann ebenfalls sehr weit eingestellt werden:

**20 Millisekunden bis 10 Sekunden**

Damit sind sowohl winzige digitale Klicks und Stottereffekte als auch lange, drastische Systemfehler möglich.

---

<a id="glitch-pitch"></a>

## Pitch-Modulation

Zusätzlich besitzt LautFunk Digital Glitch eine eigene Tonhöhenmodulation.

Diese wird ausschließlich während eines aktiven Glitch-Ereignisses auf das Effektsignal angewendet.

Der Pitch-Bereich reicht bis:

**±24 Halbtöne**

also bis zu zwei Oktaven nach oben oder unten.

### Digital Drift

Die Tonhöhe bewegt sich während des Glitches kontinuierlich.

Dadurch entstehen instabile Bewegungen, die beispielsweise an fehlerhafte Taktgeber, beschädigte Bandmaschinen oder abstürzende Audioprozessoren erinnern können.

### Pitch Steps

Die Tonhöhe verändert sich in einzelnen Stufen.

Dadurch entstehen harte digitale Sprünge, die besonders bei Sprache und Vocals deutlich hörbar werden.

### Pitch Crash

Die Tonhöhe kann während eines Glitches drastisch:

- nach unten abstürzen
- nach oben schießen

Der Modus eignet sich besonders für extreme Übergänge oder simulierte Systemfehler.

### Chaos Pitch

Für jedes Glitch-Ereignis wird automatisch ein anderer Pitch-Verlauf ausgewählt.

Dadurch entstehen weniger vorhersehbare und abwechslungsreichere Störungen.

### Anpassung an die Glitch-Dauer

Mit der Option **„An Glitch-Dauer“** wird die Geschwindigkeit der Pitch-Bewegung automatisch an die aktuelle Länge des Glitches angepasst.

So bleibt die Modulation auch bei sehr kurzen Ereignissen deutlich wahrnehmbar.

---

## Einsatzmöglichkeiten

LautFunk Digital Glitch eignet sich unter anderem für:

- Podcasts
- Hörspiele
- Rückblenden
- verfremdete Zitate
- digitale Unterbrechungen
- technische Einbrüche
- satirische Reaktionen
- Übergänge zwischen Themen
- Übergänge zwischen Podcast-Rubriken
- kaputte Telefonverbindungen
- instabile Funkübertragungen
- beschädigte Streams
- Roboterstimmen
- Science-Fiction-Effekte
- Systemabstürze
- experimentelle Vocals
- elektronische Musik
- Industrial
- IDM
- Glitch
- Noise
- Sounddesign

<a id="glitch-presets"></a>

## Presets

### Schlechte Verbindung

Kurze und deutlich hörbare Übertragungsfehler.

Geeignet für:

- Telefonstimmen
- Streams
- Funk
- VoIP-Simulationen

### Digitaler Schluckauf

Häufigere Wiederholungen, Bufferfehler und digitale Macken.

Gut geeignet für rhythmische und deutlich wahrnehmbare Glitch-Effekte.

### Systemabsturz

Die maximale Eskalationsstufe.

Lange Störungen, hohe Ereignisdichte und Chaos-Pitch verwandeln das Signal in einen digitalen Totalschaden.

---

[↑ Zurück zum Inhaltsverzeichnis](#inhaltsverzeichnis)

<a id="voice-scrambler"></a>

# LautFunk Voice Scrambler

## Stimmen zwischen Geheimfunk und Science-Fiction

Der **LautFunk Voice Scrambler** ist ein kreativer Spracheffekt für REAPER.

Er verwandelt Stimmen in metallische, ungewöhnliche und teilweise schwer verständliche Funksignale.

Entwickelt wurde er insbesondere für:

- Podcasts
- Hörspiele
- elektronische Musik
- Sounddesign
- experimentelle Sprachbearbeitung

Klanglich kann der Effekt unter anderem an:

- abgefangene Funkübertragungen
- alte Feldfunkgeräte
- Geheimfunk
- analoge Sprachverschleierung
- Science-Fiction-Kommunikation

erinnern.

---

<a id="scrambler-frequenzinversion"></a>

## Frequenzinversion

Das Herzstück des Voice Scramblers ist die **Frequenzinversion**.

Dabei werden Frequenzanteile des Eingangssignals relativ zu einer eingestellten Trägerfrequenz gespiegelt.

Vereinfacht gesagt werden tiefer liegende Frequenzanteile nach oben und höher liegende Anteile nach unten verschoben.

Bei einer Trägerfrequenz von beispielsweise:

**3.300 Hz**

wird ein Frequenzanteil bei:

**1.000 Hz**

ungefähr auf:

**2.300 Hz**

abgebildet.

Dadurch verändert sich die gesamte spektrale Struktur einer Stimme.

Sprache klingt anschließend fremdartig, metallisch und je nach Einstellung deutlich schwerer verständlich.

---

<a id="scrambler-verfahren"></a>

## Zwei Scrambler-Verfahren

### Standard Inversion

Bei der klassischen Frequenzinversion wird das Sprachsignal als zusammenhängender Frequenzbereich bearbeitet.

Das erzeugt den typischen Klang analoger Sprachverschleierung.

### Split-Band Scrambling

Das Eingangssignal wird in mehrere Frequenzbereiche aufgeteilt.

Diese Bänder können getrennt bearbeitet werden, wodurch komplexere und deutlich stärker verfremdete Sprachstrukturen entstehen.

---

<a id="scrambler-old-radio"></a>

## Old Radio

Der integrierte **Old-Radio-Modus** ergänzt die Frequenzinversion um typische Eigenschaften älterer Funkgeräte.

Dazu gehören beispielsweise:

- eingeschränkter Frequenzbereich
- Filterung
- Sättigung
- Rauschen
- schwankende Trägerfrequenzen
- Funkartefakte

Damit lässt sich aus einer einfachen Frequenzinversion eine wesentlich komplexere Funkübertragung gestalten.

---

<a id="scrambler-squelch"></a>

## Automatische Rauschsperre

Eine integrierte **Squelch-Funktion** arbeitet ähnlich wie die Rauschsperre eines Funkgerätes.

Während Sprechpausen kann das Signal automatisch geschlossen werden.

Einstellbar sind unter anderem:

- Schwellwert
- Haltezeit
- Öffnungsverhalten
- Schließverhalten

Zusätzlich können beim Öffnen und Schließen kurze Rauschimpulse erzeugt werden.

Dadurch entsteht ein deutlich lebendigerer Funkgerätecharakter.

---

<a id="scrambler-hold-to-talk"></a>

## Hold to Talk

Mit **Hold to Talk** lässt sich die Audioübertragung ähnlich wie bei einer Sprechtaste eines Funkgerätes aktivieren.

Die Funktion eignet sich besonders für:

- Hörspiele
- Funkdialoge
- Podcasts
- automatisierte Effekte
- Sounddesign

Der Parameter kann innerhalb von REAPER automatisiert werden.

---

## Klangsteuerung

Der Voice Scrambler bietet zahlreiche Einstellmöglichkeiten.

Dazu gehören unter anderem:

- Trägerfrequenz
- Feinabstimmung
- Filter
- Effektanteil
- Ausgangspegel
- Rauschanteil
- Funkcharakter
- Pegelanpassung

Die Trägerfrequenz kann bis in den Bereich von:

**0,1 Hz**

fein eingestellt werden.

Parameteränderungen werden geglättet, damit bei Automation möglichst wenige unerwünschte Sprünge oder Klicks entstehen.

---

## Pegel und Analyse

Zur Unterstützung beim Einstellen besitzt der Voice Scrambler verschiedene Analysefunktionen.

Dazu gehören unter anderem:

- Eingangspegel
- Ausgangspegel
- Übersteuerungsanzeige
- Spektrumanzeige
- Frequenzzuordnung
- Testton
- optionaler Pegelabgleich

Der Pegelabgleich versucht Lautstärkeunterschiede zwischen Original- und Effektsignal näherungsweise auszugleichen.

---

<a id="scrambler-presets"></a>

## Presets

### KGB Cold War

Dunkle, klassische Geheimfunk-Atmosphäre.

### Field Radio 1970

Anmutung eines älteren Feldfunkgerätes mit eingeschränktem Frequenzbereich und Funkartefakten.

### NSA Numbers

Experimenteller Numbers-Station- und Geheimdienst-Sound.

### Deep Scramble

Stärkere und komplexere Sprachverfremdung.

Die Namen der Presets beschreiben ausschließlich kreative Klangwelten.

Sie stellen **keine originalgetreuen Simulationen realer Geräte, Organisationen oder historischer Übertragungssysteme** dar.

---

<a id="scrambler-clean-decode"></a>

## Clean Decode

Eine ausschließlich frequenzinvertierte Stimme kann unter bestimmten Bedingungen durch eine erneute Frequenzinversion näherungsweise wieder verständlicher gemacht werden.

Dafür besitzt das Plugin den Modus:

**Clean Decode**

Dabei werden zusätzliche Funk- und Störeffekte deaktiviert, während Trägerfrequenz und Feinabstimmung erhalten bleiben.

Eine verlustfreie Wiederherstellung des ursprünglichen Signals ist jedoch nicht garantiert.

Insbesondere folgende Bearbeitungen können eine Rekonstruktion erschweren oder vollständig verhindern:

- Filter
- Verzerrung
- Rauschen
- Split-Band-Verarbeitung
- zusätzliche Effekte
- verlustbehaftete Audiokompression

Der LautFunk Voice Scrambler ist deshalb **kein Verschlüsselungssystem und bietet keine sichere Kommunikation**.

Er wurde ausschließlich als kreativer Audioeffekt entwickelt.

---

[↑ Zurück zum Inhaltsverzeichnis](#inhaltsverzeichnis)

<a id="voice-transformer"></a>

# LautFunk Voice Transformer v1.0

Stimmveränderer für REAPER mit acht Profilen, automatischer Einmessung und getrennten Reglern für Tonhöhe, Formanten und Stimmcharakter. Stand: 1. Oktober 2026.

<a id="vt-neu"></a>

## Neu in 1.0

**Korrigierte Phasenfortführung:** In v0.2 verwendete jede FFT-Frequenzzelle einen eigenen Phasenakkumulator. Wenn eine Spektralspitze beim Sprechen in eine benachbarte Zelle wanderte, konnte sie eine unpassende Phasenhistorie übernehmen. v1.0 speichert nach jeder Phasenbindung den zusammenhängenden Zustand aller Analysezellen. Bewegte Spektralspitzen übernehmen dadurch die bereits gebundene Phase ihrer Umgebung.

Der Fehler ließ sich mit einem gleich lauten, gleitenden Sinuston reproduzieren. Bei −5 Halbtönen sank der Variationskoeffizient der Ausgangshüllkurve im festgelegten Testabschnitt von etwa **0,213 auf 0,058**, also von 21,3 % auf 5,8 %. Das misst eine konkrete unerwünschte Pegelschwankung. Es bedeutet weder „73 % weniger Artefakte“ allgemein noch eine nachgewiesene Verbesserung jeder Stimme. Die vollständigen Werte und Testbedingungen stehen im Prüfbericht.

**Alter Mann:** Die gestalterischen Grundwerte bleiben bei 140 Hz und Resonanzfaktor 0,91. Die Korrektur der Verarbeitung soll die bereits gelungene Klangrichtung sauberer wiedergeben.

**Alte Frau:** Der Tonhöhenbezug beträgt jetzt 160 statt 180 Hz, der Resonanzfaktor 0,95 statt 1,01. Bei Sarahs gemessenen 185 Hz / Mittel sind das ungefähr **−2,5 Halbtöne Pitch und −0,9 Halbtöne Formanten**, statt bisher −0,5 / +0,2. Dazu kommen stärker ausgeprägte, aber regelbare Änderungen an Körper, Mitten und Luftigkeit. Das sind künstlerische Profilwerte, keine medizinisch bestimmten Altersgrenzen.

**Kontinuierliche Altersfärbung:** Atemtextur und kleine Amplitudenänderungen werden nun fortlaufend und geglättet im Audiosignal erzeugt. Die frühere zufällige Rauschphase pro FFT-Fenster entfällt. Atemtextur folgt dem Pegel des verzögerten Effektsignals und verstummt bei Stille. Stimmzittern und zusätzliche Sättigung bleiben standardmäßig ausgeschaltet.

Die Einmessung, die hohe Konsonantenbearbeitung und die vier Qualitätsstufen aus v0.2 bleiben enthalten. Unterhalb von 1,8 kHz gibt es weiterhin keinen vom Stimmhaftigkeitsdetektor gesteuerten Rückfall zum Originalsignal. Der Artikulationsregler kann oberhalb davon eingefärbte Anteile der Eingangsreibegeräusche beimischen.

<a id="vt-erster-test"></a>

## Installation und erster Test

1. In REAPER **Options → Show REAPER resource path in explorer/finder** öffnen.
2. `LautFunk_Voice_Transformer_v1.0.jsfx` in `Effects/LautFunk/` ablegen. Den Unterordner bei Bedarf anlegen. Auf die Endung `.jsfx` achten.
3. FX-Liste aktualisieren oder REAPER neu starten. Die bisherige Instanz deaktivieren und **LautFunk Voice Transformer v1.0** als neue Instanz laden. Zwei aktive Instanzen hintereinander würden den Effekt doppelt anwenden. Bestehende Projekte wechseln durch den neuen Dateinamen nicht automatisch auf v1.0.
4. Passenden Mikrofoneingang und im Plugin **Links**, **Rechts** oder **L + R** wählen. Monitoring beziehungsweise die Wiedergabe einer Aufnahme starten.
5. Zunächst **Studio** verwenden. Unter **Einmessen: Ausgangslage** auf **Automatisch** stellen, dann oben **Einmessen** anklicken und normal sprechen.
6. Gewünschtes Zielprofil wählen. Für den ersten Vergleich: **Verwandlung 100 %, Effektanteil 100 %, Alterscharakter 65 %, Rauheit 0 %, Stimmzittern 0 %**, Feinwerte 0. Der Schalter oben muss **Effekt an** anzeigen.

Die einzelne JSFX-Datei ist vollständig. Zusätzliche Modelle, DLLs oder eine Internetverbindung sind nicht nötig. Die verarbeitete Stimme liegt mono auf beiden Ausgangskanälen.

<a id="vt-einmessung"></a>

## Einmessung

Die Einmessung sammelt stimmhafte Abschnitte mit ausreichender Erkennungssicherheit und bestimmt deren Median. Sie endet frühestens nach 3 Sekunden verarbeiteter Audiozeit, sobald mindestens 2 Sekunden gültiges Material vorliegen. Nach 8 Sekunden wird mit mindestens 1 Sekunde gültigem Material ausgewertet; andernfalls erscheint „Zu wenig Sprache“ und die bisherigen Werte bleiben erhalten. Ein zweiter Klick auf den Messknopf bricht ab.

Bei geöffneter Oberfläche beendet eine zusätzliche Zeitüberwachung eine stockende Messung nach ungefähr 10 Sekunden mit „Kein Audio / Timeout“. Wenn sowohl Audioverarbeitung als auch Oberfläche nicht laufen, kann kein Timer ausgeführt werden; beim Wiederöffnen wird der Zustand überprüft.

| Gemessene Stimmbasis | Automatischer Resonanz-Startwert |
| --- | --- |
| Unter 155 Hz | Tief |
| 155 bis unter 220 Hz | Mittel |
| Ab 220 Hz | Hoch |

Diese Zuordnung ist eine klangliche Ausgangshilfe. Sie erkennt weder Alter noch Geschlecht und misst nicht die anatomische Größe des Vokaltrakts. Wenn „Hoch“ besser klingt, darf diese Einstellung unabhängig vom Messwert gewählt werden.

Ein Klick auf Tief/Mittel/Hoch schaltet auf **Manuell** um und erhält die gemessene Stimmbasis. Auch während einer Messung wird eine manuelle Auswahl respektiert. Für eine neue automatische Zuordnung wieder auf **Automatisch** schalten und einmessen. Die akzeptierte Stimmbasis liegt zwischen 70 und 350 Hz; Flüstern, Knarren, Musik oder starke Nebengeräusche können die Messung erschweren. Studio ist der vorgesehene Ausgangspunkt für die Einmessung.

<a id="vt-profile"></a>

## Profile und Klangregler

| Profil | Tonhöhenbezug | Gestalterische Richtung |
| --- | --- | --- |
| Neutral | Eigene Stimmbasis | Keine profilbedingte Pitch-/Formantverschiebung |
| Frau | 205 Hz | Hellerer erwachsener Stimmcharakter |
| Mann | 135 Hz | Tieferer erwachsener Stimmcharakter |
| Junge | 270 Hz | Kindlicher Klangentwurf A |
| Mädchen | 295 Hz | Kindlicher Klangentwurf B |
| Jugendlich | 230 Hz | Leichter, jüngerer Stimmcharakter |
| Alter Mann | 140 Hz | Tieferer Alterscharakter |
| Alte Frau | 160 Hz | Alterscharakter mit abgesenkter Tonhöhe und Resonanz |

Der natürliche Tonhöhenverlauf wird proportional verschoben, nicht auf eine feste Note gezogen. Die Profilnamen beschreiben Klangentwürfe. Sprechweise und Artikulation bleiben von der sprechenden Person geprägt; ein bestimmtes Alter oder eine neue Sprecheridentität wird nicht garantiert.

| Regler | Funktion |
| --- | --- |
| Verwandlung | Stärke der Pitch-/Formantverschiebung und der zusätzlichen Charakterregler |
| Tonhöhe fein | Zusätzliche Tonhöhenkorrektur relativ zum Profil |
| Formanten fein | Resonanzfarbe unabhängig von der Tonhöhe: links größer/dunkler, rechts kleiner/heller |
| Effektanteil | Mischung mit dem zeitlich angepassten Eingang; für Rollenstimmen mit 100 % beginnen |
| Alterscharakter | Nur für beide Altersprofile: Klangfarbe, etwas Luftigkeit und kleine kontinuierliche Amplitudenänderungen. Standard 65 %. |
| Rauheit / Sättigung | Optionale milde Sättigung für alle Profile. Standard 0 %. |
| Stimmzittern | Optionales unregelmäßiges Vibrato für alle Profile. Standard 0 %. |
| Artikulation | Hohe Reibegeräusche mit angepasster Zielklangfarbe teilweise erhalten. Standard 65 %. |
| Luftigkeit | Zusätzliches gefiltertes Atemrauschen; die Altersfärbung wird separat durch Alterscharakter gesteuert |
| Helligkeit / Körper | Breite Klangkorrektur der Höhen beziehungsweise tiefen Frequenzen |
| Glättung | Übergangszeit bei Änderungen der Klangparameter; keine Rauschunterdrückung |
| Stimmbasis | Gemessene oder manuell eingestellte mittlere Grundfrequenz |
| Eingang / Ausgang | Pegel vor der Analyse beziehungsweise nach der Effektmischung |

Manuelle Helligkeit, Körper und Luftigkeit bleiben unabhängig von „Verwandlung“ einstellbar. Die gesamte Pitch-Verschiebung ist auf ±18, die Formantverschiebung auf ±9 Halbtöne begrenzt.

Balken ziehen, Mausrad verwenden oder den Zahlenbereich anklicken und einen Wert eingeben. Enter übernimmt, Escape verwirft. Rechtsklick setzt den Standardwert zurück. **Feinwerte Reset** stellt auch Alterscharakter, Rauheit und Stimmzittern zurück; Profil, Einmessung und Effektanteil bleiben erhalten. Die Reihenfolge der 22 speicher- und automatisierbaren Parameter ist gegenüber v0.2 unverändert.

<a id="vt-qualitaet"></a>

## Qualität und Latenz

| Qualität | 44,1 kHz | 48 kHz | 96 kHz |
| --- | --- | --- | --- |
| Live | 23,2 ms | 21,3 ms | 21,3 ms |
| Balanced | 46,4 ms | 42,7 ms | 42,7 ms |
| Studio | 92,9 ms | 85,3 ms | 85,3 ms |
| Detail | 185,8 ms | 170,7 ms | 170,7 ms |

Die Tabelle zeigt die **DSP-Verzögerung des Plugins**. Audiointerface und Hostpuffer kommen beim Live-Monitoring hinzu. Studio lässt mehr Reserve für höchstens 200 ms Gesamtlatenz. Detail kann bestimmte Klänge verbessern, aber schnelle Konsonanten stärker zeitlich verwischen. Beide Modi vergleichen. Ein Qualitätswechsel leert die Audiopuffer und kann kurz unterbrechen.

REAPER erhält die Verzögerung für den Latenzausgleich. Der Originalvergleich verwendet denselben Zeitversatz und umgeht Effektpegel und Begrenzer; Effektanteil 0 % behält dagegen die eingestellten Pegel und den Begrenzer bei. Der Begrenzer ist kein Lautheitsabgleich.


<a id="vt-pruefung"></a>

## Prüfung und Grenzen

`LautFunk_Voice_Transformer_v1.0_Pruefbericht.json` dokumentiert 32 bestandene Prüfungen aus dem nativen REAPER-7.81-Batch-Konverter unter Linux: automatische und manuelle Einmessung, wiederholte Messung, Abbruch, Zeitüberschreitung, neutrale Rekonstruktion, Sampleraten, Stille, Extremwerte, Profiltonhöhen und den Vergleich gleitender Testtöne zwischen v0.2 und v1.0.


Der Effekt bleibt eine eigenständige spektrale STFT-/Pitch-/Formant-Verarbeitung. Rubber Band R3, WORLD und neuronale Voice Conversion sind nicht eingebaut. Große Verschiebungen, raues Lachen, Flüstern oder überlagerte Stimmen bleiben anspruchsvoll. Mehr Alterscharakter ist deshalb nicht automatisch natürlicher; für den ersten Versuch bei 65 % bleiben.

<a id="vt-grundlage"></a>

## Fachliche Grundlage

Die Arbeit von [Laroche und Dolson zu spektraler Tonhöhenverschiebung](https://www.ee.columbia.edu/~dpwe/papers/LaroD99-pvoc.pdf) beschreibt die Bedeutung zusammenhängender Phasen für verschobene Spektralbereiche. v1.0 übernimmt nicht unverändert deren gesamten Algorithmus; die Korrektur betrifft die Zustandsfortführung der vorhandenen Implementierung.

[Reubold, Harrington und Kleber](https://www.phonetik.uni-muenchen.de/~jmh/papers/age.pdf) untersuchen Veränderungen von Grundfrequenz und Formanten mit dem Alter. Die Untersuchung von [Lee und Kollegen](https://karger.com/fpl/article/67/6/300/141284/Aging-Effect-on-Korean-Female-Voice-Acoustic-and) zeigt zugleich, dass ältere Stimmen nicht pauschal behauchter sind. Daraus folgt für dieses Klangdesign: Alter wird nicht allein durch zusätzliches Rauschen dargestellt. Die konkreten Profilwerte bleiben gestalterische Entscheidungen und müssen an den jeweiligen Stimmen beurteilt werden.

Technische Dokumentation: [JSFX](https://www.reaper.fm/sdk/js/js.php), [FFT und atomare Funktionen](https://www.reaper.fm/sdk/js/advfunc.php), [Latenzmeldung](https://www.reaper.fm/sdk/js/vars.php).

[↑ Zurück zum Inhaltsverzeichnis](#inhaltsverzeichnis)

---

<a id="softguard"></a>

# LautFunk SoftGuard v1.1

## Sanfte Pegelbegrenzung und automatische Sprecheranpassung

**LautFunk SoftGuard** ist ein JSFX-Plugin für REAPER, das Sprachaufnahmen gleichmäßiger und kontrollierbarer machen soll, ohne jede Lautstärkeschwankung hart abzuschneiden.

Im Mittelpunkt stehen zwei Aufgaben:

- **Sprecherbearbeitung:** Einzelne Stimmen werden vorsichtig im Pegel angepasst und gegen außergewöhnlich hohe Sample-Peaks abgesichert.
- **Master-/Bus-Bearbeitung:** Ein gemeinsam gemischtes Signal wird sanft begrenzt. Die endgültigen Veröffentlichungsziele für die Gesamtlautheit und True Peaks werden anschließend im REAPER-Render eingestellt.

Anders als ein kreativer Verzerrer soll SoftGuard möglichst wenig Eigenklang hinzufügen. Die natürliche Betonung und die Dynamik einer Stimme sollen weitgehend erhalten bleiben. Wie transparent die Bearbeitung tatsächlich klingt, hängt vom Eingangssignal und den gewählten Einstellungen ab.

**Version 1.1** besitzt eine vollständig eigene dunkle Benutzeroberfläche. Die grauen REAPER-Standardregler bleiben ausgeblendet; sämtliche 13 Plugin-Parameter sind über die eigene Oberfläche bedienbar und stehen REAPER weiterhin für Presets und Automation zur Verfügung.

<a id="softguard-prinzip"></a>

## Funktionsprinzip: Soft Knee statt harter Pegelkante

Bei einem Hard-Clipper würden Signalanteile oberhalb eines Grenzwerts abgeschnitten. SoftGuard arbeitet stattdessen mit einer **gleitend zunehmenden Pegelreduzierung**.

Die Begrenzung setzt schon **unterhalb des eingestellten Ceilings** ein: Wie früh und wie sanft die Reduzierung ansteigt, bestimmt der Parameter **Soft Knee**.

Wichtige technische Bausteine:

- **Soft Knee:** Übergang von kaum wahrnehmbarer zu stärkerer Begrenzung über einen einstellbaren Pegelbereich von 0 bis 18 dB.
- **Lookahead:** Ein kurzer Audiopuffer lässt den Limiter anstehende Pegelspitzen berücksichtigen. Einstellbar sind 2 bis 20 ms.
- **Stereo-Linking:** Linker und rechter Kanal erhalten die gleiche Limiter-Gain-Reduktion, sodass das Stereobild nicht durch unterschiedliche Limiter-Regelung verschoben werden soll.
- **Release:** Nach einer Pegelspitze wird die Reduktion geglättet zurückgenommen. Der Regler reicht von 40 bis 500 ms.
- **Sample-Peak-Schutz:** Eine zusätzliche Ausgangsbegrenzung hält den Sample-Peak-Pegel innerhalb des gewählten Ceilings. Bei sehr extremen Eingangssignalen kann dieser Sicherheitsmechanismus dennoch abrupter eingreifen als die eigentliche Soft-Knee-Kennlinie.

Der Auto-Leveler ist von dieser Spitzenbegrenzung getrennt. Er reagiert deutlich langsamer als der Limiter und soll Unterschiede in der durchschnittlichen Sprachlautheit ausgleichen, nicht einzelne Silben wegdrücken.

<a id="softguard-modi"></a>

## Sprecher- und Master-Modus

Oben in der Oberfläche gibt es zwei Schaltflächen:

### SPRECHER / EINZELSPUR

Dieser Modus ist für eine einzelne Sprachspur vorgesehen, beispielsweise eine getrennte Mikrofonaufnahme in einer Podcastproduktion.

**Werkseinstellungen:**

| Einstellung | Wert | Zweck |
| --- | --- | --- |
| Aktivsprache-Ziel | ca. **−18 LUFS** | Näherungsweises Ziel während aktiver Sprache |
| Sample Peak Ceiling | **−12 dBFS** | Begrenzung außergewöhnlicher Spitzen |
| Auto-Leveler | **An** | Langsamer Ausgleich der Sprachlautheit |
| Maximale Leveler-Anpassung | **±9 dB** | Verhindert zu starke automatische Verstärkung oder Absenkung |
| Aktivitätsschwelle | ca. **−38 LUFS** | Verhindert, dass der Leveler in Sprechpausen gezielt Hintergrundgeräusche hochzieht |

Das Ziel von −18 LUFS ist **kein garantierter Integrated-LUFS-Wert** für die komplette Spur. Es ist ein Regelziel auf Basis einer geglätteten, K-gewichteten Lautheitsschätzung. Eine Stimme kann je nach Sprechweise, Pausen, Dynamik und Aufnahmepegel davon abweichen.

### MASTER / BUS

Dieser Modus ist für einen Sprachbus oder die fertige Sprechersumme vorgesehen.

**Werkseinstellungen:**

| Einstellung | Wert | Zweck |
| --- | --- | --- |
| Master Sample Peak Ceiling | **−1 dBFS** | Echtzeit-Sample-Peak-Begrenzung |
| Master Auto-Leveler | **Aus** | Vermeidet eine zusätzliche laufende Lautheitskorrektur als Standard |
| Optionales Live-Lautheitsziel | ca. **−14 LUFS** | Nur relevant, wenn der Master-Leveler ausdrücklich eingeschaltet wird |

**Wichtig:** Die Master-Anzeige des Plugins ist **keine normgerechte Messung von Integrated LUFS**. Auch das Limiter-Ceiling von −1 dBFS ist **kein True-Peak-Limit**. Für das eigentliche Podcast-Mastering wird daher die REAPER-Renderfunktion eingesetzt.

Das separate Render-Skript unterstützt als Startwerte:

- **−14 LUFS-I** für die integrierte Lautheit der vollständigen Datei.
- **−1 dBTP** als True-Peak-Obergrenze. Dieser Wert bietet für anschließende MP3- und AAC-Kodierung mehr Reserve als −0,1 dBTP.

Wer −0,1 dBTP verwenden möchte, kann den Zielwert im Render-Skript entsprechend ändern. Nach der Kodierung sollten die tatsächlichen Peaks überprüft werden.

<a id="softguard-bedienung"></a>

## Bedienelemente und Anzeigen

SoftGuard v1.1 verwendet ein dunkelblaues, skalierbares Interface mit türkisfarbenen Anzeigen. Es orientiert sich an der Gestaltung anderer LautFunk-Audioeffekte.

Die grauen Standardregler von REAPER sind ausgeblendet. Sämtliche Einstellungen können **direkt in der Plugin-Oberfläche** mit der Maus verändert werden: Regler anklicken und ziehen oder das Mausrad für einzelne Schritte verwenden.

| Bedienelement | Funktion |
| --- | --- |
| Sprecher / Einzelspur | Aktiviert das Sprachspur-Profil |
| Master / Bus | Aktiviert die Bearbeitung für Summen- oder Masterspuren |
| Aktivsprache-Ziel | Näherungsweises Lautheitsziel des Sprecher-Levelers |
| Live-Lautheitsziel | Näherungsweises Ziel des optionalen Master-Levelers |
| Voice Ceiling | Sample-Peak-Obergrenze für Einzelsprecher |
| Master Ceiling | Sample-Peak-Obergrenze für Master/Bus |
| Soft Knee | Breite des weichen Übergangs unterhalb des Ceilings |
| Lookahead | Vorausschauzeit der Limiter-Verarbeitung; erzeugt eine entsprechende Verzögerung |
| Limiter Release | Geschwindigkeit, mit der die Pegelreduzierung nachlässt |
| Maximale Anpassung | Zulässiger Verstärkungs-/Absenkungsbereich des Auto-Levelers |
| Aktivitäts-Schwelle | Mindestlautheit, ab der sich der Auto-Leveler neu orientiert; kein Noise Gate |
| Auto-Leveler | Aktiviert/deaktiviert den langsamen Sprecher-Pegelabgleich |
| Master Leveler | Optionaler, standardmäßig deaktivierter Live-Pegelabgleich im Master-Modus |
| Bypass | Umgeht die Klangbearbeitung, behält aber den Latenzausgleich bei |

### Live-Anzeigen

Die Oberfläche zeigt zusätzlich:

- **Kurzzeit-Pegel:** geglättete, K-gewichtete Lautheitsschätzung (keine LUFS-I-Messung).
- **Leveler-Gain:** aktuelle Verstärkung oder Absenkung durch den Auto-Leveler in dB.
- **Limiter-Reduktion:** aktuelle Gain-Reduktion in dB.
- **Ausgangs-Sample-Peak:** momentaner Sample-Peak-Pegel in dBFS.
- **Aktuelles Ceiling:** wirksame Sample-Peak-Obergrenze des gewählten Modus.

Die **13 REAPER-Parameter** bleiben trotz ausgeblendeter Standardregler speicherbar und automatisierbar. Änderungen im eigenen Interface werden an die Parametersteuerung von REAPER weitergegeben.

<a id="softguard-workflow"></a>

## Empfohlener Podcast-Workflow

Ein sinnvolles Projekt mit zwei getrennt aufgenommenen Sprecherstimmen lässt sich so aufbauen:

1. **Mikrofonspur A:** SoftGuard im Modus **Sprecher / Einzelspur** verwenden. Mit −18 LUFS als Näherungsziel aktiver Sprache und −12 dBFS als Sample-Peak-Ceiling beginnen.
2. **Mikrofonspur B:** Eine zweite Instanz mit denselben Ausgangswerten einsetzen. Unterschiedliche Mikrofonpegel, Sprechweisen und Abstände können bei Bedarf individuell korrigiert werden.
3. **Sprachbus:** Beide Spuren zusammenführen. Die Summe zweier Signale kann höhere Spitzen erzeugen als die Einzelspuren; deshalb die Bus- und Masterpegel kontrollieren.
4. **Master:** SoftGuard im Modus **Master / Bus** verwenden. Den zusätzlichen Master-Leveler zunächst ausgeschaltet lassen, damit die Stimme nicht mehrfach automatisch nachgeregelt wird.
5. **Rendern:** Die fertige Folge über REAPER auf **−14 LUFS-I** normalisieren und mit **−1 dBTP** als True-Peak-Grenze ausgeben. Das beiliegende Lua-Skript vereinfacht das Setzen dieser Renderziele.
6. **Kontrolle:** Den Export auf Lautheit, True Peaks und hörbare Nebenwirkungen wie Pumpen, überbetonte Atmer oder verzerrte Konsonanten prüfen. Bei MP3/AAC möglichst auch die kodierte Datei überprüfen.

Die Werte sind **empfohlene Startpunkte** und keine Pflichtwerte für jede Aufnahme. Insbesondere bei stark wechselnden Sprechabständen oder ausgeprägter Dynamik kann eine ergänzende manuelle Lautstärkeautomation sinnvoller sein, als den Auto-Leveler aggressiver einzustellen.

<a id="softguard-installation"></a>

## Installation und optionales Render-Skript

Im SoftGuard-v1.1-Paket befinden sich:

```
Effects/
└── LautFunk/
    └── LautFunk_SoftGuard.jsfx
Scripts/
└── LautFunk_Render_Ziele.lua
README_DE.txt
```

### JSFX installieren

1. In REAPER **Options → Show REAPER resource path in explorer/finder** öffnen.
2. `LautFunk_SoftGuard.jsfx` nach `Effects/LautFunk/` kopieren.
3. Falls eine ältere SoftGuard-Version vorhanden ist, ihre Datei vorher sichern und ersetzen.
4. REAPER neu starten oder den Effekt neu laden. Im FX-Browser nach **LautFunk SoftGuard** suchen.
5. Über die beiden Schaltflächen oben zwischen **Sprecher** und **Master** wechseln.

### Lua-Skript für den Export

Das optionale Skript `LautFunk_Render_Ziele.lua` wird über die **Aktionsliste** von REAPER geladen (Actions → Show action list → ReaScript laden).

Beim Start fragt es nach zwei Zielwerten:

- **Integrated LUFS**, voreingestellt auf `-14`
- **True Peak dBTP**, voreingestellt auf `-1.0`

Das Skript setzt diese Normalisierungs- und Brickwall-True-Peak-Ziele in den Render-Einstellungen des aktuellen Projekts. **Es startet keinen Render**, ändert nicht das Ausgabeformat und bearbeitet die Quellspuren nicht. Die Werte im Renderdialog vor dem Export kontrollieren.

Das JSFX-Plugin funktioniert ohne das Lua-Skript. Für die endgültige LUFS-I-/True-Peak-Begrenzung müssen dann die entsprechenden REAPER-Renderoptionen von Hand eingestellt werden.

<a id="softguard-grenzen"></a>

## Messung, Latenz und technische Grenzen

- Die Lautheitsschätzung im Plugin orientiert sich an einer **K-gewichteten Messung** und an zeitlich geglätteter Energie. Sie ersetzt **keine vollständige, normgerechte LUFS-I-Analyse** mit der dazugehörigen Programmauswertung und Gating-Logik.
- Das Plugin begrenzt **Sample Peaks**, nicht direkt **True Peaks** zwischen den Samples. Der spätere True-Peak-Schutz im Renderdialog ist deshalb kein optionaler Ersatz für einen Test, sondern Bestandteil des empfohlenen Mastering-Ablaufs.
- **Lookahead erzeugt Latenz.** Bei den Werkseinstellungen beträgt die gemeldete DSP-Verzögerung ungefähr 6 ms; hinzu kommen die üblichen Puffer- und Hardwarelatenzen. REAPER kann diese Plugin-Verzögerung bei der Wiedergabe ausgleichen.
- Der Auto-Leveler arbeitet absichtlich langsam. Er soll nicht jeden Lautstärkeunterschied innerhalb einer Silbe korrigieren; der Limiter kümmert sich um die Spitzen.
- Das **Aktivitäts-Gate** steuert nur die automatische Lautheitsanpassung; es schaltet das Audiosignal nicht stumm und ist keine Rauschunterdrückung.
- Ein zu hoher Gain-Bereich kann Hintergrundgeräusche und Atmer mit anheben. Wer ein möglichst natürliches Ergebnis möchte, sollte mit moderaten Einstellungen beginnen.
- Der Bypass gibt das zeitlich angepasste Originalsignal aus, damit beim Umschalten der zeitliche Versatz erhalten bleibt.

SoftGuard v1.1 wurde für REAPER als JSFX erstellt. Die aktuelle Version wurde vom Nutzer in REAPER ausprobiert und als funktionierend zurückgemeldet. Damit ist allerdings noch **keine messtechnische Zertifizierung** der LUFS- oder True-Peak-Eigenschaften verbunden.

Technische Referenzen: [REAPER JSFX](https://www.reaper.fm/sdk/js/js.php), [REAPER Render](https://www.reaper.fm/).

[↑ Zurück zum Inhaltsverzeichnis](#inhaltsverzeichnis)

---

<a id="playlist-player"></a>

# LautFunk Playlist Player v1.0 (VST3)

## MP3- und WAV-Playlists direkt in REAPER abspielen

Der **LautFunk Playlist Player** ist ein eigenes **VST3-Instrument für REAPER**, das Musikdateien direkt über eine Spur wiedergibt. Es ist insbesondere für **Hintergrundmusik in Livestreams**, Podcast-Einspieler und längere Musiklisten gedacht.

Im Gegensatz zu einer normalen REAPER-Timeline müssen die Musikdateien **nicht als Audio-Items auf Spuren gezogen** werden. Der Player besitzt eine eigene Playlist und eigene **Play-, Pause- und Stop-Schaltflächen**. Er steuert damit **nicht** automatisch den globalen REAPER-Transport.

**Eine Aufnahme ist nicht erforderlich.** Damit die Wiedergabe bei gestopptem REAPER-Transport funktioniert, muss REAPER das Plugin weiterhin mit Audiobuffern versorgen (siehe Einrichtung unten).

Version 1.0 wurde als **Windows-x64-VST3** und als **macOS-Universal-VST3** (Intel und Apple Silicon) mit GitHub Actions erfolgreich gebaut. Die Windows-Ausgabe wurde in REAPER verwendet; ein tatsächlicher Hör- und Funktionstest der macOS-Ausgabe ist noch nicht dokumentiert.

<a id="playlist-player-funktionen"></a>

## Funktionen und Einsatz

- **MP3 und WAV** aus dem Dateisystem laden, auch mehrere Dateien gleichzeitig und per Drag-and-drop.
- Titel in einer internen Playlist anzeigen; **Doppelklick** startet einen bestimmten Titel.
- Wiedergabe unabhängig von der REAPER-Aufnahmetaste bedienen.
- **Automatisch zum nächsten Titel** wechseln, auch bei geschlossenem Plugin-Fenster.
- **Repeat: AUS**, **Repeat: ENDLOS** oder **Repeat: 1 TITEL** wählen.
- **Zufall** aktivieren, um die Titelreihenfolge zu mischen.
- Einträge entfernen, die Liste leeren und Titel mit **Hoch/Runter** verschieben.
- Playlists als **M3U8** speichern und einlesen.
- **Gesamtspielzeit aller geladenen Titel** sowie Laufzeiten der einzelnen Stücke anzeigen.
- Aktuellen Titel, verstrichene Zeit, Gesamtdauer und Abspielfortschritt sehen.
- Player-Lautstärke in dB regeln; der Pegelparameter ist in REAPER **automatisierbar**.
- Playlists und ihre Einstellungen mit dem REAPER-Projekt speichern.

Die fertige Musik wird **als Stereo-Audio über die jeweilige REAPER-Spur** ausgegeben. Damit stehen Spurfader, FX-Kette, Sends, Busse und alle gewöhnlichen REAPER-Routingmöglichkeiten zur Verfügung.

<a id="playlist-player-installation"></a>

## Installation unter Windows und macOS

Der Playlist Player ist **kein JSFX**. Seine `.vst3`-Datei gehört deshalb **nicht** in den REAPER-Ordner `Effects`, sondern in den VST3-Pluginordner des Betriebssystems.

Die fertigen Plattformpakete findest du im GitHub-Release:

**[LautFunk Playlist Player v1.0.0 – Windows und macOS herunterladen](https://github.com/lautfunk/Reaper-FX-Plugins/releases/tag/playlist-v1.0.0)**

### Windows (64 Bit)

1. Das ZIP **`LautFunk-Playlist-Player-v1.0-Windows-x64.zip`** herunterladen und entpacken.
2. Den vollständigen Ordner **`LautFunk Playlist Player.vst3`** kopieren nach:

   ```text
   C:\Program Files\Common Files\VST3\
   ```

3. REAPER starten bzw. vollständig neu starten.
4. Falls das Plugin fehlt: **Options → Preferences → Plug-ins → VST** öffnen und einen erneuten Scan ausführen.
5. Im FX-Browser nach **LautFunk Playlist Player** suchen.

Wichtig: Unter Windows ist `.vst3` hier ein **Plugin-Bundle mit Unterordnern**. Nicht nur die darin liegende Binärdatei kopieren.

### macOS (Intel und Apple Silicon)

1. Das ZIP **`LautFunk-Playlist-Player-v1.0-macOS-Universal.zip`** herunterladen und entpacken.
2. Das Bundle **`LautFunk Playlist Player.vst3`** in das Benutzer-Pluginverzeichnis kopieren:

   ```text
   ~/Library/Audio/Plug-Ins/VST3/
   ```

3. REAPER neu starten und bei Bedarf die VST-Plugins erneut scannen.

Das macOS-Paket wurde als **Universal Binary** gebaut und enthält beide Architekturen (`arm64` und `x86_64`). Es ist **ad-hoc signiert, aber nicht von Apple notarisiert**. Abhängig von den macOS-Sicherheitseinstellungen kann beim ersten Laden eine Sicherheitsmeldung erscheinen. In diesem Fall die Herkunft des Pakets prüfen und die regulären macOS-Freigabemöglichkeiten verwenden.

**Linux:** Für den Playlist Player v1.0 wird in diesem Release **kein Linux-VST3-Paket** bereitgestellt. Die übrigen JSFX-Plugins sind davon nicht betroffen.

<a id="playlist-player-reaper"></a>

## In REAPER einrichten – ohne Aufnahme

1. In REAPER eine neue leere Spur erstellen, beispielsweise **`LAUTFUNK BACKGROUND MUSIC`**.
2. Über **FX** das Instrument **`VSTi: LautFunk Playlist Player`** zur Spur hinzufügen. Es sind **keine MIDI-Items** erforderlich.
3. Unter **Options → Preferences → Audio → Playback** die Option **Run FX when stopped** aktivieren, damit das Plugin auch bei gestopptem Projekttransport Audio verarbeiten kann.
4. Im Plugin über **`+ Dateien`** MP3-/WAV-Dateien hinzufügen oder Dateien in das Pluginfenster ziehen.
5. Auf **PLAY** klicken. Das Plugin spielt selbstständig ab; **Record** muss nicht gedrückt werden.
6. Die Musik über den **Spurfader**, die FX-Kette und gegebenenfalls **Sends** zum gewünschten Stream-Ausgang routen.

Die Plugin-Tasten **PLAY, PAUSE und STOP** steuern die Musik im Player und **nicht** die Haupt-Wiedergabe oder Aufnahme von REAPER.

**Wenn trotz PLAY kein Ton kommt:** REAPER-Audiogerät und Ausgangsrouting prüfen, die Option **Run FX when stopped** kontrollieren sowie Track-FX-Bypass, automatischen Bypass auf Stille und ggf. **Flush FX on stop** prüfen. Für den Test kann auch kurz die normale REAPER-Wiedergabe gestartet werden, um eine fehlende Audiobuffer-Versorgung einzugrenzen. Eine Aufnahme ist hierfür nicht nötig.

<a id="playlist-player-playlist"></a>

## Playlist laden, sortieren und speichern

### Musikdateien hinzufügen

Mit **`+ Dateien`** lassen sich mehrere lokale MP3-/WAV-Dateien auswählen. Alternativ funktioniert **Drag-and-drop** in das Plugin-Fenster. Die Reihenfolge der hinzugefügten Dateien entspricht zunächst ihrer Reihenfolge in der Playlist.

Ein **Doppelklick auf einen Listeneintrag** startet den entsprechenden Titel sofort. Ein einfacher Klick wählt ihn zum Bearbeiten aus.

### Reihenfolge verändern

**Hoch** und **Runter** verschieben den ausgewählten Titel um eine Listenposition. **Entfernen** löscht nur den gewählten Eintrag. **Leeren** leert die gesamte Playlist und stoppt die Wiedergabe.

### M3U8-Playlists

- **M3U8 speichern:** Schreibt die aktuelle Playlist in eine `.m3u8`-Datei. Der Export verwendet die vollständigen Dateipfade.
- **M3U8 laden:** Liest die in einer `.m3u8` hinterlegten Musikdateien ein und **fügt** gültige Einträge der vorhandenen Liste **hinzu**. Relative Dateipfade in der importierten Liste werden relativ zum Speicherort der M3U8-Datei aufgelöst.

Möchtest du die bisherige Playlist **ersetzen**, klicke zuerst auf **Leeren** und danach auf **M3U8 laden**.

### Speicherung mit REAPER-Projekten

Das Plugin merkt sich die Playlist-Einträge (Dateipfade), ihre Reihenfolge, den ausgewählten Titel, Repeat, Zufall und Lautstärke im Projekt. Beim erneuten Öffnen wird die Liste wiederhergestellt, **die Musik startet aus Sicherheitsgründen aber nicht automatisch**.

Die MP3- und WAV-Dateien werden **nicht in die VST3-Datei oder in die M3U8-Playlist eingebettet**. Wenn du Musikdateien verschiebst, umbenennst oder löschst, müssen die Dateipfade wieder passen. Die Dateianzeige kann fehlende Titel als **FEHLT** markieren.

<a id="playlist-player-bedienung"></a>

## Bedienelemente und Anzeigen

Die dunkel gestaltete Oberfläche ist in fünf Bereiche gegliedert: Dateiverwaltung, Playlist, aktueller Titel, Transportsteuerung sowie Wiedergabeoptionen/Lautstärke.

| Element in der Oberfläche | Bedeutung |
| --- | --- |
| **+ Dateien** | Eine oder mehrere MP3-/WAV-Dateien hinzufügen |
| **M3U8 laden** | Vorhandene Playlist einlesen und ihre Einträge hinzufügen |
| **M3U8 speichern** | Aktuelle Liste als M3U8-Datei exportieren |
| **Entfernen** | Ausgewählten Titel aus der Liste löschen |
| **Hoch / Runter** | Ausgewählten Titel in der Playlist verschieben |
| **Leeren** | Gesamte Playlist löschen |
| **Doppelklick auf einen Titel** | Gewählten Titel sofort starten |
| **`|<` (Zurück)** | Vorheriger Titel; nach mehr als 3 Sekunden Spielzeit zunächst aktuellen Titel neu starten |
| **PLAY** | Aktuellen Titel starten bzw. pausierte Wiedergabe fortsetzen |
| **PAUSE** | Player-Wiedergabe pausieren |
| **STOP** | Player-Wiedergabe anhalten und Position auf Titelanfang setzen |
| **`>|` (Weiter)** | Zum nächsten Titel wechseln |
| **Fortschrittsbalken** | Aktuelle Wiedergabeposition anzeigen und durch Ziehen ändern |
| **Repeat: AUS / ENDLOS / 1 TITEL** | Wiederholungsmodus festlegen |
| **Zufall** | Zufällige Abspielreihenfolge aktivieren |
| **Lautstärke** | Player-Ausgangspegel in dB; über REAPER automatisierbar |
| **Aktueller Titel** | Dateiname des laufenden Titels ohne Dateiendung |
| **Zeitangabe `mm:ss / mm:ss`** | Abgelaufene Spielzeit / Länge des aktuellen Titels |
| **Titelzeit in der Liste** | Gesamtlänge des jeweiligen MP3-/WAV-Titels |
| **GESAMTSPIELZEIT** | Summe der bekannten Dauern aller Titel in der Liste |
| **ENDLOS AKTIV** | Kennzeichnet die eingeschaltete Endlosschleife |

### Gesamtspielzeit richtig lesen

Die **Gesamtspielzeit** befindet sich **oberhalb der Titelliste**, direkt neben der Titelanzahl. Eine lange Playlist kann beispielsweise so angezeigt werden:

```text
127 TITEL  |  GESAMTSPIELZEIT  5:23:31
```

Das ist die **einmalige Gesamtdauer** aller erkannten Musikdateien, **nicht** die verbleibende Zeit bis zum Ende und **nicht** die Laufzeit bei aktivem Repeat. Im Endlosmodus ist die tatsächliche Gesamt-Abspieldauer unbegrenzt.

Beim Hinzufügen vieler Dateien werden die Laufzeiten schrittweise eingelesen. Bis alle Metadaten verfügbar sind, kann die Summe noch unvollständig sein. Nicht lesbare Dateien werden entsprechend markiert.

<a id="playlist-player-repeat"></a>

## Endloswiedergabe und Zufallsmodus

Das Auswahlfeld **Repeat** unten links besitzt drei Betriebsarten:

| Modus | Verhalten am Ende eines Titels bzw. der Playlist |
| --- | --- |
| **Repeat: AUS** | Spielt die Liste einmal durch und hält am Ende an |
| **Repeat: ENDLOS** | Springt nach dem letzten Titel wieder zum ersten und spielt die Liste erneut ab |
| **Repeat: 1 TITEL** | Wiederholt den aktuellen Titel fortlaufend |

**Werkseinstellung: ENDLOS.** Ist diese aktiv, steht rechts oberhalb der Playlist **ENDLOS AKTIV**.

Das Kontrollkästchen **Zufall** mischt die Wiedergabereihenfolge. Mit **Repeat: AUS** endet die Zufallsrunde, sobald alle Titel gespielt wurden. Mit **Repeat: ENDLOS** beginnt danach eine neue zufällige Runde.

**Hinweis:** Der automatische Titelwechsel wird über die interne Ablaufprüfung ausgelöst. Zwischen zwei Stücken kann dadurch eine **kurze Pause** entstehen. Version 1.0 besitzt **noch kein Crossfade** und garantiert keine samplegenau lückenlosen Übergänge.

<a id="playlist-player-livestream"></a>

## Beispiel: Hintergrundmusik im Livestream

Die Musikausgabe des Plugins kann genauso wie jedes andere REAPER-Instrument mit Mikrofonen und weiteren Spuren gemischt werden:

```text
Mikrofon A ───────────────┐
Mikrofon B ───────────────┼──► STREAM-BUS ──► OBS / Stream-Ausgang
                          │
Musikspur ────────────────┘
  LautFunk Playlist Player VST3
  → EQ / Limiter (optional)
  → Spurfader / Send
```

### Praxisablauf

1. Musikspur einrichten und ihren Pegel bewusst **unterhalb der Sprache** einstellen.
2. Eine Playlist mit Hintergrundmusik laden, **Repeat: ENDLOS** aktivieren.
3. Über den **FX-Button** auf der Musikspur bei Bedarf EQ, Lautheitsbearbeitung oder Limiter **nach** dem Player einfügen.
4. Lautstärke des Players und den REAPER-Spurfader separat nutzen: Der Player regelt den Plugin-Ausgang, der Fader die ganze Spur.
5. Den Stream-Ausgang kontrollieren und anschließend den Player mit **PLAY** starten. Aufnahme im Projekt ist nicht notwendig.

Der Player hat in Version 1.0 **noch kein automatisches Ducking**. Wenn die Musik beim Sprechen automatisch leiser werden soll, kann dies zunächst mit einem externen Kompressor und Sidechain-Routing in REAPER realisiert werden.

**Startpegel:** Der interne Lautstärkeparameter ist standardmäßig auf **−12 dB** eingestellt. Dies ist ein Ausgangspunkt, kein automatisch geeigneter Stream-Mix. Den tatsächlichen Pegel über die gesamte Signalkette kontrollieren und bei Bedarf weiter reduzieren.

<a id="playlist-player-grenzen"></a>

## Hinweise, technische Grenzen und Verfügbarkeit

- **Keine Aufnahme nötig:** Der Player arbeitet als VST3-Instrument und erzeugt sein Audiosignal direkt in der REAPER-FX-Kette. Es sind weder MIDI-Items noch Audio-Items erforderlich.
- **Kein eigener Audioausgang:** Der Sound wird über REAPERs Audiogerät und Routing ausgegeben; es gibt keinen separaten Standalone-Player.
- **Transport bei Stop:** Damit das Plugin bei gestopptem REAPER-Transport weiterläuft, müssen Host und Audiogerät weiterhin Audiobuffer bereitstellen. Dafür ist **Run FX when stopped** wichtig.
- **Kein Crossfade / Ducking:** Diese Funktionen gehören nicht zu v1.0.
- **Mögliche Übergangspausen:** Ein automatischer Titelwechsel ist nicht als garantierter Gapless-Player ausgelegt.
- **Externe Dateipfade:** Gespeicherte Playlists benötigen weiterhin Zugriff auf die Originaldateien.
- **Plattformen:** GitHub Actions hat die Windows-x64- und macOS-Universal-Versionen erfolgreich kompiliert. Ein nativer macOS-Funktionstest ist noch offen.
- **Signierung:** Das macOS-VST3 wurde ad-hoc signiert, ist aber nicht durch Apple notarisiert.
- **Framework:** Der Player ist in C++ mit **JUCE 9.0.4** entwickelt. Bei öffentlicher Verteilung gelten die jeweiligen JUCE-Lizenzbedingungen; AGPLv3- bzw. kommerzielle Lizenzoptionen vor der Weiterverwendung beachten.

**Download und Quellcode:** [GitHub – LautFunk REAPER FX Plugins](https://github.com/lautfunk/Reaper-FX-Plugins) · [Playlist Player v1.0.0 Release](https://github.com/lautfunk/Reaper-FX-Plugins/releases/tag/playlist-v1.0.0)

[↑ Zurück zum Inhaltsverzeichnis](#inhaltsverzeichnis)

---

<a id="fartsynth"></a>

# LautFunk FartSynth 61 v1.0

## Parametrische Furzsynthese auf 61 MIDI-Tasten

Der **LautFunk FartSynth 61** ist kein Sampleplayer.

Die Klänge werden innerhalb der Synthese-Engine aus analytisch erzeugten Klangbausteinen und neu generierter Resttextur aufgebaut.

Die Engine erzeugt ihre Klänge vollständig innerhalb der Synthese-Engine und lädt beim Spielen keine externen Audiodateien.

Technisch handelt es sich deshalb um eine:

**referenzgebundene parametrische Resynthese**

Version 1.0 besitzt zwei unterschiedliche Spielmodi:

1. **ALLE 12**\
   Zwölf unterschiedliche Klangcharaktere werden gemeinsam über die Tastatur verteilt.
2. **EIN CHARAKTER**\
   Ein einzelner Klangcharakter erhält die vollständige Variantenbelegung über alle 61 Tasten.

Beim Laden startet Version 1.0 automatisch im Modus:

**ALLE 12**

---

<a id="fartsynth-alle-12"></a>

# Modus „ALLE 12“

MIDI **36 bis 95** wird in zwölf Gruppen aus jeweils fünf aufeinanderfolgenden Halbtönen aufgeteilt.

Dabei werden selbstverständlich auch die schwarzen Tasten verwendet.

Jede Gruppe repräsentiert einen eigenen Klangcharakter.

| **Gruppe** | **Charakter**     | **MIDI** |
| ---------- | ----------------- | -------- |
| 01         | Referenz          | 36–40    |
| 02         | Tiefer            | 41–45    |
| 03         | Wechselmuster     | 46–50    |
| 04         | Runder Plopp      | 51–55    |
| 05         | Lockeres Flattern | 56–60    |
| 06         | Feuchtes Blubbern | 61–65    |
| 07         | Arm-Raspel        | 66–70    |
| 08         | Trocken / Kurz    | 71–75    |
| 09         | Blechern          | 76–80    |
| 10         | Tiefes Poltern    | 81–85    |
| 11         | Hohes Schnarren   | 86–90    |
| 12         | Dreifach-Brrap    | 91–95    |

Die fünf Tasten jeder Gruppe besitzen dieselbe grundlegende Bedeutung:

| **Position** | **Variante** | **Wirkung**                                                        |
| ------------ | ------------ | ------------------------------------------------------------------ |
| 1            | Original     | Grundform des jeweiligen Charakters                                |
| 2            | Kurz         | Stark verkürzt und enger geformt                                   |
| 3            | Tief         | Breiter, langsamer und länger                                      |
| 4            | Schnell      | Kompakter und schneller                                            |
| 5            | Wild         | Bewegter, länger und mit stärkerem Geräusch- und Schwingungsanteil |

---

## Die 61. Taste: Zufallsmodus

**MIDI 96** besitzt im Modus „ALLE 12“ eine besondere Funktion.

Sie ist die:

**Zufallstaste**

Beim Spielen werden sämtliche **60 Charakter-/Variantenkombinationen** automatisch durchmischt.

Dabei gilt:

- jede Kombination erscheint einmal
- anschließend wird neu gemischt
- innerhalb eines Durchlaufs gibt es keine Wiederholung
- zwischen zwei Durchläufen wird dieselbe Kombination nicht unmittelbar erneut gespielt

Zusätzlich bleiben die normalen Klangvariationen und Humanize-Funktionen aktiv.

Dadurch erzeugt auch die Zufallstaste nicht bei jedem Durchlauf exakt identische Ergebnisse.

---

<a id="fartsynth-ein-charakter"></a>

# Modus „EIN CHARAKTER“

Durch Anklicken eines Charakterfeldes wird automatisch in den Modus **EIN CHARAKTER** gewechselt.

Der gewählte Charakter steht anschließend auf allen 61 Tasten zur Verfügung.

Die Tastatur verwendet dabei die bereits aus Version 0.9 bekannte Variantenstruktur.

| **MIDI** | **Familie**  | **MIDI** | **Familie**      |
| -------- | ------------ | -------- | ---------------- |
| 36–39    | Reference    | 68–70    | Loose Bass       |
| 40–42    | Loose Flap   | 71–74    | Drooping         |
| 43–46    | Dry Pop      | 75–77    | Rising           |
| 47–49    | Long Flutter | 78–81    | False Start      |
| 50–53    | Stutter      | 82–84    | Unstable         |
| 54–56    | Air Leak     | 85–88    | Double Burst     |
| 57–60    | Wet Gurgle   | 89–92    | Triple Burst     |
| 61–63    | Fast Rattle  | 93–96    | Bathroom Monster |
| 64–67    | Tight Squeak |          |                  |

Über **ALLE 12** kann jederzeit wieder zur Gesamtbelegung gewechselt werden.

Die Schaltfläche **EIN CHARAKTER** ruft anschließend die zuletzt gewählte Einzelauswahl wieder auf.

Das Spielen im Gesamtmodus verändert diese gespeicherte Auswahl nicht.

---

<a id="fartsynth-regler"></a>

# FartSynth-Regler

| **Regler**       | **Funktion**                                                   |
| ---------------- | -------------------------------------------------------------- |
| Pressure         | Stärke des Klangereignisses und Einfluss auf die Detailbreite  |
| Pulse Rate       | Geschwindigkeit und damit auch Tonhöhe der gesamten Klanggeste |
| Timing Variation | Zeitliche Variationen bei neuen Anschlägen                     |
| Air Supply       | Zeitliche Dehnung der Klanggeste                               |
| Air Texture      | Stärke der Resttextur; 0 deaktiviert sie                       |
| Tail Sputter     | Form und Geschwindigkeit später Klangdetails                   |
| Humanize         | Variationen von Form, Timing und Lautstärke                    |
| Closure Ring     | Pegel kurzer schwingender Klanganteile                         |
| Body / Sharpness | Veränderung der Detailbreite und Klanghärte                    |
| Alternation      | Zusätzliche paarweise Zeitverschiebung                         |
| Output dB        | Geglätteter Ausgangspegel                                      |
| Voices           | Anzahl gleichzeitig möglicher Stimmen von 1 bis 12             |
| Release ms       | Ausklang nach dem Loslassen einer Taste                        |
| Bend Depth       | Stärke des Pitchbend-Einflusses                                |

Die grauen Standardregler von JSFX bleiben in der Benutzeroberfläche ausgeblendet.

Alle **17 Parameter** des Plugins sind automatisierbar.

Die Parameternummern der bisherigen Version wurden beibehalten. **Keyboard Mode** wurde als Parameter 17 ergänzt.

---

<a id="fartsynth-midi"></a>

# MIDI-Steuerung des FartSynth

Neben den Reglern lässt sich die Engine über verschiedene MIDI-Controller beeinflussen.

- **Velocity** → Stärke
- **CC1 / Modwheel** → Zeitvariation
- **CC11 / Expression** → Detailbreite
- **Pitchbend** → Geschwindigkeit beziehungsweise Pitch-Verlauf
- **Aftertouch** → zusätzliche Stärke
- **CC64** → Sustain/Haltepedal
- **CC120 / CC123** → Stimmen stoppen

Das Haltepedal hält eine Note, bis das Pedal wieder losgelassen wird.

Die eigentliche Klanggeste bleibt trotzdem endlich und läuft nicht unbegrenzt weiter.

Zum vollständigen Abspielen eines Klanges sollte eine Taste gehalten werden, bis die Klanggeste beendet ist.

Kurzes Antippen startet entsprechend früher die Release-Phase.

Für kontrolliertere Ergebnisse können insbesondere:

- Timing Variation
- Humanize

reduziert werden.

---

# Stimmen und Moduswechsel

Modus- und Charakterwechsel gelten ausschließlich für neu angeschlagene Noten.

Bereits laufende Stimmen behalten ihre ursprüngliche Zuordnung.

Dadurch funktionieren auch:

- Note-Off
- Sustain
- Release

korrekt weiter, wenn während eines gehaltenen Tons der Modus gewechselt wird.

Modus und Charakterauswahl werden zusammen mit den Pluginparametern im REAPER-Projekt beziehungsweise Preset gespeichert.

---

<a id="fartsynth-pruefung"></a>

# Technische Prüfung

Geprüft wurden unter anderem:

- alle 61 Zuordnungen des Gesamtmodus
- alle 732 Charakter-/Tastenkombinationen des Einzelmodus
- mehrere vollständige Zufallsdurchläufe
- laufende Stimmen während Moduswechseln
- Sustain-Pedal bei Moduswechseln
- Parameterspeicherung
- GUI-Klicks
- Ereignisverarbeitung
- Audiopuffer

Alle 61 Tasten lieferten bei 48 kHz endliche Audiosignale ohne Ereignispuffer-Überlauf.

Zusätzlich wurden **28 native Audioregressionen des Einzelmodus bitgenau mit Version 0.9 verglichen**.

REAPER selbst war nicht Bestandteil dieser automatisierten Testumgebung.

Die Benutzeroberfläche wurde offscreen ausgeführt und visuell kontrolliert.

Für den normalen Einsatz ist ausschließlich die eigentliche JSFX-Datei erforderlich.

Der zusätzliche Source-Ordner enthält den reproduzierbaren Builder und die Prüfprogramme.

---

[↑ Zurück zum Inhaltsverzeichnis](#inhaltsverzeichnis)

<a id="installation"></a>

# JSFX-Installation in REAPER

Die LautFunk-Sammlung enthält **JSFX-Plugins** und den separat installierbaren **Playlist Player als VST3-Instrument**.

**JSFX** werden in den REAPER-Ressourcenordner `Effects` kopiert. **Der Playlist Player als VST3** wird in den VST3-Ordner des Betriebssystems installiert (siehe [Playlist Player – Installation](#playlist-player-installation)).

Für die JSFX-Dateien genügt das Kopieren in den REAPER-Ordner:

`Effects`

Die folgenden JSFX-Installationsschritte gelten **nicht** für den Playlist Player als VST3.

## Empfohlene Methode

In REAPER:

**Options → Show REAPER resource path in explorer/finder**

beziehungsweise sinngemäß in einer deutschen Oberfläche:

**Optionen → REAPER-Ressourcenpfad im Explorer/Finder anzeigen**

REAPER öffnet anschließend den persönlichen Ressourcenordner.

Darin befindet sich:

```
Effects

```

Wir empfehlen, darin einen eigenen LautFunk-Unterordner anzulegen:

```
REAPER/
└── Effects/
    └── LautFunk/
        ├── LautFunk_Digital_Glitch
        ├── LautFunk_Voice_Scrambler
        ├── LautFunk_SoftGuard.jsfx
        └── LautFunk_FartSynth_61_v1.0.jsfx

```

Diese Struktur hält den FX-Browser übersichtlich.

---

<a id="installationspfade"></a>

# Typische JSFX-Installationspfade für JSFX

Die tatsächlichen Pfade können abhängig von Betriebssystem, REAPER-Version und einer eventuell verwendeten portablen Installation abweichen.

Der Weg über **Show REAPER resource path** ist deshalb grundsätzlich zu bevorzugen.

## Windows

Typischerweise:

```
%APPDATA%\REAPER\Effects\

```

beziehungsweise:

```
C:\Users\DEIN-BENUTZERNAME\AppData\Roaming\REAPER\Effects\

```

Zum Beispiel:

```
C:\Users\DEIN-BENUTZERNAME\AppData\Roaming\REAPER\Effects\LautFunk\

```

## macOS

Typischerweise:

```
~/Library/Application Support/REAPER/Effects/

```

## Linux

Typischerweise:

```
~/.config/REAPER/Effects/

```

Bei einer portablen REAPER-Installation befindet sich der `Effects`-Ordner innerhalb des jeweiligen portablen REAPER-Ressourcenverzeichnisses.

---

<a id="plugins-laden"></a>

# Plugins in REAPER laden

Nach dem Kopieren bzw. Installieren des jeweiligen Plugins:

1. REAPER starten beziehungsweise zu REAPER zurückkehren.
2. Eine Audio- oder MIDI-Spur auswählen.
3. Auf **FX** klicken.
4. Im FX-Browser nach `LautFunk` suchen.
5. Das gewünschte Plugin auswählen.

Zum Beispiel:

```
LautFunk Digital Glitch

```

```
LautFunk Voice Scrambler

```

oder:

```
LautFunk SoftGuard

```

oder:

```
LautFunk FartSynth 61

```

oder (nach separater VST3-Installation):

```text
LautFunk Playlist Player
```

Falls ein Plugin nicht sofort angezeigt wird, kann der FX-Browser geschlossen und erneut geöffnet werden.

Alternativ REAPER neu starten beziehungsweise die FX-Liste aktualisieren. Beim Playlist Player gegebenenfalls unter **Preferences → Plug-ins → VST** einen VST-Rescan durchführen.

Beim FartSynth muss zusätzlich:

- eine MIDI-Spur scharf geschaltet
- das Monitoring aktiviert

werden.

Auch die virtuelle Bildschirmtastatur benötigt eine laufende Audioverarbeitung.

---

<a id="anforderungen"></a>

# Anforderungen

- **REAPER** mit JSFX-Unterstützung für die JSFX-Plugins bzw. mit VST3-Unterstützung für den Playlist Player
- **JSFX-Plugins:** Windows, macOS oder Linux; keine zusätzliche VST-Installation
- **Playlist Player v1.0:** Windows x64 oder macOS (Intel/Apple Silicon); separate VST3-Installation
- **Playlist Player:** Zugriff auf lokale MP3-/WAV-Dateien und ein aktives REAPER-Audiogerät
- Für den **fertigen Playlist Player** ist keine separate JUCE-Installation nötig; für das **Kompilieren des Quellcodes** werden CMake, C++-Compiler und JUCE benötigt

Beim FartSynth können sehr dichte Klangereignisse mit vielen gleichzeitig aktiven Stimmen entsprechend mehr Rechenleistung benötigen.

Falls erforderlich:

- Stimmenanzahl reduzieren
- Audiopuffer vergrößern

Die Werkseinstellung des FartSynth verwendet acht Stimmen.

---

<a id="einsatzbereiche"></a>

# Einsatzbereiche

Die LautFunk Plugins wurden für kreative Audioanwendungen und für die kontrollierte Bearbeitung von Sprachaufnahmen entwickelt.

Geeignet sind sie unter anderem für:

- Podcasts
- Hörspiele
- Livestreams
- YouTube-Produktionen
- Radio- und Funk-Simulationen
- elektronische Musik
- Vocal-Effekte
- Sounddesign
- Intro-Effekte
- Übergänge
- Comedy
- Satire
- experimentelle Audioproduktionen
- Sprecher-Pegelabgleich
- Podcast-Mastering-Vorbereitung
- transparente Dynamikbearbeitung und Soft-Knee-Limiting
- Hintergrundmusik über eine Playlist auf eigener REAPER-Spur
- M3U8-basierte Musiklisten und Endloswiedergabe für Livestreams

---

[↑ Zurück zum Inhaltsverzeichnis](#inhaltsverzeichnis)

<a id="ueber-lautfunk"></a>

# Über LautFunk

Die Plugins entstanden ursprünglich für Audio-, Podcast- und Sounddesign-Produktionen von **LautFunk**.

Der Schwerpunkt liegt nicht darauf, historische Hardware oder reale Übertragungssysteme perfekt zu simulieren.

Stattdessen werden charakteristische Klangideen aufgegriffen und als flexibel einsetzbare Werkzeuge für REAPER umgesetzt. Mit SoftGuard gehört auch ein Werkzeug für kontrollierte, möglichst transparente Sprachbearbeitung zum Projekt. Der Playlist Player ergänzt das Angebot um die direkte Musik- und Playlist-Wiedergabe innerhalb von REAPER.

Mal kontrolliert.

Mal experimentell.

Und manchmal vollkommen absurd.

**Audio muss nicht immer sauber sein, um interessant zu klingen.**
