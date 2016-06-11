#include "land.h"

extern QString *GROUND;

Land::Land(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_size = QSize(w,h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.userData = GROUND;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);

    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w/2,h/2);

    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.filter.groupIndex = -3;
    fixturedef.density = 9.0f;

    g_body->CreateFixture(&fixturedef);

    scene->addItem(&g_pixmap);
    paint();
}
