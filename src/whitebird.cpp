#include "whitebird.h"

Whitebird::Whitebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x, y, radius, timer, pixmap, world, scene)
{

}

void Whitebird::collide()
{
    this->setpixmap(QPixmap(":/image/angry-bird-white-icon.png").scaled(180,180),3);
    this->setLinearVelocity(b2Vec2(15,-50));
    this->getBody().GetFixtureList()->SetDensity(90.0f);
    this->getBody().ResetMassData();
}
