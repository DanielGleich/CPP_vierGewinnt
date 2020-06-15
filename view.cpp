#include "view.h"

View::View(QWidget *parent)
  : QWidget(parent)
{
  QGridLayout *layout = new QGridLayout();
  QGridLayout *fieldLayout = new QGridLayout();
  QHBoxLayout *buttonRow = new QHBoxLayout();

  QPushButton *pbNewGame = new QPushButton("Neues Spiel");
  QPushButton *pbExit = new QPushButton(tr("Exit"));

  QLabel *lbTitle = new QLabel(tr("<h1>4 gewinnt</h1>"));
  lbPlayersTurn = new QLabel(tr("Spieler nicht erkannt!"));

  QSignalMapper *mapper = new QSignalMapper(this);

  game = new Model();
  this->setPlayerNames();
  lbTitle->setAlignment(Qt::AlignHCenter);
  this->setFixedSize(QSize(400,475));

  emptyField = new QPixmap(":/images/emptyField.png");
  blueField = new QPixmap(":/images/blueField.png");
  redField = new QPixmap(":/images/redField.png");

  pbNewGame->setMaximumWidth(150);

  for (int i = 0; i < 7; i++)
  {
    pbThrowIn << new QPushButton(tr("\u2B07"),this);
    connect(pbThrowIn[i],SIGNAL(clicked(bool)),mapper, SLOT(map()));
    mapper->setMapping(pbThrowIn[i],i);
    pbThrowIn[i]->setFixedWidth(50);
    buttonRow->addWidget(pbThrowIn[i]);
  }

  for ( int i = 0 ; i < 42 ; i++ )
  {
    field << new QLabel(this);
    field[i]->setPixmap(*emptyField);
    fieldLayout->addWidget(field[i],7-i/7, i%7);
  }

  connect(mapper, SIGNAL(mapped(int)), this, SLOT(columnPressed(int)));     // Wurf ins Spiel
  connect(game, SIGNAL(dataChanged()), this, SLOT(printField()));           // aktualisierung des Spielfeldes
  connect(game, SIGNAL(playerChanged()),this, SLOT(updatePlayerStatus()));  // Spielerwechsel
  connect(game, SIGNAL(gameEnd()), this, SLOT(disablePlayButtons()));       // Spielende erkannt
  connect(game, SIGNAL(gameEnd()), this, SLOT(gameEndNotification()));      // Gewinnbenachrichtigung
  connect(pbNewGame,SIGNAL(clicked(bool)),this, SLOT(restartGame()));       // Spielneustart
  connect(pbExit, SIGNAL(clicked(bool)),this, SLOT( close() ) );            // Fenster schließen

  layout->setColumnStretch(0,6);
  layout->addWidget(lbTitle,0,0,1,6);
  layout->addLayout(buttonRow,1,0,1,7);
  layout->addLayout(fieldLayout,2,0,1,7);
  layout->addWidget(pbNewGame,3,0,1,2);
  layout->addWidget(lbPlayersTurn,3,1,1,3);
  layout->addWidget(pbExit,3,4,1,3);
  setLayout(layout);

  updatePlayerStatus();
}

void View::printField()
{
  for(int i = 0; i < 42; i++)
  {
    int player = game->getFieldStatus(i);
    switch (player)
    {
      case UNSET:
        field[i]->setPixmap(*emptyField);
      break;
      case PLAYER1:
        field[i]->setPixmap(*blueField);
      break;
      case PLAYER2:
        field[i]->setPixmap(*redField);
      break;
    }
  }
}

View::~View()
{
}

void View::setPlayerNames()
{
  int i;
  QString name1 = QInputDialog::getText(this, "Spielername eingeben",
                                        tr("Spieler 1: "), QLineEdit::Normal,
                                        QDir::home().dirName());
  QString name2 = QInputDialog::getText(this, "Spielername eingeben",
                                        tr("Spieler 2: "), QLineEdit::Normal,
                                        QDir::home().dirName());
  if (name1.isEmpty()) name1 = "Spieler 1";
  if (name2.isEmpty()) name2 = "Spieler 2";
  if (name1 == name2) name2.append("2");

  char c_name1[20], c_name2[20];
  for(i = 0; i<name1.size() && i<20; i++)
    c_name1[i] = name1.at(i).toLatin1();
  c_name1[i] = '\0';
  for(i = 0; i<name2.size() && i<20; i++)
    c_name2[i] = name2.at(i).toLatin1();
  c_name2[i] = '\0';
  game->setPlayerNames(c_name1, c_name2);
}

void View::columnPressed(int i)
{
  game->throwInColumn(i);
}

void View::restartGame()
{
  game->resetGame();
  this->setPlayerNames();
  for(int i = 0; i < pbThrowIn.length(); i++)
    pbThrowIn[i]->setDisabled(false);
  this->printField();
}

void View::disablePlayButtons()
{
  for(int i = 0; i < pbThrowIn.length(); i++)
    pbThrowIn[i]->setDisabled(true);
}

void View::updatePlayerStatus()
{
  QString player = game->getActivePlayerName();
  player.prepend("Spielzug: ");
  this->lbPlayersTurn->setText(player);
}

void View::gameEndNotification()
{
  if (game->whoHasWon() != nullptr)
  {
    QMessageBox win;
    win.setText(game->whoHasWon()->name+" hat gewonnen!");
    win.exec();
  }
}

