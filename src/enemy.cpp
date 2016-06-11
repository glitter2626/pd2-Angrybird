#include "enemy.h"

extern QString *PIG;

Enemy::Enemy(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : GameItem(world)
{
    health = 325;

    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(x,y);
    bodydef.userData = PIG;
    g_body = world->CreateBody(&bodydef);

    b2CircleShape bodyshape;

    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;

    fixturedef.density = 15;
    fixturedef.friction = 0.5;
    fixturedef.restitution = 0.5;
    fixturedef.userData = this;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Enemy::setpixmap(QPixmap pixmap, float radius)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

}

int &Enemy::gethealth()
{
    return health;
}

bool Enemy::getshoulddisappear()
{
    return shoulddisappear;
}

void Enemy::disappear()
{
    shoulddisappear = 1;
}

void Enemy::resetdisappear()
{
    shoulddisappear = 0;
}
