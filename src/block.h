#ifndef BLOCK_H
#define BLOCK_H

#include "gameitem.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class Block : public GameItem
{
public:
    Block(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setpixmap(QPixmap pixmap, float w, float h);
    int& gethealth();
    bool getshoulddisappear();
    void disappear();
    void resetdisappear();
private:
    int health;
    bool shoulddisappear = 0;
};

#endif // BLOCK_H
