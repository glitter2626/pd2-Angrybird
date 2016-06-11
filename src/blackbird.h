#ifndef BLACKBIRD_H
#define BLACKBIRD_H

#include "bird.h"

class Blackbird : public Bird
{
public:
    Blackbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void collide();
    virtual ~Blackbird();
    void clear();
private:
    QTimer *temptimer;
    b2World *tempworld;
    QGraphicsScene *tempscene;

    Bird *tempbird;
    Bird *tempbird1;
    Bird *tempbird2;
    Bird *tempbird3;
};

#endif // BLACKBIRD_H
