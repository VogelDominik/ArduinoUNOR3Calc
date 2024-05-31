ArduinoUNOR3_Calc


Projektübersicht

Dieses Projekt implementiert einen einfachen Taschenrechner, der über die serielle Schnittstelle zwischen einem Arduino UNO R3 Mikrocontroller und einem Windows-PC kommuniziert. Der Mikrocontroller führt die Berechnungen durch und sendet die Ergebnisse zurück an den PC.

Ordnerstruktur

Der Ordner ArduinoUNOR3_Calc enthält folgende Unterordner:

Code_ArduinoUNOR3: Dieser Ordner enthält den Code für den Arduino Mikrocontroller.

Code_Visual_Studio_2022: Dieser Ordner enthält den Projektordner für Visual Studio 2022. Der Code liegt in der main.cpp Datei.

Schritte zur Ausführung des Projekts

1. Arduino UNO R3 vorbereiten
Schließe den Arduino UNO R3 Mikrocontroller an den COM3-Port deines Computers an.
Falls COM3 nicht verfügbar ist, überprüfe den tatsächlichen COM-Port in der Arduino IDE unter Werkzeuge -> Port und passe den Code entsprechend an.

2. Arduino Code aufspielen
Öffne die Arduino IDE.
Gehe zu Datei -> Öffnen und wähle die Datei im Ordner Code_ArduinoUNOR3.
Stelle sicher, dass der richtige COM-Port ausgewählt ist (Werkzeuge -> Port).
Klicke auf den Upload-Button, um den Code auf den Arduino zu laden.

3. Visual Studio 2022 Projekt ausführen
Öffne Visual Studio 2022.
Gehe zu Datei -> Öffnen -> Ordner und wähle den Ordner Code_Visual_Studio_2022.
Stelle sicher, dass der COM-Port im main.cpp-Code korrekt auf den verwendeten Port eingestellt ist (standardmäßig COM3).
Klicke auf Strg + Umschalt + B, um das Projekt zu kompilieren.
Drücke F5, um das Projekt auszuführen.

4. Verwendung des Kalkulators
Nachdem das Terminal sich öffnet, kannst du arithmetische Ausdrücke eingeben (z.B. 34 * 72).
Drücke Enter, um die Berechnung ausführen zu lassen.
Das Ergebnis wird im Terminal angezeigt.

Hinweis
Stelle sicher, dass der richtige COM-Port sowohl in der Arduino IDE als auch im main.cpp-Code eingestellt ist. Falls der COM3-Port nicht verfügbar ist, finde den richtigen Port in der Arduino IDE und ändere den Code entsprechend.
