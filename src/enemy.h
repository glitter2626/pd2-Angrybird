#ifndef ENEMY_H
#define ENEMY_H

#include "gameitem.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QString>

class Enemy : public GameItem
{
public:
    Enemy(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setpixmap(QPixmap pixmap, float radius);
    int &gethealth();
    bool getshoulddisappear();
    void disappear();
    void resetdisappear();
private:
    int health;
    bool shoulddisappear = 0;
};

#endif // ENEMY_H
