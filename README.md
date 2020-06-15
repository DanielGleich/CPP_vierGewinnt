#2. Schuljahr (Ausbildung als staatlich geprüfter informationstechnischer Assistent) (Aufgabe 3/4 PMC)

##neue Programmierübungen im Projekt:
*Unit-Tests (tst_vierGewinnt.pro)
*Benutzung von Bildern/Icons
*Einstieg in Model-/Controller-/View-Aufbau (Controller quasi im View implementiert)
*Erstellung eigener Signals
*qDebug()
*Datentyp "enum"
*QMessageBox / QInputDialog

## Haupt-Projekt (vierGewinnt.pro)

### main.cpp
View-Element wird initialisiert und mit *show()* gezeigt.

### view.cpp / view.h
Benutzeroberfläche des Spiels.

#### QList<QLabel*> field
Eine Liste mit allen Feldern, wo ein vierGewinnt-Chip drinnen sein könnte.

#### QList<QPushButton*> pbThrowIn
Knöpfe, die das Einwerfen in eine Reihe des Spielfelds ermöglichen soll.

#### Model *game
Model-Objekt, welches die ganze Spiellogik enthält.

#### QPixmap* emptyField, blueField, redField
Icons für Spielfelder.

#### QLabel *lbPlayersTurn
Textbereich, wo angezeigt wird, welcher Spieler dran ist.

#### View(QWidget *parent = 0), ~View()
Konstruktor und Destruktor.
Im Destruktor findet keine Operation statt.
Im Konstruktor hingegen werden die Layouts (Anordnung von Widgets)
initialisiert und verschachtelt. Außerdem werden Buttons, die
Neustart und das Beenden des Spiels auslösen, initialisiert.
Die Textfelder werden gesetzt und ein QSignalMapper-Objekt wird 
erstellt. Dieser Mapper sorgt dafür, dass jeder Einwurf-Knopf (*pbThrowIn*)
die richtige Funktion aufruft. Weiterhin werden noch nicht initialisierte
Variablen initialisiert und die Oberfläche wird mit den Widgets versehen.
Zum Schluss werden diverse connects gesetzt (z.B. wenn das Spiel zuende ist,
werden die *pbThrowIn*'s disabled. Alle Widgets werden in Layouts 
eingebunden; bzw. einige Layouts werden verschachtelt.

#### void setPlayerNames()
Funktion, mit der zwei Input-Dialoge hintereinander, welche die
Spielernamen abfragen, erscheinen. Falls kein Name gesetzt wird,
wird der Name "Spieler 1"/"Spieler 2" zugeteilt. Wenn der selbe
Name 2x angegeben wird, wird beim 2.Spieler eine "2" angehangen.

#### void printField()
Geht mit einer for-Schleife jedes Spielfeld von *Model \*game* durch
und stellt das gesamte Spielfeld auf der Oberfläche dar.

#### void columnPressed(int i)
Funktion, die ausgeführt wird, wenn ein pbThrowIn gedrückt wird.
Die Funktion greift dabei die Methode von *Model \*game* auf.

#### void restartGame()
Startet das Spiel neu, setzt die Spielernamen zurück und das Spiel
wird neu dargestellt.

#### void disablePlayButtons()
Macht alle *pbThrowIn*'s unbenutztbar.

#### void updatePlayerStatus()
Updatet das Textfeld, welches den aktuellen Spieler angibt.

#### void gameEndNotification()
Schaut nach, wer der Gewinner ist; wenn es *nullptr* ist, gibt
es keinen Gewinner. Sollte es doch einen Gewinner geben, wird eine
MessageBox ausgegeben.

### model.cpp / model.h
Enthält den logischen Spielaufbau.

#### enum FIELDSTATUS { UNSET, PLAYER1, PLAYER2 }
Ganzzahl-Werte mit eigenem Alias. UNSET==0, PLAYER1==1, PLAYER2==2.

#### struct Player
Eigene Struktur für jeden Spieler. Der Spieler besitzt derzeit nur einen
Namen (*QString name*), jedoch bleibt es beim Struct für die Erweiterbarkeit.

#### QList<FIELDSTATUS> field
Enthält alle Felder, wo ein Vier-Gewinnt-Chip sein könnte.
*field[0]* linke untere Ecke
*field[6]* rechte untere Ecke
*field[35]* linke obere Ecke
*field[41]* rechte obere Ecke.

#### QList<Player *> players
Eine Liste der teilnehmenden Spieler.

#### Player *activePlayer
Zeiger auf den Spieler, der aktuell dran ist.

#### Model(QObject *parent=0)
Initialisiert zwei Spieler, setzt den ersten Spieler als aktiven 
Spieler und setzt das komplette Spielfeld auf *UNSET*.

#### QList<FIELDSTATUS> getField()
Getter-Funktion für *QList<FIELDSTATUS> field*.

#### FIELDSTATUS getFieldStatus(int x, int y), FIELDSTATUS getFieldStatus(int i)
Returnt den *FIELDSTATUS* vom gewünschten Wert/ von gewünschten Koordinaten

#### int getIndex(int x, int y)
Rechnet Koordinaten in den Index des gewünschten X-/ und Y-Werts.

#### QList<Player *> getPlayer() 
Getter-Funktion für *QList<Player*> players*.

#### FIELDSTATUS getActivePlayerSign()
Returnt *PLAYER1* oder *PLAYER2* je nach aktiven Spieler.

#### QString getActivePlayerName()
Returnt Namen des aktiven Spielers

#### bool isBoardFull()
Returnt true, wenn das gesamte Spielfeld (*QList<FIELDSTATUS> field*) 
kein *UNSET* enthält.

#### bool isHorizontalWin()
Schaut nach, ob vier gleiche Spieler-*FIELDSTATUS* in einer Reihe sind.

#### bool isVerticalWin()
Schaut nach, ob vier gleiche Spieler-*FIELDSTATUS* in einer Spalte sind.

#### bool isDiagonalWin1() 
Schaut nach, ob vier gleiche Spieler-*FIELDSTATUS* in einer Diagonalen sind
(von unten links nach oben rechts).

#### bool isDiagonalWin2() 
Schaut nach, ob vier gleiche Spieler-*FIELDSTATUS* in einer Diagonalen sind
(von unten rechts nach oben links).

#### bool isGameWon()
Schaut nach, ob jemand das Spiel gewonnen hat.

#### bool isGameFinished()
Schaut nach, ob jemand das Spiel gewonnen hat oder ob das komplette Spielfeld voll ist.

#### Player* whoHasWon()
Returnt den Gewinner des Spiels.

#### void setPlayerNames(QString player1, QString player2)
Setzt Namen der Spieler-Objekte. 

#### void throwInColumn(int column)
Setzt *FIELDSTATUS* des aktiven Spielers in *QList<FIELDSTATUS> field*.
Dabei wird geguckt, ob beim obersten Feld der gegebenen Spalte ein *UNSET* ist; wenn das 
zutrifft geht es soweit nach unten bis die Bedingung nicht mehr zutrifft. Danach wird der
Spieler-*FIELDSTATUS* auf das letzte *UNSET*-Feld gesetzt.
Zum Schluss wird geschaut, ob niemand gewonnen hat und das komplette Spielfeld nicht voll 
ist. Wenn die Bedingungen zutreffen, wird der Spieler gewechselt; wenn das nicht zutrifft, 
wird das Signal *gameEnd()* ausgestoßen.
Zum Schluss wird das Signal *dataChanged()* ausgestoßen.

#### void debugField()
Stellt das komplette Spielfeld in der Konsole dar.

#### void debugBoard(QList<FIELDSTATUS> field) 
Stellt die gegebene Liste als Spielfeld in der Konsole dar.

#### void switchPlayersTurn()
Wechselt zwischen Spieler 1 und Spieler 2. Dabei wird das Signal *playerChanged* 
ausgestoßen.

#### void resetGame();
Setzt alle Spielfelder auf *UNSET*.

## Unit-Test Projekt (tst_vierGewinnt.pro)
In dieser Projekt-Datei wurde die Funktionalität der Gewinnabfragen
in der Model-Klasse getestet. 