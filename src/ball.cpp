#include "ball.h"

extern QString *BIRD;

Ball::Ball(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    //bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = BIRD;
    g_body = world->CreateBody(&bodydef);

    b2CircleShape bodyshape;

    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;

    //fixturedef.filter.groupIndex = -2;
    fixturedef.density = 1;
    fixturedef.friction = 0.1;
    fixturedef.restitution = 0.7;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}
