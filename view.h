#ifndef VIEW_H
#define VIEW_H
#include <QtWidgets>
#include "model.h"

class View : public QWidget
{
    Q_OBJECT
  private:
    QList<QLabel*> field;
    QList<QPushButton*> pbThrowIn;
    Model *game;
    QPixmap* emptyField;
    QPixmap* blueField;
    QPixmap* redField;
    QLabel *lbPlayersTurn;


  public:
    View(QWidget *parent = 0);
    ~View();
    void setPlayerNames();
  public slots:
    void printField();
    void columnPressed(int i);
    void restartGame();
    void disablePlayButtons();
    void updatePlayerStatus();
    void gameEndNotification();
};

#endif // VIEW_H
