#ifndef YELLOWBIRD_H
#define YELLOWBIRD_H

#include "bird.h"

class Yellowbird : public Bird
{
public:
    Yellowbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void collide();
};

#endif // YELLOWBIRD_H
