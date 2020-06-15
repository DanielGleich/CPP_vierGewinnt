#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QDebug>

enum FIELDSTATUS { UNSET, PLAYER1, PLAYER2 };

struct Player
{
  Player(){ this->name = name;}
  QString name;
};

class Model : public QObject
{
    Q_OBJECT

private:
  QList<FIELDSTATUS>      field;
  QList<Player *>         players;
  Player                  *activePlayer;
  public:
    Model(QObject *parent=0);
    QList<FIELDSTATUS>      getField() const;
    FIELDSTATUS             getFieldStatus(int x, int y) const;
    FIELDSTATUS             getFieldStatus(int i) const;
    int                     getIndex(int x, int y) const;
    QList<Player *>         getPlayer() const;
    FIELDSTATUS             getActivePlayerSign() const;
    QString                 getActivePlayerName() const;
    bool                    isBoardFull() const;
    bool                    isHorizontalWin() const;
    bool                    isVerticalWin() const;
    bool                    isDiagonalWin1() const; //links  unten - rechts oben
    bool                    isDiagonalWin2() const; //rechts unten - links  oben
    bool                    isGameWon() const;
    bool                    isGameFinished() const;
    Player*                 whoHasWon() const;
    void                    setPlayerNames(QString player1, QString player2);
    void                    throwInColumn(int column);
    void                    debugField() const;
    void                    debugBoard(QList<FIELDSTATUS> field) const;
    void                    switchPlayersTurn();
    void                    resetGame();

  signals:
    void dataChanged();
    void gameEnd();
    void playerChanged();
};

#endif // MODEL_H
