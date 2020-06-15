#include "model.h"

Model::Model(QObject *parent)
  : QObject(parent)
{
  players << new Player();
  players << new Player();

  activePlayer = players[0];

  for (int i=0; i<42;i++)
    field << UNSET;
}

QList<FIELDSTATUS> Model::getField() const
{ return field; }

FIELDSTATUS Model::getFieldStatus(int x, int y) const
{  return field[getIndex(x,y)]; }

FIELDSTATUS Model::getFieldStatus(int i) const
{  return field[i]; }

int Model::getIndex(int x, int y) const
{  return (7*y+x); }

QList<Player *> Model::getPlayer() const
{  return players; }

FIELDSTATUS Model::getActivePlayerSign() const
{
  if (activePlayer== players[0])
    return PLAYER1;
  return PLAYER2;
}

QString Model::getActivePlayerName() const
{
  if (activePlayer== players[0])
    return players[0]->name;
  return players[1]->name;
}

bool Model::isBoardFull() const
{
  for(int x = 0; x < 7; x++)
    if (getFieldStatus(x,5) == UNSET)
      return false;
  return true;
}

bool Model::isHorizontalWin() const
{
  for(int y= 0; y < 6 ; y++)
    for(int x=0; x < 4 ; x++)
      if (getFieldStatus(x,y) != UNSET &&
          getFieldStatus(x,y) == getFieldStatus(x+1,y) &&
          getFieldStatus(x,y) == getFieldStatus(x+2,y) &&
          getFieldStatus(x,y) == getFieldStatus(x+3,y))
        return true;
  return false;
}

bool Model::isVerticalWin() const
{
  for(int y= 0; y < 3 ; y++)
    for(int x=0; x < 7 ; x++)
      if (getFieldStatus(x,y) != UNSET &&
          getFieldStatus(x,y) == getFieldStatus(x,y+1) &&
          getFieldStatus(x,y) == getFieldStatus(x,y+2) &&
          getFieldStatus(x,y) == getFieldStatus(x,y+3))
        return true;
  return false;
}

bool Model::isDiagonalWin1() const
{
  for(int y= 0; y < 3 ; y++)
    for(int x=0; x < 4 ; x++)
      if (getFieldStatus(x,y) != UNSET &&
          getFieldStatus(x,y) == getFieldStatus(x+1,y+1) &&
          getFieldStatus(x,y) == getFieldStatus(x+2,y+2) &&
          getFieldStatus(x,y) == getFieldStatus(x+3,y+3))
        return true;
  return false;
}

bool Model::isDiagonalWin2() const
{
  for(int y= 0; y < 3 ; y++)
    for(int x=6; x > 2 ; x--)
      if (getFieldStatus(x,y) != UNSET &&
          getFieldStatus(x,y) == getFieldStatus(x-1,y+1) &&
          getFieldStatus(x,y) == getFieldStatus(x-2,y+2) &&
          getFieldStatus(x,y) == getFieldStatus(x-3,y+3))
        return true;
  return false;
}

bool Model::isGameWon() const
{
  if (isHorizontalWin() || isVerticalWin() || isDiagonalWin1() || isDiagonalWin2())
    return true;
  return false;
}

bool Model::isGameFinished() const
{
  if (isGameWon() || isBoardFull())
    return true;
  return false;
}

Player* Model::whoHasWon() const
{
  if (isGameWon())
    return activePlayer;
  return nullptr;
}

void Model::setPlayerNames(QString player1, QString player2)
{
  players[0]->name = player1;
  players[1]->name = player2;
}

void Model::throwInColumn(int column)
{
  if (column >= 0 && column <=6)
  {
    int y = 5;
    if ( getFieldStatus(column,y) == UNSET )
    {
      for (; y >= 0; y--)
        if (getFieldStatus(column,y) != UNSET)
          break;
      field.replace(getIndex(column,y+1),getActivePlayerSign());
      if (!isGameFinished())
        switchPlayersTurn();
      else emit gameEnd();
    }
  }
  emit dataChanged();
}

void Model::debugField() const
{
  for(int y=5;y>=0;y--)
    qDebug() << getFieldStatus(0,y) <<
                getFieldStatus(1,y) <<
                getFieldStatus(2,y) <<
                getFieldStatus(3,y) <<
                getFieldStatus(4,y) <<
                getFieldStatus(5,y) <<
                getFieldStatus(6,y);
}

void Model::debugBoard(QList<FIELDSTATUS> field) const
{
  for(int y=5;y>=0;y--)
    qDebug() << field[getIndex(0,y)] <<
                field[getIndex(1,y)] <<
                field[getIndex(2,y)] <<
                field[getIndex(3,y)] <<
                field[getIndex(4,y)] <<
                field[getIndex(5,y)] <<
                field[getIndex(6,y)];
}
void Model::switchPlayersTurn()
{
  if (activePlayer == players[0])
  {
    activePlayer = players[1];
    emit playerChanged();
  }
  else
  {
    activePlayer = players[0];
    emit playerChanged();
  }
}

void Model::resetGame()
{
  for(int i = 0; i<42; i++)
    field[i] = UNSET;
}
