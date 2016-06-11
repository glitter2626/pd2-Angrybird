#include "mycontactlistener.h"
#include <QDebug>
#include <math.h>

extern QString *BIRD;
extern QString *ROPE;
extern QString *GROUND;
extern QString *BUN;
extern QString *BLOCK;
extern QString *PIG;

extern b2Body *delbody;
extern float imp;
extern void* feature;
extern int score;

void myContactListener::BeginContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody()->GetUserData() == BLOCK && contact->GetFixtureB()->GetBody()->GetUserData() == BIRD){ //|| (contact->GetFixtureA()->GetBody()->GetUserData() == BIRD && contact->GetFixtureB()->GetBody()->GetUserData() == BLOCK)){
        iscontacted = 1;
        qDebug()<<"iscontact is 1";
    }



    if(contact->GetFixtureA()->GetBody()->GetUserData() == BIRD && contact->GetFixtureB()->GetBody()->GetUserData() == PIG){
        iscontacted = 1;
        //qDebug()<<"iscontact is 1";
    }
    if(contact->GetFixtureA()->GetBody()->GetUserData() == PIG && contact->GetFixtureB()->GetBody()->GetUserData() == BIRD){
        iscontacted = 1;
        //qDebug()<<"iscontact is 1";
    }

    /*if(contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody){
        qDebug()<<"test";
        contact->GetFixtureA()->GetBody()->SetLinearVelocity(b2Vec2(50,50));
        contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(5,5));
    }*/
    //if(contact->IsTouching())
        //qDebug()<<"OKOK";
}

void myContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    //if(contact->GetFixtureA()->GetBody()->GetUserData() == BIRD)
    //qDebug()<<"ccccc";
    if(contact->GetFixtureB()->GetBody()->GetUserData() == BIRD && contact->GetFixtureA()->GetBody()->GetUserData() == BUN)
        contact->SetEnabled(false);
    if(contact->GetFixtureB()->GetBody()->GetUserData() == BIRD && contact->GetFixtureA()->GetBody()->GetUserData() == ROPE)
        contact->SetEnabled(false);
}

void myContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    /*if(score == 0 && ((contact->GetFixtureA()->GetBody()->GetUserData() == BIRD && contact->GetFixtureB()->GetBody()->GetUserData() == PIG)  || (contact->GetFixtureA()->GetBody()->GetUserData() == PIG && contact->GetFixtureB()->GetBody()->GetUserData() == BIRD))){
        score = abs((int)impulse->normalImpulses[0]) + abs((int)impulse->normalImpulses[1]);
    }*/

    if(score == 0 && contact->GetFixtureA()->GetBody()->GetUserData() == BIRD && contact->GetFixtureB()->GetBody()->GetUserData() == PIG){
        score = abs((int)impulse->normalImpulses[0]) + abs((int)impulse->normalImpulses[1]);
    }
    if(score == 0 && contact->GetFixtureA()->GetBody()->GetUserData() == PIG && contact->GetFixtureB()->GetBody()->GetUserData() == BIRD){
        score = abs((int)impulse->normalImpulses[0]) + abs((int)impulse->normalImpulses[1]);
    }



    if(iscontacted == true && contact->GetFixtureA()->GetBody()->GetUserData() == BIRD && contact->GetFixtureB()->GetBody()->GetUserData() == PIG){
        //delbody = contact->GetFixtureA()->GetBody();
        imp = abs((int)impulse->normalImpulses[0]) + abs((int)impulse->normalImpulses[1]);
        iscontacted = false;
        feature = contact->GetFixtureB()->GetUserData();
        qDebug()<<"delbody yes now!!";
    }
    if(iscontacted == true && contact->GetFixtureA()->GetBody()->GetUserData() == PIG && contact->GetFixtureB()->GetBody()->GetUserData() == BIRD){
        //delbody = contact->GetFixtureA()->GetBody();
        imp = abs((int)impulse->normalImpulses[0]) + abs((int)impulse->normalImpulses[1]);
        iscontacted = false;
        feature = contact->GetFixtureA()->GetUserData();
        qDebug()<<"delbody yes now!!";
    }




    if(iscontacted == true && contact->GetFixtureA()->GetBody()->GetUserData() == BLOCK && contact->GetFixtureB()->GetBody()->GetUserData() == BIRD){
        delbody = contact->GetFixtureA()->GetBody();
        imp = abs((int)impulse->normalImpulses[0]) + abs((int)impulse->normalImpulses[1]);
        iscontacted = false;
        feature = contact->GetFixtureA()->GetUserData();
        qDebug()<<"delbody yes now!!";
    }
}

void myContactListener::EndContact(b2Contact *contact)
{
    score = 0;
}
