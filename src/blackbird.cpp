#include "blackbird.h"

Blackbird::Blackbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x, y, radius, timer, pixmap, world, scene)
{
    tempscene = scene;
    temptimer = timer;
    tempworld = world;

    tempbird = NULL;
    tempbird1 = NULL;
    tempbird2 = NULL;
    tempbird3 = NULL;
}

void Blackbird::collide()
{
    b2Vec2 pos = this->getBody().GetPosition();

    //this->setpixmap(QPixmap(":/image/air.png").scaled(height()/9.0,height()/9.0),0.27);
    this->getBody().SetTransform(b2Vec2(50,50),0);



    tempbird = new Bird(pos.x,pos.y,0.5,temptimer,QPixmap(":/image/angry-bird-black-icon (1).png").scaled(30,30),tempworld,tempscene);
    tempbird->setLinearVelocity(b2Vec2(50,0));

    tempbird1 = new Bird(pos.x,pos.y,0.5,temptimer,QPixmap(":/image/angry-bird-black-icon (1).png").scaled(30,30),tempworld,tempscene);
    tempbird1->setLinearVelocity(b2Vec2(50,50));

    tempbird2 = new Bird(pos.x,pos.y,0.5,temptimer,QPixmap(":/image/angry-bird-black-icon (1).png").scaled(30,30),tempworld,tempscene);
    tempbird2->setLinearVelocity(b2Vec2(-50,0));

    tempbird3 = new Bird(pos.x,pos.y,0.5,temptimer,QPixmap(":/image/angry-bird-black-icon (1).png").scaled(30,30),tempworld,tempscene);
    tempbird3->setLinearVelocity(b2Vec2(-50,-50));
}

Blackbird::~Blackbird()
{
    delete tempbird;
    delete tempbird1;
    delete tempbird2;
    delete tempbird3;
}

void Blackbird::clear()
{
    if(tempbird != NULL){
    tempworld->DestroyBody(&tempbird->getBody());
    tempworld->DestroyBody(&tempbird1->getBody());
    tempworld->DestroyBody(&tempbird2->getBody());
    tempworld->DestroyBody(&tempbird3->getBody());

    tempbird = NULL;
    tempbird1 = NULL;
    tempbird2 = NULL;
    tempbird3 = NULL;
    }

}
