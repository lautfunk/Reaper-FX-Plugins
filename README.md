# LautFunk REAPER FX Plugins

Kreative **JSFX-Plugins für REAPER** – entwickelt für Podcasts, Hörspiele, Sounddesign, elektronische Musik und experimentelle Audiobearbeitung.

Die LautFunk-Plugins sind keine klassischen Mixing-Werkzeuge, die möglichst unauffällig arbeiten sollen. Sie sind dafür gebaut, Audio gezielt zu verändern, zu verfremden, zu zerstören oder vollkommen neue Klänge zu erzeugen.

**Kaputt darf hier ausdrücklich gut klingen.**

> **Navigation:** Diese README ist umfangreich. Über das Inhaltsverzeichnis kannst du direkt zu jedem Plugin und zu den wichtigsten Unterkapiteln springen.

<a id="inhaltsverzeichnis"></a>

## Inhaltsverzeichnis

- [Enthaltene Plugins](#enthaltene-plugins)
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
  - [Hörvergleich](#vt-hoervergleich)
  - [Prüfung und Grenzen](#vt-pruefung)
  - [Fachliche Grundlage](#vt-grundlage)
- [LautFunk FartSynth 61 v1.0](#fartsynth)
  - [Modus „ALLE 12“](#fartsynth-alle-12)
  - [Modus „EIN CHARAKTER“](#fartsynth-ein-charakter)
  - [FartSynth-Regler](#fartsynth-regler)
  - [MIDI-Steuerung](#fartsynth-midi)
  - [Hörfolge und technische Prüfung](#fartsynth-pruefung)
- [Installation](#installation)
- [Typische Installationspfade](#installationspfade)
- [Plugins in REAPER laden](#plugins-laden)
- [Anforderungen](#anforderungen)
- [Einsatzbereiche](#einsatzbereiche)
- [Über LautFunk](#ueber-lautfunk)

<a id="enthaltene-plugins"></a>

## Enthaltene Plugins

Aktuell enthält das Projekt:

- **LautFunk Digital Glitch**\
  Erzeugt digitale Fehler, Stutter, Buffer-Freezes, Dropouts, Bitcrushing und chaotische Pitch-Effekte.
- **LautFunk Voice Scrambler**\
  Verfremdet Sprache mithilfe von Frequenzinversion, Split-Band-Scrambling, Funkrauschen und weiteren Radioeffekten.
- **LautFunk Voice Transformer v1.0**\
  Verändert Stimmen mit acht Klangprofilen, automatischer Einmessung sowie getrennten Reglern für Tonhöhe, Formanten und Stimmcharakter.
- **LautFunk FartSynth 61**\
  Ein vollständig synthetischer MIDI-Synthesizer mit 61 spielbaren Tasten und zwölf unterschiedlichen Klangcharakteren.

Alle Plugins laufen direkt als **JSFX in REAPER**. Eine zusätzliche VST-, VST3- oder CLAP-Installation ist nicht erforderlich.

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

Sarahs gelieferte Originalaufnahme ergibt im geprüften Anfangsausschnitt weiterhin **185 Hz / Mittel**. Das ist ein Ausschnittsergebnis; andere Sprechabschnitte können andere Werte liefern.

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

<a id="vt-hoervergleich"></a>

## Hörvergleich

`LautFunk_Voice_Transformer_v1.0_Hoerprobe.wav` enthält je 15 Sekunden aus derselben Originalaufnahme, mit 1,5 Sekunden Pause:

| Beginn | Abschnitt |
| --- | --- |
| 0:00,0 | Sarahs Original |
| 0:16,5 | Alter Mann v0.2 |
| 0:33,0 | Alter Mann v1.0 |
| 0:49,5 | Alte Frau v0.2 |
| 1:06,0 | Alte Frau v1.0 |
| 1:22,5 | Mann v1.0 |

Die Effektabschnitte sind native REAPER-Renderings mit Studio, 185 Hz / Mittel, 100 % Verwandlung und Effektanteil, Artikulation 65 %, Alterscharakter 65 %, Rauheit/Stimmzittern 0 %. Die v0.2-Referenzen stammen aus den gespeicherten Renderings dieser Einstellungen; sie sind nicht identisch mit den zuletzt hochgeladenen MP3-Exports unbekannter vollständiger Einstellungen. Die Abschnitte sind ungefähr auf gleichen RMS-Pegel gebracht. Identische wahrgenommene Lautheit ist damit nicht garantiert. Kurze Randblenden vermeiden Schnittknackser.

<a id="vt-pruefung"></a>

## Prüfung und Grenzen

`LautFunk_Voice_Transformer_v1.0_Pruefbericht.json` dokumentiert 32 bestandene Prüfungen aus dem nativen REAPER-7.81-Batch-Konverter unter Linux: automatische und manuelle Einmessung, wiederholte Messung, Abbruch, Zeitüberschreitung, neutrale Rekonstruktion, Sampleraten, Sprach-Renderings, Stille, Extremwerte, Profiltonhöhen und den Vergleich gleitender Testtöne zwischen v0.2 und v1.0.

Die Zeitüberwachung wurde mit den unveränderten Überwachungsanweisungen und einer gezielt abgelaufenen Uhr im EEL-Interpreter geprüft. Das ist kein Test echter GUI-Ereignisse. Die Oberfläche wurde im Code überprüft; Windows, echte Maus-/Tastaturbedienung, ein physisches Mikrofon und ein Echtzeit-CPU-Test mit verbindlichen Audiopufferfristen wurden hier nicht geprüft. Numerische Tests bestätigen keine vollständige Artefaktfreiheit und ersetzen den Hörvergleich nicht.

Der Effekt bleibt eine eigenständige spektrale STFT-/Pitch-/Formant-Verarbeitung. Rubber Band R3, WORLD und neuronale Voice Conversion sind nicht eingebaut. Große Verschiebungen, raues Lachen, Flüstern oder überlagerte Stimmen bleiben anspruchsvoll. Mehr Alterscharakter ist deshalb nicht automatisch natürlicher; für den ersten Versuch bei 65 % bleiben.

<a id="vt-grundlage"></a>

## Fachliche Grundlage

Die Arbeit von [Laroche und Dolson zu spektraler Tonhöhenverschiebung](https://www.ee.columbia.edu/~dpwe/papers/LaroD99-pvoc.pdf) beschreibt die Bedeutung zusammenhängender Phasen für verschobene Spektralbereiche. v1.0 übernimmt nicht unverändert deren gesamten Algorithmus; die Korrektur betrifft die Zustandsfortführung der vorhandenen Implementierung.

[Reubold, Harrington und Kleber](https://www.phonetik.uni-muenchen.de/~jmh/papers/age.pdf) untersuchen Veränderungen von Grundfrequenz und Formanten mit dem Alter. Die Untersuchung von [Lee und Kollegen](https://karger.com/fpl/article/67/6/300/141284/Aging-Effect-on-Korean-Female-Voice-Acoustic-and) zeigt zugleich, dass ältere Stimmen nicht pauschal behauchter sind. Daraus folgt für dieses Klangdesign: Alter wird nicht allein durch zusätzliches Rauschen dargestellt. Die konkreten Profilwerte bleiben gestalterische Entscheidungen und müssen an den jeweiligen Stimmen beurteilt werden.

Technische Dokumentation: [JSFX](https://www.reaper.fm/sdk/js/js.php), [FFT und atomare Funktionen](https://www.reaper.fm/sdk/js/advfunc.php), [Latenzmeldung](https://www.reaper.fm/sdk/js/vars.php).

[↑ Zurück zum Inhaltsverzeichnis](#inhaltsverzeichnis)

---

<a id="fartsynth"></a>

# LautFunk FartSynth 61 v1.0

## Parametrische Furzsynthese auf 61 MIDI-Tasten

Der **LautFunk FartSynth 61** ist kein Sampleplayer.

Die Klänge werden innerhalb der Synthese-Engine aus analytisch erzeugten Klangbausteinen und neu generierter Resttextur aufgebaut.

Die Engine basiert auf Analysedaten von Referenzaufnahmen, lädt beim Spielen jedoch keine WAV- oder MP3-Dateien.

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

# Hörfolge und technische Prüfung

Zum FartSynth gehört die Testdatei:

`LautFunk_FartSynth_61_v1.0_61_Tasten.wav`

Sie spielt im Modus **ALLE 12** sämtliche 61 Tasten nacheinander ab:

**MIDI 36 bis MIDI 96**

Die Aufnahme wurde mit den Werkseinstellungen und Velocity 104 erzeugt.

Die Audiodaten stammen direkt aus der tatsächlichen JSFX-Engine im **ysfx-Prüfhost**.

Für die Hörfolge wurden lediglich:

- Stille am Ende einzelner Töne gekürzt
- Pausen zwischen den Klängen eingefügt

Es erfolgte keine individuelle Klangbearbeitung oder Pegelanpassung.

Zusätzliche genaue Zeitmarken befinden sich in:

`LautFunk_FartSynth_61_v1.0_Hoerfolge.json`

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

# Installation

Alle LautFunk-Plugins sind **JSFX-Plugins für REAPER**.

Eine klassische Installation wie bei VST-, VST3- oder CLAP-Plugins ist deshalb nicht notwendig.

Die Plugin-Dateien müssen lediglich in den REAPER-Ordner:

`Effects`

kopiert werden.

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
        └── LautFunk_FartSynth_61_v1.0.jsfx

```

Diese Struktur hält den FX-Browser übersichtlich.

---

<a id="installationspfade"></a>

# Typische Installationspfade

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

Nach dem Kopieren der Dateien:

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
LautFunk FartSynth 61

```

Falls ein Plugin nicht sofort angezeigt wird, kann der FX-Browser geschlossen und erneut geöffnet werden.

Alternativ REAPER neu starten beziehungsweise die FX-Liste aktualisieren.

Beim FartSynth muss zusätzlich:

- eine MIDI-Spur scharf geschaltet
- das Monitoring aktiviert

werden.

Auch die virtuelle Bildschirmtastatur benötigt eine laufende Audioverarbeitung.

---

<a id="anforderungen"></a>

# Anforderungen

- **REAPER**
- Unterstützung für **JSFX / Jesusonic Effects**
- Windows, macOS oder Linux
- keine zusätzlichen VST-Abhängigkeiten
- keine externe Runtime erforderlich

Beim FartSynth können sehr dichte Klangereignisse mit vielen gleichzeitig aktiven Stimmen entsprechend mehr Rechenleistung benötigen.

Falls erforderlich:

- Stimmenanzahl reduzieren
- Audiopuffer vergrößern

Die Werkseinstellung des FartSynth verwendet acht Stimmen.

---

<a id="einsatzbereiche"></a>

# Einsatzbereiche

Die LautFunk Plugins wurden insbesondere für kreative Audioanwendungen entwickelt.

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

---

[↑ Zurück zum Inhaltsverzeichnis](#inhaltsverzeichnis)

<a id="ueber-lautfunk"></a>

# Über LautFunk

Die Plugins entstanden ursprünglich für Audio-, Podcast- und Sounddesign-Produktionen von **LautFunk**.

Der Schwerpunkt liegt nicht darauf, historische Hardware oder reale Übertragungssysteme perfekt zu simulieren.

Stattdessen werden charakteristische Klangideen aufgegriffen und als flexibel einsetzbare Werkzeuge für REAPER umgesetzt.

Mal kontrolliert.

Mal experimentell.

Und manchmal vollkommen absurd.

**Audio muss nicht immer sauber sein, um interessant zu klingen.**
