# Lizenz, Urheberrecht und kostenlose Veröffentlichung

**Stand 2026-11-03 · Arbeitsdokument vor Veröffentlichung**

## Ausgangslage

Nach Angabe des Projektbetreibers werden die LautFunk-Plugins **kostenlos für alle** zur Verfügung gestellt und erzielen **0 € Einnahmen**. Es sind keine Plugin-Verkäufe geplant.

Das ist eine wichtige Voraussetzung für die Verwendung der **kostenlosen JUCE 9 Starter-Lizenz**. Für den LautFunk-eigenen Quellcode wurde inzwischen ausdrücklich **MIT** gewählt. Die eigenständigen Rechte und Bedingungen von JUCE bleiben unberührt.

## 1. JUCE-Framework

Das VST3 verwendet **JUCE 9.0.4**. JUCE ist sowohl unter **AGPLv3** als auch unter einer separaten JUCE-Lizenz verfügbar. Das Projekt soll nach Aussage des Betreibers die **JUCE Starter-Lizenz (kostenlos)** verwenden.

Die JUCE-9-EULA führt für Starter ein Limit von **20.000 USD Einnahmen oder Fördermitteln im maßgeblichen Zwölfmonatszeitraum** auf. Für eine individuelle Lizenz zählt die mit der Nutzung von JUCE erzielte Finanzierung aus allen Quellen, darunter auch Spenden, Sponsorengelder, Werbung und andere indirekte Erlöse. Bei Unternehmen können andere Regeln für den Umsatz der Rechtseinheit gelten. Auch die Anzahl tatsächlich entwickelnder Personen kann für die erforderlichen Lizenzplätze relevant sein.

Offizielle Quellen:

- https://juce.com/get-juce/
- https://juce.com/legal/juce-9-licence/

**Aktuelle Angaben des Betreibers:** 0 € Plugin-Einnahmen, kostenlose öffentliche Bereitstellung, kostenlose JUCE-Lizenz vorhanden.

**Vor dem finalen Release prüfen:** Die kostenlose Starter-Lizenz muss dem tatsächlichen Lizenzinhaber, der Anzahl der Framework-Entwickler und der Nutzung des Produkts entsprechen; der JUCE-9-EULA-Text bleibt maßgeblich. Keine Lizenzschlüssel, Kontodaten oder persönlichen Zugänge in ein öffentliches Repository schreiben.

## 2. MIT-Lizenz für den LautFunk-eigenen Quellcode

**Entscheidung vom 3. November 2026:** Der Projektbetreiber hat ausdrücklich bestätigt, dass der eigenständig entwickelte Quellcode des **LautFunk Playlist Player & Soundboard** unter der **MIT-Lizenz (SPDX: MIT)** veröffentlicht werden soll.

Die vollständige Lizenz liegt in [../LICENSE](../LICENSE), mit dem Copyright-Vermerk `Copyright (c) 2026 LautFunk contributors`.

**Geltungsbereich:** Diese MIT-Lizenz betrifft die im Verzeichnis `LautFunk_Playlist_Player/` enthaltenen, selbst entwickelten Quellen und zugehörigen Unterlagen. Sie **lizenziert weder JUCE noch fremde Komponenten neu** und gilt **nicht automatisch für die übrigen Plugins im übergeordneten Repository**.

Die MIT-Lizenz erlaubt Nutzung, Veränderung, Verbreitung, Unterlizenzierung und kommerzielle Weiterverwendung des eigenen Codes, sofern der Copyright- und Lizenzhinweis bei Kopien bzw. wesentlichen Teilen enthalten bleibt. Sie verlangt nicht, abgeleitete Werke wiederum als Open Source zu veröffentlichen.

**Wichtig:** Auch wenn der LautFunk-Code MIT-lizenziert ist, müssen alle, die JUCE verwenden, modifizieren oder daraus eigene JUCE-basierte Produkte bauen, die **JUCE-eigenen** Lizenzbedingungen selbst einhalten. Die kostenlose Starter-Lizenz des ursprünglichen Entwicklers wird dadurch nicht automatisch an Dritte übertragen. Externe Beispiele, Audiosamples und Marken sind nur erfasst, soweit sie tatsächlich vom LautFunk-Rechteinhaber stammen und der entsprechende Rechteumfang nachweisbar ist.

Die Entscheidung, Plugins kostenlos anzubieten, ist unabhängig davon: Eine MIT-Lizenz **verbietet** fremden Entwicklern kommerzielle Nutzung des LautFunk-eigenen Codes **nicht**.

## 3. Drittanbieterhinweise und Abgrenzungen

- **JUCE 9.0.4**: © jeweilige Rechteinhaber, separate Lizenzbedingungen (siehe Links oben).
- **VST3**: Das Plugin verwendet JUCEs VST3-Unterstützung; vor Veröffentlichung aktuelle Hinweise zur Steinberg-VST3-Lizenzierung und etwaigen Markenregeln prüfen.
- **Ultraschall Soundboard**: Nur konzeptionelle Inspiration; laut Projektangaben wurden keine Ultraschall-Quellcodedateien übernommen. Repo: https://github.com/Ultraschall/ultraschall-soundboard
- Keine Samples, Fotos, Musikstücke oder Logos von Dritten ohne entsprechende Rechte in Beispielpakete aufnehmen.
- **Bitfocus Companion / Elgato Stream Deck**: Lediglich Kompatibilität bzw. manuelle OSC-Anbindung; keine offizielle Partnerschaft oder Produktfreigabe behaupten.

## 4. Mindestangaben im öffentlichen GitHub Release

1. Produktname und Versionsnummer.
2. Plattform, Architektur und Installationspfad.
3. Hinweis „Kostenloser Download“ sowie **MIT-Lizenz für den LautFunk-Code und gesonderte JUCE-Lizenzbedingungen**.
4. JUCE-Version und Link zu den Original-Lizenzbedingungen.
5. Hinweise zu Dateipfaden, Lautstärke/Clipping, Host-Verhalten und optionalem Routing.
6. Changelog, bekannte Einschränkungen, Teststatus und Möglichkeit, Fehler zu melden.
7. Hinweis zur Apple-Signierung/Notarisierung; keine falsche Aussage, dass macOS-Builds notarisiert seien.

Diese Datei ist Projektorganisation, keine rechtsverbindliche Lizenz und keine individuelle Rechtsberatung.
