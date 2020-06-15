#include <QString>
#include <QtTest>
#include "model.h"

class VierGewinntTest : public QObject
{
    Q_OBJECT

  public:
    VierGewinntTest();

  private Q_SLOTS:
    void init();      // Wird automatisch vor JEDER Testmethode ausgeführt
    void cleanup();   // wird automatisch nach JEDER Testmethode ausgeführt
    void tstBoardStatusAfterGameStart();
    void tstBoardStatusAfterFewMoves();
    void tstBoardStatusAfterSeveralMoves();
    void tstFullBoard();
    void tstNotFullBoard();
    void tstHorizontalWin1();
    void tstHorizontalWin2();
    void tstHorizontalWin3();
    void tstHorizontalWin4();
    void tstHorizontalWin5();
    void tstVerticalWin1();
    void tstVerticalWin2();
    void tstVerticalWin3();
    void tstVerticalWin4();
    void tstDiagonalWin1();
    void tstDiagonalWin2();
    void tstDiagonalWin3();
    void tstDiagonalWin4();
    void tstNoWin();
    void tstGameNotFinished();
    void tstGameFinished1();
    void tstGameFinished2();

  private:
    Model *model;
};

VierGewinntTest::VierGewinntTest()
{
}

void VierGewinntTest::init()
{
  model = new Model;
}

void VierGewinntTest::cleanup()
{
  delete model;
  model = nullptr;
}

void VierGewinntTest::tstBoardStatusAfterGameStart()
{
  QList<FIELDSTATUS> tstfield;
  for (int i= 0; i<42; i++)
    tstfield.append(UNSET) ;
  QCOMPARE(tstfield,model->getField());
}
void VierGewinntTest::tstBoardStatusAfterFewMoves()
{
  QList<FIELDSTATUS> tstfield;
  tstfield<<PLAYER1<<UNSET<<UNSET<<UNSET<<PLAYER2<<PLAYER1<<UNSET;
  tstfield<<UNSET<<UNSET<<UNSET<<UNSET<<PLAYER2<<PLAYER2<<UNSET;
  tstfield<<UNSET<<UNSET<<UNSET<<UNSET<<PLAYER1<<UNSET<<UNSET;

  for (int index = 21; index<42; index++)
      tstfield<<UNSET;
  model->throwInColumn(0);
  model->throwInColumn(4);
  model->throwInColumn(-1);
  model->throwInColumn(5);
  model->throwInColumn(4);
  model->throwInColumn(7);
  model->throwInColumn(4);
  model->throwInColumn(5);

  QCOMPARE(tstfield, model->getField());
}
void VierGewinntTest::tstBoardStatusAfterSeveralMoves()
{
  QList<FIELDSTATUS> tstfield;
  tstfield<<PLAYER1<<PLAYER1<<PLAYER1<<PLAYER2<<PLAYER2<<PLAYER1<<PLAYER1;
  tstfield<<PLAYER1<<PLAYER2<<PLAYER2<<PLAYER1<<PLAYER1<<PLAYER2<<PLAYER2;
  tstfield<<PLAYER2<<PLAYER1<<PLAYER2<<PLAYER1<<PLAYER2<<PLAYER2<<PLAYER2;
  tstfield<<PLAYER1<<PLAYER2<<PLAYER2<<PLAYER1<<PLAYER1<<PLAYER1<<PLAYER2;
  tstfield<<PLAYER2<<PLAYER1<<PLAYER1<<PLAYER2<<UNSET<<PLAYER2<<PLAYER1;
  tstfield<<UNSET<<PLAYER1<<PLAYER1<<UNSET<<UNSET<<UNSET<<PLAYER2;
  QList<int> moves;
  moves<<0<<3<<0<<4<<3<<0<<4<<4<<6<<6<<1<<1<<2<<2<<0<<2<<1<<1<<5<<5<<1<<6<<1<<0
       <<3<<6<<3<<2<<2<<3<<6<<5<<2<<6<<5<<5<<4;
  foreach(int move, moves)  model->throwInColumn(move);
  QCOMPARE(tstfield, model->getField());
}

void VierGewinntTest::tstFullBoard()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6
       <<1<<2<<3<<4<<5<<6<<6<<5<<4<<3<<2<<1<<1<<2<<3<<4<<5<<0<<0<<0<<6;
  foreach(int move, moves)  model->throwInColumn(move);
  QCOMPARE(true, model->isBoardFull());
}

void VierGewinntTest::tstNotFullBoard()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6
       <<1<<2<<3<<4<<5<<6<<6<<5<<4<<3<<2<<1<<1<<2<<3<<1<<4<<5<<5<<0<<0<<1<<2<<3<<4<<5<<0;
  foreach(int move, moves)  model->throwInColumn(move);
  QCOMPARE(false, model->isBoardFull());
}

void VierGewinntTest::tstHorizontalWin1()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<0<<1<<1<<2<<2<<3;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[1], model->whoHasWon());
  QCOMPARE(QString("Ute"),        model->whoHasWon()->name);
}

void VierGewinntTest::tstHorizontalWin2()
{
  QList<int> moves;
  moves<<6<<1<<5<<0<<3<<0<<4;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[0], model->whoHasWon());
  QCOMPARE(QString("Klaus"),      model->whoHasWon()->name);
}

void VierGewinntTest::tstHorizontalWin3()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6
       <<1<<2<<3<<4<<5<<6<<6<<5<<4<<3<<2<<1<<3<<1<<6<<2<<4<<0<<5;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[1], model->whoHasWon());
  QCOMPARE(QString("Ute"),        model->whoHasWon()->name);
}

void VierGewinntTest::tstHorizontalWin4()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6
       <<1<<2<<3<<4<<5<<6<<6<<1<<4<<1<<2<<0<<0<<0<<6<<2<<3<<3;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[0], model->whoHasWon());
  QCOMPARE(QString("Klaus"),      model->whoHasWon()->name);
}

void VierGewinntTest::tstHorizontalWin5()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6
       <<1<<2<<3<<4<<5<<6<<6<<5<<4<<3<<2<<1<<1<<0<<0<<5<<0<<6<<3<<5<<4<<2;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[1], model->whoHasWon());
  QCOMPARE(QString("Ute"),        model->whoHasWon()->name);
}

void VierGewinntTest::tstVerticalWin1()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<6<<0<<1<<0<<1<<0;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[0], model->whoHasWon());
  QCOMPARE(QString("Klaus"),      model->whoHasWon()->name);
}

void VierGewinntTest::tstVerticalWin2()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<6<<0<<6<<0<<6;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[0], model->whoHasWon());
  QCOMPARE(QString("Klaus"),      model->whoHasWon()->name);
}

void VierGewinntTest::tstVerticalWin3()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6
       <<1<<2<<3<<4<<5<<6<<6<<0<<1<<0<<2<<0;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[0], model->whoHasWon());
  QCOMPARE(QString("Klaus"),      model->whoHasWon()->name);
}

void VierGewinntTest::tstVerticalWin4()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6
       <<1<<2<<3<<4<<5<<6<<6<<0<<1<<0<<2<<6<<1;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[1], model->whoHasWon());
  QCOMPARE(QString("Ute"),        model->whoHasWon()->name);
}

void VierGewinntTest::tstDiagonalWin1()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6
       <<0<<1<<2<<3<<4<<5<<6<<0;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[1], model->whoHasWon());
  QCOMPARE(QString("Ute"),        model->whoHasWon()->name);
}

void VierGewinntTest::tstDiagonalWin2()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6
       <<0<<1<<2<<3<<4<<5<<6<<1<<3;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[0], model->whoHasWon());
  QCOMPARE(QString("Klaus"),      model->whoHasWon()->name);
}

void VierGewinntTest::tstDiagonalWin3()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6<<3<<4<<4<<6<<5<<6<<6<<5<<5<<0<<6;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[0], model->whoHasWon());
  QCOMPARE(QString("Klaus"),      model->whoHasWon()->name);
}

void VierGewinntTest::tstDiagonalWin4()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6<<3<<2<<2<<0<<1<<0<<0<<1<<0<<6<<1;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QCOMPARE(model->getPlayer()[0], model->whoHasWon());
  QCOMPARE(QString("Klaus"),      model->whoHasWon()->name);
}

void VierGewinntTest::tstNoWin()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6
       <<0<<1<<2<<3<<4<<5<<6<<1<<1;
  foreach(int move, moves)  model->throwInColumn(move);
  model->setPlayerNames("Klaus", "Ute");
  QVERIFY(nullptr== model->whoHasWon());
}

void VierGewinntTest::tstGameNotFinished()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6
       <<0<<1<<2<<3<<4<<5<<6<<1<<1<<5<<5<<5<<5<<5<<5<<5<<5<<5
       <<5<<5<<5<<5<<5<<5<<5<<5<<5<<5<<5<<5<<5<<5<<5;
  foreach(int move, moves) model->throwInColumn(move);
  QCOMPARE(false, model->isGameFinished());
}

void VierGewinntTest::tstGameFinished1()
{
  QList<int> moves;
  moves<<0<<3<<0<<4<<3<<0<<4<<4<<6<<6<<1<<1<<2<<2<<0<<2<<1<<1<<5<<5<<1<<6<<1<<0
       <<1<<1<<3<<6<<3<<2<<1<<2<<3<<6<<5<<2<<6<<2<<5<<1<<6<<5<<4<<0<<3<<3<<6<<4<<5<<4;
  foreach(int move, moves) model->throwInColumn(move);
  QVERIFY(model->whoHasWon() == nullptr);
  QCOMPARE(true,    model->isGameFinished());
}

void VierGewinntTest::tstGameFinished2()
{
  QList<int> moves;
  moves<<0<<1<<2<<3<<4<<5<<6<<0<<1<<2<<3<<4<<5<<6<<3<<2<<2<<0<<1<<0<<0<<1<<0<<6<<1;
  foreach(int move, moves) model->throwInColumn(move);
  QCOMPARE(true, model->isGameFinished());
}

QTEST_APPLESS_MAIN(VierGewinntTest)

#include "tst_viergewinnt.moc"
