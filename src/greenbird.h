#ifndef GREENBIRD_H
#define GREENBIRD_H

#include "bird.h"

class Greenbird : public Bird
{
public:
    Greenbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // GREENBIRD_H
