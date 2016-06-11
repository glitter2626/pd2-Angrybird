#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QLCDNumber>
#include <QDesktopWidget>
#include <QTimer>
#include <QPushButton>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>


#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <rope.h>
#include <yellowbird.h>
#include <blackbird.h>
#include <whitebird.h>
#include <enemy.h>
#include <block.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    class MyCallBack : public b2QueryCallback{
    private:
        b2Body *test;
    public:
        MyCallBack(){test = NULL;}
        b2Body * getb2body(){
            return test;
        }
        bool ReportFixture(b2Fixture *fixture){
                 std::cout<<"get";
            //if(fixture->GetBody()->GetUserData()=="bird"){
                if(1){
               test = fixture->GetBody();

                return false;
            }
            return true;
        }
    };


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);

    //void mousePressEvent(QMouseEvent *event);
   // void mouseMoveEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void restart();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;

    QList<GameItem *> itemList;
    QList<GameItem *> items;
    QList<Block *> block;
    QList<Enemy *> enemy;
    QList<Rope *> rope;
    Whitebird *temp;
    Blackbird *tempb;
    QList<b2RevoluteJoint*> revolutejoint;
    QList<b2RopeJoint*> ropejoint;
    int ropelength;
    b2WeldJoint *weldjoint;

    QTimer timer;
    QLCDNumber *lcd;
    QPushButton *button;

    double x,y;
    b2MouseJoint *joint;
    MyCallBack callback;

};

#endif // MAINWINDOW_H
