#include "yellowbird.h"

Yellowbird::Yellowbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x, y, radius, timer, pixmap, world, scene)
{

}

void Yellowbird::collide()
{
    this->getBody().SetLinearVelocity(b2Vec2(0,-100));
}
