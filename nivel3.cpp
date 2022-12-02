
#include "nivel3.h"
#include "winner.h"
#include "Play.h"
#include "CCProperties.h"
#include <openssl/err.h>
#include <cocostudio/SimpleAudioEngine.h>

using namespace std;
//#include"AudioEngine.h"

USING_NS_CC;
int score = 0;

Scene* nivel3::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    scene->getPhysicsWorld()->setGravity( Vec2( 0, -1000 ) );

    auto layer = nivel3::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

bool nivel3::init()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("stereo.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("stereo.mp3");

    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    auto listener = EventListenerTouchOneByOne().create();
    auto listenerKeyboard = EventListenerKeyboard().create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(nivel3::onTouchBegan, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(nivel3::onKeyReleased, this);


    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height/3 +350 ));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);


    fondo = Sprite::create("fondo4.png");
    fondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    addChild(fondo, 0);

    fondo2 = Sprite::create("fondo4.png");
    fondo2->setPosition(Vec2(visibleSize.width + visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(fondo2, 0);

    auto fondo1mover = RepeatForever::create(MoveBy::create(2, Vec2(-visibleSize.width / 2, 0)));
    fondo->runAction(fondo1mover);
    auto fondo2mover = RepeatForever::create(MoveBy::create(2, Vec2(-visibleSize.width / 2, 0)));
    fondo2->runAction(fondo2mover);
    this->scheduleUpdate();

    abajo = Sprite::create("abajo22.png");
    abajo->setAnchorPoint(Vec2::ZERO);
    abajo->setPosition(Vec2::ZERO);
    this->addChild(abajo, 0);


    auto nombre = Label::createWithTTF("Nivel2", "fonts/Marker Felt.ttf", 60);
    nombre->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - nombre->getContentSize().height));
    this->addChild(nombre, 1);

    puntuacion = Label::createWithTTF("-", "fonts/Marker Felt.ttf", 60);
    puntuacion->setPosition(Vec2(origin.x + visibleSize.width / 4 * 3, origin.y + visibleSize.height - puntuacion->getContentSize().height));
    this->addChild(puntuacion, 1);
    this->schedule(CC_SCHEDULE_SELECTOR(nivel3::ScoreBoard), .1);

    auto Back = MenuItemImage::create("Back.jpg", "Back.jpg", CC_CALLBACK_1(nivel3::ImageButton, this));
    Back->setPosition(Point((visibleSize.width / 10), (visibleSize.height / 10) * 9));
    auto* menu2 = Menu::create(Back, NULL);
    menu2->setPosition(Point(0, 0));
    this->addChild(menu2);
    {
        cubito = Sprite::create("cubitoreal.png");
        cubito->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y - 48));
        auto cubitobody = PhysicsBody::createBox(cubito->getContentSize(), PhysicsMaterial(0, 0, 0));
        cubitobody->setCollisionBitmask(1);
        cubitobody->setContactTestBitmask(true);
        cubito->setPhysicsBody(cubitobody);
        this->addChild(cubito, 0);
    }
    {
        spike = Sprite::create("triangulo.png");
        spike->setPosition(Vec2(visibleSize.width / 2 + origin.x + 700, visibleSize.height / 3 + origin.y - 40));
        auto spikebody = PhysicsBody::createCircle(30, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spike->setPhysicsBody(spikebody);
        this->addChild(spike, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        spike->runAction(moverspike);
    }
      
    {
        spike2 = Sprite::create("triangulo.png");
        spike2->setPosition(Vec2(visibleSize.width / 2 + origin.x + 500, visibleSize.height / 3 + origin.y - 40));
        auto spikebody = PhysicsBody::createCircle(30, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spike2->setPhysicsBody(spikebody);
        this->addChild(spike2, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        spike2->runAction(moverspike);
    }

    {
        spike3 = Sprite::create("triangulo.png");
        auto spikebody = PhysicsBody::createCircle(30, PhysicsMaterial(10000, 0, 10000));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spike3->setPhysicsBody(spikebody);
        this->addChild(spike3, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        spike3->runAction(moverspike);
    }

    {
        spike4 = Sprite::create("triangulo.png");
        auto spikebody = PhysicsBody::createCircle(30, PhysicsMaterial(10000, 0, 10000));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spike4->setPhysicsBody(spikebody);
        this->addChild(spike4, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        spike4->runAction(moverspike);
    }

    {
        spikes = Sprite::create("triangulos.png");
        spikes->setPosition(Vec2(visibleSize.width / 2 + origin.x + 230, visibleSize.height / 3 + origin.y - 40));
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikes->setPhysicsBody(spikebody);
        this->addChild(spikes, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        spikes->runAction(moverspike);
    }

    {
        spikes2 = Sprite::create("triangulos.png");
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikes2->setPhysicsBody(spikebody);
        this->addChild(spikes2, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        spikes2->runAction(moverspike);
    }

    {
        spikes3 = Sprite::create("triangulos.png");
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikes3->setPhysicsBody(spikebody);
        this->addChild(spikes3, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        spikes3->runAction(moverspike);
    }

    {
        spikes4 = Sprite::create("triangulos.png");
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikes4->setPhysicsBody(spikebody);
        this->addChild(spikes4, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        spikes4->runAction(moverspike);
    }

    {
        spikes5 = Sprite::create("triangulos.png");
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikes5->setPhysicsBody(spikebody);
        this->addChild(spikes5, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        spikes5->runAction(moverspike);
    }

    {
        spikes6 = Sprite::create("triangulos.png");
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikes6->setPhysicsBody(spikebody);
        this->addChild(spikes6, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        spikes6->runAction(moverspike);
    }

    {
        bola = Sprite::create("bola.png");
        bola->setPosition(Vec2(visibleSize.width / 2 + origin.x + 700, visibleSize.height / 3 + origin.y + 340));
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        bola->setPhysicsBody(spikebody);
        this->addChild(bola, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        bola->runAction(moverspike);
    }
    {
        bola2 = Sprite::create("moneda (1).png");
        auto spikebody = PhysicsBody::createCircle(100, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(4);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        bola2->setPhysicsBody(spikebody);
        this->addChild(bola2, 0);
        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        bola2->runAction(moverspike);
    }


    {
        razor = Sprite::create("razor.png");
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        razor->setPhysicsBody(spikebody);
        this->addChild(razor, 0);
        auto rotarrazor = RepeatForever::create(RotateBy::create(1.5, 360));
        razor->runAction(rotarrazor);

        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        razor->runAction(moverspike);
    }

    {
        razor2 = Sprite::create("razor.png");
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        razor2->setPhysicsBody(spikebody);
        this->addChild(razor2, 0);
        auto rotarrazor = RepeatForever::create(RotateBy::create(1.5, 360));
        razor2->runAction(rotarrazor);

        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        razor2->runAction(moverspike);
    }

    {
        razor3 = Sprite::create("razor.png");
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        razor3->setPhysicsBody(spikebody);
        this->addChild(razor3, 0);
        auto rotarrazor = RepeatForever::create(RotateBy::create(1.5, 360));
        razor3->runAction(rotarrazor);

        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        razor3->runAction(moverspike);
    }

    {
        razor4 = Sprite::create("razor.png");
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        razor4->setPhysicsBody(spikebody);
        this->addChild(razor4, 0);
        auto rotarrazor = RepeatForever::create(RotateBy::create(1.5, 360));
        razor4->runAction(rotarrazor);

        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        razor4->runAction(moverspike);
    }

    {
        razor5 = Sprite::create("razor.png");
        auto spikebody = PhysicsBody::createCircle(40, PhysicsMaterial(0, 0, 0));
        spikebody->setCollisionBitmask(2);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        razor5->setPhysicsBody(spikebody);
        this->addChild(razor5, 0);
        auto rotarrazor = RepeatForever::create(RotateBy::create(1.5, 360));
        razor5->runAction(rotarrazor);

        auto moverspike = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        razor5->runAction(moverspike);
    }

    {
        base = Sprite::create("base.png");
        base->setPosition(Vec2(visibleSize.width / 2 + origin.x+100, visibleSize.height / 3 + origin.y -48));
        auto spikebody = PhysicsBody::createBox(base->getContentSize(), PhysicsMaterial(10000, 0, 10000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base->setPhysicsBody(spikebody);
        this->addChild(base, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
         base->runAction(moverbase);
    }

    {
        base11 = Sprite::create("base.png");
        auto spikebody = PhysicsBody::createBox(base->getContentSize(), PhysicsMaterial(10000, 0, 10000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base11->setPhysicsBody(spikebody);
        this->addChild(base11, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        base11->runAction(moverbase);
    }

    {
        base12 = Sprite::create("base.png");
        auto spikebody = PhysicsBody::createBox(base->getContentSize(), PhysicsMaterial(10000, 0, 10000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base12->setPhysicsBody(spikebody);
        this->addChild(base12, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        base12->runAction(moverbase);
    }

    {
        base2 = Sprite::create("doscubos.png");
        base2->setPosition(Vec2(visibleSize.width / 2 + origin.x + 370, visibleSize.height / 3 + origin.y - 20));
        auto spikebody = PhysicsBody::createBox(base2->getContentSize(), PhysicsMaterial(1000000, 0, 1000000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base2->setPhysicsBody(spikebody);
        this->addChild(base2, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        base2->runAction(moverbase);
    }

    {
        base21 = Sprite::create("doscubos.png");
        base21->setPosition(Vec2(visibleSize.width / 2 + origin.x + 850, visibleSize.height / 3 + origin.y - 20));
        auto spikebody = PhysicsBody::createBox(base2->getContentSize(), PhysicsMaterial(1000000, 0, 1000000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base21->setPhysicsBody(spikebody);
        this->addChild(base21, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        base21->runAction(moverbase);
    }

    {
        base3 = Sprite::create("trescubos.png");
        base3->setPosition(Vec2(visibleSize.width / 2 + origin.x + 600, visibleSize.height / 3 + origin.y +30 ));
        auto spikebody = PhysicsBody::createBox(base3->getContentSize(), PhysicsMaterial(1000000, 0, 1000000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base3->setPhysicsBody(spikebody);
        this->addChild(base3, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        base3->runAction(moverbase);
    }

    {
        base31 = Sprite::create("trescubos.png");
        base31->setPosition(Vec2(visibleSize.width / 2 + origin.x + 600, visibleSize.height / 3 + origin.y + 30));
        auto spikebody = PhysicsBody::createBox(base31->getContentSize(), PhysicsMaterial(1000000, 0, 1000000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base31->setPhysicsBody(spikebody);
        this->addChild(base31, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        base31->runAction(moverbase);
    }

    {
        base32 = Sprite::create("trescubos.png");
        base32->setPosition(Vec2(visibleSize.width / 2 + origin.x + 600, visibleSize.height / 3 + origin.y + 30));
        auto spikebody = PhysicsBody::createBox(base32->getContentSize(), PhysicsMaterial(1000000, 0, 1000000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base32->setPhysicsBody(spikebody);
        this->addChild(base32, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        base32->runAction(moverbase);
    }

    {
        base4 = Sprite::create("cubito4.png");
        auto spikebody = PhysicsBody::createBox(base4->getContentSize(), PhysicsMaterial(1000000, 0, 1000000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base4->setPhysicsBody(spikebody);
        this->addChild(base4, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        base4->runAction(moverbase);
    }

    {
        base41 = Sprite::create("cubito4.png");
        auto spikebody = PhysicsBody::createBox(base41->getContentSize(), PhysicsMaterial(1000000, 0, 1000000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base41->setPhysicsBody(spikebody);
        this->addChild(base41, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        base41->runAction(moverbase);
    }

    {
        base42 = Sprite::create("cubito4.png");
        auto spikebody = PhysicsBody::createBox(base42->getContentSize(), PhysicsMaterial(1000000, 0, 1000000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base42->setPhysicsBody(spikebody);
        this->addChild(base42, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        base42->runAction(moverbase);
    }

    {
        base5 = Sprite::create("base5.png");
        auto spikebody = PhysicsBody::createBox(base5->getContentSize(), PhysicsMaterial(1000000, 0, 1000000));
        spikebody->setCollisionBitmask(3);
        spikebody->setContactTestBitmask(true);
        spikebody->setGravityEnable(false);
        base5->setPhysicsBody(spikebody);
        this->addChild(base5, 0);
        auto moverbase = RepeatForever::create(MoveBy::create(1.5, Vec2(-visibleSize.width / 2, 0)));
        base5->runAction(moverbase);
    }




    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(nivel3::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;

}



void nivel3::update(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    score ++;
    scoreS = to_string(score);
    puntuacion->setString("Puntuacion: "+scoreS);
    CCLOG("Puntuacion: %i",score);
    if (fondo->getPosition().x <= -visibleSize.width / 2)
    {
        fondo->setPosition(Vec2(visibleSize.width + visibleSize.width / 2 - 5, visibleSize.height / 2 + origin.y));
    }
    if (fondo2->getPosition().x <= -visibleSize.width / 2)
    {
        fondo2->setPosition(Vec2(visibleSize.width + visibleSize.width / 2 - 5, visibleSize.height / 2 + origin.y));
    }

    if (cubito->getPosition().x != visibleSize.width / 5)
    {
        cubito->setPosition(Vec2(visibleSize.width / 5, cubito->getPosition().y));
    }
    if (cubito->getPosition().y <= 0)
    {
        cubito->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 3 + origin.y - 48));
    }
    if (score == 60)
    {
        spike3->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 40));
    }
    if (score == 110)
    {
        spike4->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 40));
    }
    if (score == 160)
    {
        base->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y -40));
    }
    if (score == 175)
    {
       razor->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 48));
    }
    
    if (score == 250)
    {
        base11->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y -48));
    }
    if (score == 265)
    {
        spike->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 30));
    }
    if (score == 280)
    {
        base2->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 10));
    }
    if (score == 290)
    {
        razor2->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y +250));
    }

    if (score == 300)
    {
        spike2->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 30));
    }
    if (score == 310)
    {
        base->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 48));
    }
    if (score == 325)
    {
        spikes3->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 10));
    }
    if (score == 340)
    {
        base21->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 10));
    }
    if (score == 355)
    {
        spikes2->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y ));
    }
    if (score == 370)
    {
        base3->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y +30));
    }
    if (score == 385)
    {
        spikes->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y ));
    }
    if (score == 400)
    {
        base4->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 30));
    }
    if (score == 410)
    {
        razor->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 400));
    }
    if (score == 415)
    {
        spikes4->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 30));
    }
    if (score == 430)
    {
        base32->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 30));
    }
    if (score == 445)
    {
        spike2->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 30));
    }
    if (score == 460)
    {
        base41->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 30));
    }
    if (score == 475)
    {
        spike3->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 30));
    }
    if (score == 490)
    {
        base5->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 100));
    }
    if (score == 505)
    {
        spikes->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 100));
    }
    if (score == 520)
    {
        base42->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 30));
    }
    if (score == 535)
    {
        spikes2->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 30));
    }
    if (score == 550)
    {
        base3->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 30));
    }
    if (score == 565)
    {
        spikes3->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 10));
    }
    if (score == 580)
    {
        base2->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 10));
    }
    if (score == 595)
    {
        spikes5->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y +30));
    }
    if (score == 610)
    {
        base11->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y - 48));
    }
    if (score == 625)
    {
        spikes6->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y +30));
    }
    if (score == 650)
    {
        razor->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y +50));
    }
    if (score == 670)
    {
        razor2->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 50));
    }
    if (score == 690)
    {
        razor3->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 50));
    }
    if (score == 710)
    {
        razor4->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y + 50));
    }


    if (score == 780)
    {
        bola->setPosition(Vec2(visibleSize.width / 4 * 4, visibleSize.height / 3 + origin.y -35));
    }
    if (score == 850)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("endStart_02.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("endStart_02.mp3");
    }

    if (score == 900)
    {
        bola2->setPosition(Vec2(visibleSize.width / 4 * 3.5, visibleSize.height / 3 + origin.y +50));
    }

}

void nivel3::ScoreBoard(float points)
{
   // score = score + .5;
   // scoreS = std::to_string(score);
   // puntuacion->setString("Score: " + scoreS);
}
bool nivel3::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        score = 0;
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("explode_11.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explode_11.mp3");
        auto repeat = nivel3::createScene();
        Director::getInstance()->replaceScene(repeat);
    }
    else if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()) || (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        score = 0;
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        auto plei = winner::createScene();
        Director::getInstance()->replaceScene(plei);
    }

    return true;
}


void nivel3::ImageButton(cocos2d::Ref* pSender)
{
    auto Back = Play::createScene();
    Director::getInstance()->replaceScene(Back);
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

}


bool nivel3::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto salto = JumpBy::create(.4, Point(0, 130), 150, 1);
    auto rotar = RotateBy::create(.4, 90);
    cubito->runAction(salto);
    cubito->runAction(rotar);

    return true;
}

bool nivel3::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
    if (key == EventKeyboard::KeyCode::KEY_SPACE) {
        auto salto = JumpBy::create(.4, Point(0, 130), 150, 1);
        auto rotar = RotateBy::create(.4, 90);
        cubito->runAction(salto);
        cubito->runAction(rotar);
    }

    else if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) {
        auto salto = JumpBy::create(.4, Point(0, 130), 150, 1);
        auto rotar = RotateBy::create(.4, 90);
        cubito->runAction(salto);
        cubito->runAction(rotar);
    }

    return true;

}

