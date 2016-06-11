#ifndef ROPE_H
#define ROPE_H
#include "gameitem.h"
#include <QList>
#include <Box2D/Box2D.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class Rope: public GameItem
{
public:
    Rope(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // ROPE_H
