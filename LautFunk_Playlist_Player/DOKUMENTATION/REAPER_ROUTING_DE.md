# REAPER – Stereo-Mix und optional getrennte Audioausgänge

Diese Anleitung gilt für den **Release-Kandidaten v2.3**. Der Modus mit getrennten Ausgängen ist **optional** und benötigt einen VST3-Host mit Multi-Output-Unterstützung.

## Einfacher Standardmodus

1. In REAPER eine Spur erstellen und das Plugin als FX laden.
2. Oben auf **AUDIO-ROUTING** klicken.
3. **Standard: Playlist + Soundboard auf Stereo 1/2** wählen.

Damit laufen Playlist-Musik und Soundboard gemeinsam durch die beiden Ausgänge 1/2. Du brauchst **keine weiteren Spuren, Sends oder Kanalzuweisungen**. Das ist die Werkseinstellung.

## Erweiterter Modus: zwei Stereoausgänge

| Signal | VST3-Ausgang | REAPER-Spurkanal |
| --- | --- | --- |
| Playlist-Musik | 1/2 | 1/2 |
| Soundboard-Samples | 3/4 | 3/4 |

**Wichtig:** Die Auswahl im Plugin aktiviert den zweiten Bus, aber sie garantiert **nicht**, dass die DAW die Kanäle 3/4 hörbar weiterleitet. Die Einstellung ist für Nutzer gedacht, die das Routing ihrer DAW kennen.

### Einrichtung in REAPER

1. Ein **neues Testprojekt** öffnen und das Plugin auf einer neuen Spur einsetzen.
2. Die Spur im REAPER-Routing auf **4 Kanäle** erweitern.
3. Im Plugin **AUDIO-ROUTING → Erweitert: Playlist 1/2, Soundboard 3/4** wählen.
4. Im **FX-Pin-Connector** prüfen, ob alle vier VST3-Ausgangskanäle auf die entsprechenden vier Trackkanäle gelegt sind. Manche Host- oder Kanal-Konfigurationen verlangen ein erneutes Öffnen des FX.
5. Für **Soundboard** eine zweite REAPER-Spur anlegen und einen **Receive** von der Plugin-Spur einstellen: Quelle **3/4**, Ziel **1/2**.
6. Den normalen 1/2-Musikanteil auf der Plugin-Spur belassen. **Nicht** gleichzeitig 3/4 auf den Master senden, wenn es bereits über die separate Sample-Spur geht.
7. Playlist-Musik starten und anschließend ein Sample auslösen. Musik muss auf dem Musikpfad, Sample auf dem zweiten Pfad hörbar sein.
8. Ducking testen: Es reduziert intern die Playlist-Musik, nicht die Einspieler.

### So sieht das Signal aus

```text
LautFunk VST3
├─ Playlist (Ducking) ── Out 1/2 ── REAPER-Kanal 1/2 ── Master / Musik
└─ Soundboard ────────── Out 3/4 ── REAPER-Kanal 3/4 ── Receive 3/4 -> 1/2 ── Samples
```

### Rückkehr zum gemeinsamen Stereoausgang

Im Plugin einfach **AUDIO-ROUTING → Standard: Playlist + Soundboard auf Stereo 1/2** auswählen. Dieser Modus ist jederzeit verfügbar und benötigt keine Zusatzspur.

### Was passiert, wenn die DAW das zweite Ausgangspaar nicht unterstützt?

Das Plugin versucht, den zweiten Stereo-Bus zu aktivieren. Gelingt dies nicht, **bleibt der Audio-Mix auf dem gemeinsamen Ausgang 1/2**. Die Oberfläche meldet, dass der Mehrkanal-Ausgang nicht zur Verfügung steht.

**Grenze:** Ein von der DAW als *aktiviert* gemeldeter Bus kann trotzdem unhörbar sein, wenn die DAW ihn nirgends hin routet. Das kann das Plugin nicht zuverlässig erkennen. Darum zeigt der Expertenmodus eine Warnung und lässt sich wieder auf Standard zurückstellen. Es wird nicht gleichzeitig auf beide Ausgangspaare gedoppelt, um Echo und Phasing zu vermeiden.

## Andere DAWs

Die Bezeichnungen für Multi-Out, Plugin-Pins, Sends und Instrument-Outs unterscheiden sich je nach DAW. In Hosts ohne solche Funktionen immer den **Stereo-Mix** verwenden. Wir versprechen Mehrkanal-Kompatibilität mit anderen Hosts erst nach einem konkreten Praxistest.

## Vor dem Livestream

- REAPER-Projekt speichern und neu öffnen.
- Wiedergabe bei gestopptem DAW-Transport prüfen.
- Musik- und Sample-Kanäle getrennt stummschalten und sicherstellen, dass der jeweils andere weiterhin funktioniert.
- Lautstärken und Peak-Limiter kontrollieren; es gibt noch keinen internen Summen-Limiter.
