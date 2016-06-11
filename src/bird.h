#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QString>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setpixmap(QPixmap pixmap, float radius);
    void setLinearVelocity(b2Vec2 velocity);
    void setDensity();
    virtual void collide();
    virtual ~Bird();

};

#endif // BIRD_H
