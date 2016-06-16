#include "block.h"
#include <iostream>

extern QString *BLOCK;

Block::Block(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    //g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    std::cout<<g_pixmap.boundingRect().width()<<" "<<g_pixmap.boundingRect().height();
    g_size = QSize(w,h);

    health = 400;

    b2BodyDef bodydef;
    //bodydef.type = b2_dynamicBody;
    bodydef.position.Set(x,y);
    bodydef.userData = BLOCK;
    bodydef.linearVelocity = b2Vec2(0,0);


    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w/2,h/2);

    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.density = 10;
    fixturedef.friction = 3;
    fixturedef.userData = this;


    g_body = world->CreateBody(&bodydef);
    g_body->CreateFixture(&fixturedef);


    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Block::setpixmap(QPixmap pixmap,float w, float h)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    //g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    //std::cout<<g_pixmap.boundingRect().width()<<" "<<g_pixmap.boundingRect().height();
    g_size = QSize(w,h);

}

int& Block::gethealth()
{
    return health;
}

bool Block::getshoulddisappear()
{
    return shoulddisappear;
}

void Block::disappear()
{
    shoulddisappear = 1;
}

void Block::resetdisappear()
{
    shoulddisappear = 0;
}

