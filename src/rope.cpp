#include "rope.h"

extern QString *ROPE;

Rope::Rope(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(w,h);


    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(x,y);
    bodydef.userData = ROPE;
    bodydef.linearVelocity = b2Vec2(0,0);
    bodydef.angularDamping = 1000;

    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);

    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.density = 2;
    fixturedef.restitution=0.00001;
    fixturedef.filter.groupIndex = -3;

    g_body = world->CreateBody(&bodydef);
    g_body->CreateFixture(&fixturedef);
    //g_body->SetGravityScale(0);
    g_body->SetFixedRotation(true);

    /*b2RevoluteJointDef jointdef;
    jointdef.localAnchorA.y = - h/2;
    jointdef.localAnchorB.y = h/2;

    for(int i = 0; i < length - 1; i++){
        jointdef.bodyA = body[i];
        jointdef.bodyB = body[i + 1];
        joint.push_back((b2RevoluteJoint*) world->CreateJoint(&jointdef));
    }

    b2RopeJointDef ropejointdef;
    ropejointdef.localAnchorA.Set(0, -h/2);
    ropejointdef.localAnchorB.Set(0, h/2);
    ropejointdef.maxLength = h;

    for(int i = 0; i < length - 1; i++){
        ropejointdef.bodyA = body[i];
        ropejointdef.bodyB = body[i+1];
        ropejoint.push_back((b2RopeJoint*)world->CreateJoint(&ropejointdef));
    }*/

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);

}
