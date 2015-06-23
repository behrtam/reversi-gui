# Requirements

We got them in german ... sorry. Strikethrough indicates that this is already done.

## Anforderungen an Reversi

**Status 15/100**

- 5 Bonus Punkte bei Abgabe vor 21. Juli
- 15 Punkte durch Dozent für Gesamteinschätzung

### 1.1 Projektunabhängige Anforderungen (Punkte 2/15)

~~(1) Das Programm ist eine Qt-Anwendung mit einem Hauptfenster.~~ **(Punkte 1)**

(2) Die Größe des Fensters kann mit den üblichen Methoden verändert werden, das GUI passt sich der Größenveränderung automatisch an. (Punkte 1)

~~(3) Es gibt es einen Vollbild-Modus.~~ **(Punkte 1)**

(4) Die Anwendung ist lokalisiert und das Benutzerinterface ist in mind. zwei Sprachen (z.B. englisch und deutsch) verfügbar. (Punkte 4)

(5) Die Applikation läuft auf einem Desktop-Rechner, wird aber auch auf einer mobilen Plattform getestet und wenn nötig angepasst. Das Ergebnis ist in der Dokumentation festzuhalten. (Punkte 4)

(6) Die Anwendung reagiert weiterhin auf Benutzereingaben, wenn längere Berechnungen anstehen. Beispielsweise soll es möglich sein, eine länger dauernde Berechnung abzubrechen. (Punkte 4)

### 1.2 Anforderungen an den Entwicklungsprozess (Punkte 13/25)

~~(7) Es wird ein Versionsverwaltungssystem wie git oder svn benutzt. Die Commit-Kommentare beschreiben genau, was gemacht wurde. Build-Artefakte befinden sich nicht im Repository.~~ **(Punkte 4)**

(8) Klassen, Funktionen und Schnittstellen sind ausführlich im Quelltext im Doxygen oder qdoc-Format dokumentiert. Die Doxygen- bzw. qdoc-basierende Dokumentation lässt sich einfach mittels make generieren. (Punkte 4)

~~(9) Verwendete Algorithmen und Datenstrukturen sind möglichst Qt-unabhängig zu entwickeln, um eine anderweitige Nutzung zu gewährleisten.~~ **(Punkte 4)**

~~(10) Fehlerfreies Funktionieren der implementierten Algorithmen und Datenstrukturen ist mit Unit-Tests zu belegen und deren Erfolg ist im Beleg zu dokumentieren.~~ **(Punkte 5)**

(11) Werkzeuge wie valgrind und AddressSanitizer werfen bei der Ausführung des Programms und der Unit-Tests keine Fehlermeldungen aus. Der Erfolg ist im Beleg zu dokumentieren. (Punkte 4)

(12) Das Programm lässt sich einfach für eine Linux-Plattform übersetzen und die Tests laufen dabei automatisch ab. Build-Artefakte werden sowohl für für Linux und für eine weitere Plattform wie Windows oder OS X erzeugt und optional für eine mobilen Plattform. Das Bauen der Artefakte wird über ein Containerlösung wie Docker realisiert. (Punkte 4)

### 1.3 Projektspezifische Anforderungen (Punkte 1/30)

~~(13) Es können zwei Menschen gegeneinander oder ein Mensch gegen den Computer spielen.~~ **(Punkte 1)**

(14) Beim Spiel Mensch gegen Computer kann ausgewählt werden, wer beginnt. (Punkte 1)

(15) Menschliche Spieler sollen vor Spielbeginn in der GUI ihre(n) Namen eingeben. (Punkte 1)

(16) Für das Spielfeld und die Spielsteine soll es mindestens drei verschiedene Designs geben, die sich nicht nur in den Farben unterscheiden. (Punkte 2)

(17) Die Größe des Spielfelds soll vor Spielstart in der GUI konfigurierbar sein (z.B. 5 bis 10 Zeilen und Spalten, voreingestellt 8x8 wie im echten Spiel). (Punkte 1)

(18) Beim Setzen eines Spielsteines soll ein Sound abgespielt werden, für jede Partei ein anderer. (Punkte 1)

(19) Das Umdrehen eines gegnerischen Spielsteins soll animiert sein. (Punkte 1)

(20) Die Anwendung lässt illegale Züge nicht zu und weist sie mit Animation und Sound zurück. (Punkte 1)

(21) Die Anwendung erkennt eine Gewinnposition und ein Unentschieden, spielt dazu geeignete Sounds ab und zeigt das Resultat in einer Animation an. (Punkte 1)

(22) Alle Spielergebnisse sollen in einer lokalen Datenbank (SQLite) abgespeichert werden und alle wichtigen Informationen über die gespielten Spiele enthalten. (Punkte 1)

(23) Die Spielergebnisse sollen in der GUI abrufbar sein (Highscore). (Punkte 1)

(24) Die Spielergebnisse (Highscore) sollen ausgedruckt werden können oder auf anderem Wege der Welt bekannt gemacht werden können. (Punkte 1)

(25) Es soll möglich sein, ein Spiel zu unterbrechen (Save) und später, nach dem Neustart der Anwendung fortzusetzen (Load). (Punkte 1)

(26) Die Anwendung soll es Spielern erlauben, über das Netzwerk zu spielen. Es darf davon ausgegangen werden, dass die beiden Anwendungen im selben Subnetz sind, und die Ports erreichbar sind (keine Firewall, keine NAT, etc.). (Punkte 1)

(27) Die Anwendung soll sowohl Remote-Verbindungen annehmen können (als Server agieren), als auch sich mit einer anderen Anwendung aktiv verbinden können (als Client agieren). (Punkte 1)

(28) Eintretende Verbindungwünsche sollen angezeigt werden und akustisch hinterlegt werden. (Punkte 1)

(30) Der Anwender des Servers kann entscheiden, ob er den Verbindungswunsch annimmt, oder nicht. (Punkte 1)

(31) Der Anwender des Clients wird über die Entscheidung informiert. (Punkte 1)

(32) Die Verbindung soll solange gehalten werden, bis das Spiel beendet ist. (Punkte 1)

(33) Beim Spiel Mensch gegen Computer soll eine einfache Spielstrategie (Heuristik) zum Beispiel auf Basis des Minimax-Algorithmus implementiert werden. Eine kurze Beschreibung findet sich z.B. auf http://mnemstudio.org/game-reversi-example-2.
htm. (Punkte 5)

(34) Beim Spiel Mensch gegen Computer soll die Spielstärke des Computers in mindestens 3 Stufen einstellbar sein.

### 1.4 Eigene Zusatz-Anforderungen (Punkte 5/15)
(35) ...

(36) ...

(37) ...

(38) ...

(39) ...
