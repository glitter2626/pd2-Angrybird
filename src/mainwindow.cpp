#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mycontactlistener.h"
#include <QDebug>
#include <QLabel>
#include <Box2D/Common/b2Math.h>

extern QString *BUN;
extern b2Body *delbody;
extern float imp;
extern void* feature;
extern int score;

int birdID = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    setMouseTracking(true);
    joint = NULL;
    weldjoint = NULL;
    ropelength = 30;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{

    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());

    scene->addPixmap(QPixmap(":/image/Angry Bird Game - Background.png"));
    QLabel *label = new QLabel(QString("分數 : "));
    label->setGeometry(30,30,45,30);
    scene->addWidget(label);
    lcd = new QLCDNumber();
    lcd->display(0);
    lcd->setGeometry(60,30,50,30);
    scene->addWidget(lcd);
    button = new QPushButton(QString("Restart!!"));
    button->setGeometry(0,0,50,30);
    connect(button,SIGNAL(pressed()),this,SLOT(restart()));
    scene->addWidget(button);
    exit = new QPushButton(QString("Exit"));
    exit->setGeometry(930,0,30,30);
    connect(exit,SIGNAL(pressed()),this,SLOT(QUITSLOT()));
    scene->addWidget(exit);

    ui->graphicsView->setScene(scene);

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    items.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(960,90),world,scene));

    // Create bird (You can edit here)

    Bird *birdie = new Bird(2.0f,10.0f,1,&timer,QPixmap(":/bird.png").scaled(60,60),world,scene);
    // Setting the Velocity
    birdie->setLinearVelocity(b2Vec2(0,0));
    birdie->setDensity();
    itemList.push_back(birdie);


    Bird *birdie1 = new Yellowbird(5.0f,17.0f,1,&timer,QPixmap(":/image/angry-bird-yellow-icon.png").scaled(60,60),world,scene);
    // Setting the Velocity
    birdie1->setLinearVelocity(b2Vec2(0,0));
    //birdie1->getBody().SetActive(false);
    itemList.push_back(birdie1);

    tempb = new Blackbird(3.0f,17.0f,1,&timer,QPixmap(":/image/angry-bird-black-icon (1).png").scaled(60,60),world,scene);
    // Setting the Velocity
    tempb->setLinearVelocity(b2Vec2(0,0));
    //birdie2->getBody().SetActive(false);
    itemList.push_back(tempb);

    temp = new Whitebird(1.0f,17.0f,1,&timer,QPixmap(":/image/angry-bird-white-icon.png").scaled(60,60),world,scene);
    // Setting the Velocity
    temp->setLinearVelocity(b2Vec2(0,0));
    //birdie3->getBody().SetActive(false);
    itemList.push_back(temp);




    items.push_back(new Land(3,6,0.7/2,3.5/2,QPixmap(":/image/bun.png").scaled(width()/(320/7),height()/(36/7)),world,scene));
    items.at(1)->getBody().SetUserData(BUN);
    items.push_back(new Land(2.6,6,0.7/2,2.1/2,QPixmap(":/image/bun2.png").scaled(width()/(320/7),height()/(60/7)),world,scene));
    items.at(2)->getBody().SetUserData(BUN);
    //itemList.push_back(new Rope(20.0f, 10.0f, 0.5f, 0.5f, 10.0f, &timer, QPixmap(":/image/angry-bird-yellow-icon.png").scaled(height()/9.0,height()/9.0),world,scene));

    items.push_back(new Land(5,14,2,0.5,QPixmap(":/image/plate.png").scaled(60,15),world,scene));
    items.push_back(new Land(3,14,2,0.5,QPixmap(":/image/plate.png").scaled(60,15),world,scene));
    items.push_back(new Land(1,14,2,0.5,QPixmap(":/image/plate.png").scaled(60,15),world,scene));

    for(int j = 0; j < 5; j++){
        ball.push_back(new Ball(15,12 + j*2,1,&timer,QPixmap(":/image/ball.png").scaled(60,60),world,scene));
        ball.push_back(new Ball(28,12 + j*2,1,&timer,QPixmap(":/image/ball.png").scaled(60,60),world,scene));
    }


    float h = 0.03f, w = 0.03f;
    for(int i = 0; i < ropelength; ++i)
        rope.push_back(new Rope(1.0f, 4.0f, w/2, h/2, &timer, QPixmap(":/image/rope1.png").scaled(width()/(320/3), height()/(60)),world,scene));

    b2RevoluteJointDef jointdef;
    jointdef.localAnchorA.x = -w/2;
    jointdef.localAnchorB.x = w/2;


    for(int i = 0; i < rope.length() - 1; i++){
            jointdef.bodyA = &rope.at(i)->getBody();
            jointdef.bodyB = &rope.at(i+1)->getBody();
            revolutejoint.push_back((b2RevoluteJoint*) world->CreateJoint(&jointdef));
    }

    b2RopeJointDef ropejointdef;
    ropejointdef.localAnchorA.Set(-w/2,0);
    ropejointdef.localAnchorB.Set(w/2,0);
    ropejointdef.maxLength = 0;

    for(int i = 0; i < rope.length() - 1; i++){
        ropejointdef.bodyA = &rope.at(i)->getBody();
        ropejointdef.bodyB = &rope.at(i+1)->getBody();
        ropejoint.push_back((b2RopeJoint*)world->CreateJoint(&ropejointdef));
    }

    jointdef.localAnchorA.x=0;
    jointdef.localAnchorB.x=0;
    jointdef.bodyA = &items.at(2)->getBody();
    jointdef.bodyB = &rope.at(0)->getBody();
    world->CreateJoint(&jointdef);

    jointdef.localAnchorA.x=0.3;
    jointdef.localAnchorA.y=0;
    jointdef.localAnchorB.x=0;
    jointdef.bodyA = &items.at(1)->getBody();
    jointdef.bodyB = &rope.at(ropelength-1)->getBody();
    world->CreateJoint(&jointdef);

    //create enemy

    //itemList.push_back(new Enemy(19.0f,5.0f,0.27f,&timer,QPixmap(":/image/enemy1.png").scaled(height()/(9),height()/(9)),world,scene));
    //itemList.push_back(new Enemy(21.5f,7.0f,0.27f,&timer,QPixmap(":/image/pig.png").scaled(height()/(9),height()/(9)),world,scene));
    enemy.push_back(new Enemy(19.0f,5.0f,1,&timer,QPixmap(":/image/enemy1.png").scaled(60,60),world,scene));
    enemy.push_back(new Enemy(21.5f,7.0f,1,&timer,QPixmap(":/image/pig.png").scaled(60,60),world,scene));
    enemy.at(1)->gethealth() += 50;

    //create block
    block.push_back(new Block(18.0f,4.0f,2,2,&timer,QPixmap(":/image/block1.png").scaled(60,60),world,scene));
    block.push_back(new Block(18.0f,6.0f,2,2,&timer,QPixmap(":/image/block1.png").scaled(60,60),world,scene));
    block.push_back(new Block(18.0f,8.0f,2,2,&timer,QPixmap(":/image/block1.png").scaled(60,60),world,scene));
    block.push_back(new Block(20.0f,8.0f,2,2,&timer,QPixmap(":/image/block1.png").scaled(60,60),world,scene));
    block.push_back(new Block(22.0f,8.0f,2,2,&timer,QPixmap(":/image/block1.png").scaled(60,60),world,scene));
    block.push_back(new Block(24.0f,8.0f,2,2,&timer,QPixmap(":/image/block1.png").scaled(60,60),world,scene));
    block.push_back(new Block(24.0f,6.0f,2,2,&timer,QPixmap(":/image/block1.png").scaled(60,60),world,scene));
    block.push_back(new Block(24.0f,4.0f,2,2,&timer,QPixmap(":/image/block1.png").scaled(60,60),world,scene));

    //block.at(3)->setpixmap(QPixmap(":/image/dispear.png").scaled(height()/9, height()/9),1,1);

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);

    world->SetContactListener(new myContactListener());
}



void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!


//if(birdID <= 4){
    if(event->type() == QEvent::KeyPress){
        if(birdID >= 1 )
            if(itemList.at(birdID-1)->getcollide() == 0){
                itemList.at(birdID-1)->collide();
                itemList.at(birdID-1)->usecollide();
            }
        //qDebug()<<"ccccc";
    }


if(birdID <= 3){
    if(event->type() == QEvent::MouseButtonPress)
    {
        //x = static_cast<QMouseEvent*>(event)->x()/30 - 7;
        //y = 22 - static_cast<QMouseEvent*>(event)->y()/30;
        if(birdID == 4)
            this->restart();


        x = static_cast<QMouseEvent*>(event)->x()/30 ;
        y = 17 - static_cast<QMouseEvent*>(event)->y()/30;

        itemList.at(birdID)->getBody().SetTransform(b2Vec2(2,3),0);


        if(weldjoint == NULL){

            //world->DestroyBody(&block.at(3)->getBody());
            //block.erase(block.begin()+3);

            //rope.at(75)->getBody().ApplyForceToCenter(b2Vec2(x,y),0);
            b2WeldJointDef jointdef;
            jointdef.bodyA = &rope.at(ropelength/2)->getBody();
            jointdef.bodyB = &itemList.at(birdID)->getBody();
            jointdef.localAnchorB.x = -0.8;
            jointdef.localAnchorB.y = -0.5;
            weldjoint = (b2WeldJoint*)world->CreateJoint(&jointdef);
        }

        if(joint == NULL){

           /* b2AABB aabb;
            aabb.lowerBound.Set(x-1/30, y-1/30);
            aabb.upperBound.Set(x+1/30, y+1/30);
            world->QueryAABB(&callback, aabb);

            if(callback.getb2body() != NULL){*/
            b2Body &test = itemList.at(birdID)->getBody();//rope.at(0)->getBody();
            b2BodyDef bodydef;
            b2Body *bodyA = world->CreateBody(&bodydef);

            b2MouseJointDef jointdef;
            jointdef.bodyA = bodyA;
            jointdef.bodyB = &test;
            jointdef.target = b2Vec2(x,y);

            jointdef.dampingRatio = 1;
            jointdef.frequencyHz = 1;
            jointdef.maxForce = test.GetMass()*1000;

            joint = (b2MouseJoint*)world->CreateJoint(&jointdef);
            //}
        }
        std::cout << "Press !" <<x<<" "<<y<<"real:"<< itemList.at(1)->getBody().GetWorldCenter().y<< std::endl ;

        /* TODO : add your code here */
        //std::cout << "Press !" << std::endl ;
    }
    if(event->type() == QEvent::MouseMove)
    {
        if(joint != NULL){
        x = static_cast<QMouseEvent*>(event)->globalX()/30 - 7;
        y = 22 - static_cast<QMouseEvent*>(event)->globalY()/30;
        joint->SetTarget(b2Vec2(x,y));
        }
        //std::cout << "Move !" << std::endl ;
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(weldjoint != NULL){
            world->DestroyJoint(weldjoint);
            weldjoint = NULL;
            /*b2Filter filter;
            filter.groupIndex = -3;
            itemList.at(3)->getBody().GetFixtureList()->SetFilterData(filter);
            itemList.at(4)->getBody().GetFixtureList()->SetFilterData(filter);
            itemList.at(1)->getBody().GetFixtureList()->SetFilterData(filter);*/
            //std::cout<<itemList.at(4)->getBody().GetFixtureList()->GetFilterData().groupIndex;
            b2Vec2 test =  items.at(1)->getBody().GetWorldCenter() - itemList.at(birdID)->getBody().GetWorldCenter();
            test.y = test.y + 0.6*test.y;
            test.x = test.x - 0.5*test.x;
            itemList.at(birdID)->getBody().SetLinearVelocity(2*test.Length()*test.Normalize()*test);

            birdID++;


            /*filter.groupIndex = -3;
            itemList.at(3)->getBody().GetFixtureList()->SetFilterData(filter);
            itemList.at(4)->getBody().GetFixtureList()->SetFilterData(filter);
            filter.groupIndex = 0;
            itemList.at(1)->getBody().GetFixtureList()->SetFilterData(filter);*/
        }
        if(joint != NULL){
            world->DestroyJoint(joint);
            joint = NULL;
        }
        //std::cout << "Release !" << std::endl ;
        /* TODO : add your code here */
        //std::cout << "Release !" << std::endl ;
    }
}
    return false;
}



void MainWindow::tick()
{
    /*for(QList<Block*>::iterator i = block.begin(); i != block.end(); i++){
        (*i)->gethealth() -= (int)imp;
        imp = 0;
        if((*i)->gethealth() <= 0){
            if((*i)->getshoulddisappear() == true ){
                world->DestroyBody(&(*i)->getBody());
                block.erase(i);
                continue;
            }
            (*i)->setpixmap(QPixmap(":/image/dispear.png").scaled(height()/9, height()/9),1,1);
            (*i)->disappear();
        }
    }*/

    if(score != 0){
        lcd->display(lcd->intValue() + score);
        score = 0;
    }

    //block disappear

    for(int i = 0; i != block.length(); i++){

        if(block.at(i)->getshoulddisappear() == true && block.at(i)->getBody().IsActive()){
            //world->DestroyBody(&block.at(i)->getBody());
            //block.removeAt(i);
            block.at(i)->getBody().SetTransform(b2Vec2(100,0),0);
            block.at(i)->getBody().SetActive(false);
            break;
        }


        if(feature == block.at(i)->getBody().GetFixtureList()->GetUserData() ){
            block.at(i)->gethealth() -= (int)imp;
            imp = 0;
            feature = NULL;

            if(block.at(i)->gethealth() < 200 && block.at(i)->gethealth() > 0)
                block.at(i)->setpixmap(QPixmap(":/image/block11.png").scaled(60,60),2,2);

            if(block.at(i)->gethealth() <= 0){
                block.at(i)->setpixmap(QPixmap(":/image/dispear.png").scaled(60,60),2,2);
                block.at(i)->disappear();
            }
        }
    }

    //enemy disappear


    for(int i = 0; i != enemy.length(); i++){

        if(enemy.at(i)->getshoulddisappear() == true && enemy.at(i)->getBody().IsActive()){
            //world->DestroyBody(&enemy.at(i)->getBody());
            //enemy.removeAt(i);
            enemy.at(i)->getBody().SetTransform(b2Vec2(100,0),0);
            enemy.at(i)->getBody().SetActive(false);
            break;
        }


        if(feature == enemy.at(i)->getBody().GetFixtureList()->GetUserData() ){
            enemy.at(i)->gethealth() -= (int)imp;
            imp = 0;
            feature = NULL;

            if(enemy.at(i)->gethealth() < 200 && enemy.at(i)->gethealth() > 0)
                enemy.at(i)->setpixmap(QPixmap(":/image/pig3.png").scaled(60,60),1);

            if(enemy.at(i)->gethealth() <= 0){
                enemy.at(i)->setpixmap(QPixmap(":/image/dispear2.png").scaled(60,60),1);
                enemy.at(i)->disappear();
            }
        }
    }

    /*if(delbody != NULL){
        world->DestroyBody(delbody);
        delbody =NULL;
    }*/


    world->Step(1.0/60.0,10,10);
    scene->update();



    /*b2Body *del = world->GetBodyList();
    if(birdID == 5)
        for(int k = 1;k != world->GetBodyCount(); k++){
            b2Body *tempdel = del->GetNext();
            world->DestroyBody(del);
            del = tempdel;
        }*/

    /*if(birdID == 5){
        for(b2Body* k = world->GetBodyList();k != NULL; k = k->GetNext()){
            //b2Body *tempdel = del->GetNext();
            qDebug()<<"deldeldeldeldleldledl";
            world->DestroyBody(k);
            //del = tempdel;
        }
    }*/


}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
    this->close();
}

void MainWindow::restart()
{
    birdID = 0;


    for(int i = 0; i != enemy.length();i++)
        enemy.at(i)->getBody().SetActive(true);
    for(int i = 0; i != block.length(); i++)
        block.at(i)->getBody().SetActive(true);

    enemy.at(0)->resetdisappear();
    enemy.at(1)->resetdisappear();

    enemy.at(0)->getBody().SetLinearVelocity(b2Vec2(0,0));
    enemy.at(0)->getBody().SetTransform(b2Vec2(19,5),0);
    enemy.at(0)->setpixmap(QPixmap(":/image/enemy1.png").scaled(60,60),1);
    enemy.at(0)->gethealth() = 325;
    enemy.at(1)->getBody().SetLinearVelocity(b2Vec2(0,0));
    enemy.at(1)->getBody().SetTransform(b2Vec2(21.5,7),0);
    enemy.at(1)->setpixmap(QPixmap(":/image/pig.png").scaled(60,60),1);
    enemy.at(1)->gethealth() = 375;

    block.at(0)->resetdisappear();
    block.at(1)->resetdisappear();
    block.at(2)->resetdisappear();
    block.at(3)->resetdisappear();
    block.at(4)->resetdisappear();
    block.at(5)->resetdisappear();
    block.at(6)->resetdisappear();
    block.at(7)->resetdisappear();

    block.at(0)->getBody().SetTransform(b2Vec2(18,4),0);
    block.at(1)->getBody().SetTransform(b2Vec2(18,6),0);
    block.at(2)->getBody().SetTransform(b2Vec2(18,8),0);
    block.at(3)->getBody().SetTransform(b2Vec2(20,8),0);
    block.at(4)->getBody().SetTransform(b2Vec2(22,8),0);
    block.at(5)->getBody().SetTransform(b2Vec2(24,8),0);
    block.at(6)->getBody().SetTransform(b2Vec2(24,6),0);
    block.at(7)->getBody().SetTransform(b2Vec2(24,4),0);

    block.at(0)->gethealth() = 400;
    block.at(1)->gethealth() = 400;
    block.at(2)->gethealth() = 400;
    block.at(3)->gethealth() = 400;
    block.at(4)->gethealth() = 400;
    block.at(5)->gethealth() = 400;
    block.at(6)->gethealth() = 400;
    block.at(7)->gethealth() = 400;

    block.at(0)->setpixmap(QPixmap(":/image/block1.png").scaled(60,60),2,2);
    block.at(1)->setpixmap(QPixmap(":/image/block1.png").scaled(60,60),2,2);
    block.at(2)->setpixmap(QPixmap(":/image/block1.png").scaled(60,60),2,2);
    block.at(3)->setpixmap(QPixmap(":/image/block1.png").scaled(60,60),2,2);
    block.at(4)->setpixmap(QPixmap(":/image/block1.png").scaled(60,60),2,2);
    block.at(5)->setpixmap(QPixmap(":/image/block1.png").scaled(60,60),2,2);
    block.at(6)->setpixmap(QPixmap(":/image/block1.png").scaled(60,60),2,2);
    block.at(7)->setpixmap(QPixmap(":/image/block1.png").scaled(60,60),2,2);

    temp->setpixmap(QPixmap(":/image/angry-bird-white-icon.png").scaled(60,60),1);
    temp->getBody().SetBullet(true);
    temp->getBody().GetFixtureList()->SetDensity(10.0f);
    temp->getBody().ResetMassData();

    tempb->clear();

    itemList.at(0)->getBody().SetLinearVelocity(b2Vec2(0,0));
    itemList.at(1)->getBody().SetLinearVelocity(b2Vec2(0,0));
    itemList.at(2)->getBody().SetLinearVelocity(b2Vec2(0,0));
    itemList.at(3)->getBody().SetLinearVelocity(b2Vec2(0,0));

    itemList.at(0)->getBody().SetTransform(b2Vec2(2,10),0);
    itemList.at(1)->getBody().SetTransform(b2Vec2(5,17),0);
    itemList.at(2)->getBody().SetTransform(b2Vec2(3,17),0);
    itemList.at(3)->getBody().SetTransform(b2Vec2(1,17),0);


    itemList.at(0)->resetcollide();
    itemList.at(1)->resetcollide();
    itemList.at(2)->resetcollide();
    itemList.at(3)->resetcollide();

    for(int l = 0; l < 5; l++){
        ball.at(l)->getBody().SetTransform(b2Vec2(15, 12 + 2*l),0);
        ball.at(l)->getBody().SetLinearVelocity(b2Vec2(0,0));
        ball.at(l+5)->getBody().SetTransform(b2Vec2(28, 12 + 2*l),0);
        ball.at(l+5)->getBody().SetLinearVelocity(b2Vec2(0,0));
    }


    lcd->display(0);



}


