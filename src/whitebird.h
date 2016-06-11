#ifndef WHITEBIRD_H
#define WHITEBIRD_H

#include "bird.h"

class Whitebird : public Bird
{
public:
    Whitebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void collide();
};

#endif // WHITEBIRD_H
