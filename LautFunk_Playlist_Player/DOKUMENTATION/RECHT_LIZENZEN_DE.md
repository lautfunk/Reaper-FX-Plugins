# Lizenz, Urheberrecht und kostenlose Veröffentlichung

**Stand 2026-11-03 · Arbeitsdokument vor Veröffentlichung**

## Ausgangslage

Nach Angabe des Projektbetreibers werden die LautFunk-Plugins **kostenlos für alle** zur Verfügung gestellt und erzielen **0 € Einnahmen**. Es sind keine Plugin-Verkäufe geplant.

Das ist eine wichtige Voraussetzung für die Verwendung der **kostenlosen JUCE 9 Starter-Lizenz**. Die freie Verfügbarkeit der Plugins allein ist aber **keine Lizenzbestimmung über den Quellcode**: Kostenlose Benutzung bedeutet nicht automatisch das Recht, Code zu verändern, umzubenennen oder weiterzuverkaufen.

## 1. JUCE-Framework

Das VST3 verwendet **JUCE 9.0.4**. JUCE ist sowohl unter **AGPLv3** als auch unter einer separaten JUCE-Lizenz verfügbar. Das Projekt soll nach Aussage des Betreibers die **JUCE Starter-Lizenz (kostenlos)** verwenden.

Die JUCE-9-EULA führt für Starter ein Limit von **20.000 USD Einnahmen oder Fördermitteln im maßgeblichen Zwölfmonatszeitraum** auf. Für eine individuelle Lizenz zählt die mit der Nutzung von JUCE erzielte Finanzierung aus allen Quellen, darunter auch Spenden, Sponsorengelder, Werbung und andere indirekte Erlöse. Bei Unternehmen können andere Regeln für den Umsatz der Rechtseinheit gelten. Auch die Anzahl tatsächlich entwickelnder Personen kann für die erforderlichen Lizenzplätze relevant sein.

Offizielle Quellen:

- https://juce.com/get-juce/
- https://juce.com/legal/juce-9-licence/

**Aktuelle Angaben des Betreibers:** 0 € Plugin-Einnahmen, kostenlose öffentliche Bereitstellung, kostenlose JUCE-Lizenz vorhanden.

**Vor dem finalen Release prüfen:** Die kostenlose Starter-Lizenz muss dem tatsächlichen Lizenzinhaber, der Anzahl der Framework-Entwickler und der Nutzung des Produkts entsprechen; der JUCE-9-EULA-Text bleibt maßgeblich. Keine Lizenzschlüssel, Kontodaten oder persönlichen Zugänge in ein öffentliches Repository schreiben.

## 2. Lizenz des LautFunk-eigenen Quellcodes

**Noch offen:** Unter welchen Bedingungen andere den eigenen C++-Quellcode weiterverwenden dürfen.

Mögliche Modelle:

- **Kostenlose Nutzung der kompilierten VST3-Datei:** Die Software darf gratis heruntergeladen und verwendet werden; Veröffentlichung des Quellcodes auf GitHub erteilt nicht automatisch eine allgemeine Weiterverwendungslizenz.
- **Freie/Open-Source-Lizenz für den eigenen Quellcode:** Lizenz ausdrücklich auswählen und mit JUCE-Starter-Bedingungen auf Vereinbarkeit prüfen, bevor eine Datei \`LICENSE\` hinzugefügt wird.

Die Lizenz für den eigenen Quellcode wird **nicht stillschweigend als MIT, GPL oder AGPL festgelegt**. Der Betreiber muss die beabsichtigten Weitergaberechte bestätigen.

Hinweis: Wenn stattdessen die **AGPLv3** als Lizenzgrundlage für JUCE verwendet wird, gelten deren Bedingungen einschließlich Quellcodepflichten. Diese Option sollte nicht unbeabsichtigt mit einer JUCE-Starter-Lizenz verwechselt werden.

## 3. Drittanbieterhinweise und Abgrenzungen

- **JUCE 9.0.4**: © jeweilige Rechteinhaber, separate Lizenzbedingungen (siehe Links oben).
- **VST3**: Das Plugin verwendet JUCEs VST3-Unterstützung; vor Veröffentlichung aktuelle Hinweise zur Steinberg-VST3-Lizenzierung und etwaigen Markenregeln prüfen.
- **Ultraschall Soundboard**: Nur konzeptionelle Inspiration; laut Projektangaben wurden keine Ultraschall-Quellcodedateien übernommen. Repo: https://github.com/Ultraschall/ultraschall-soundboard
- Keine Samples, Fotos, Musikstücke oder Logos von Dritten ohne entsprechende Rechte in Beispielpakete aufnehmen.
- **Bitfocus Companion / Elgato Stream Deck**: Lediglich Kompatibilität bzw. manuelle OSC-Anbindung; keine offizielle Partnerschaft oder Produktfreigabe behaupten.

## 4. Mindestangaben im öffentlichen GitHub Release

1. Produktname und Versionsnummer.
2. Plattform, Architektur und Installationspfad.
3. Hinweis „Kostenloser Download“ und **korrekte Nutzungs-/Quellcodelizenz**, sobald entschieden.
4. JUCE-Version und Link zu den Original-Lizenzbedingungen.
5. Hinweise zu Dateipfaden, Lautstärke/Clipping, Host-Verhalten und optionalem Routing.
6. Changelog, bekannte Einschränkungen, Teststatus und Möglichkeit, Fehler zu melden.
7. Hinweis zur Apple-Signierung/Notarisierung; keine falsche Aussage, dass macOS-Builds notarisiert seien.

Diese Datei ist Projektorganisation, keine rechtsverbindliche Lizenz und keine individuelle Rechtsberatung.
