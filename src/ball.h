#ifndef BALL_H
#define BALL_H

#include "gameitem.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class Ball : public GameItem
{
public:
    Ball(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // BALL_H
