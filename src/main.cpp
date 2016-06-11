#include "mainwindow.h"
#include <QApplication>
#include <QString>

QString *BIRD = new QString("bird");
QString *ROPE = new QString("rope");
QString *GROUND = new QString("ground");
QString *BUN = new QString("bun");
QString *PIG = new QString("pig");
QString *BLOCK = new QString("block");

b2Body *delbody = NULL;
float imp = 0;
void * feature =NULL;
int score = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
