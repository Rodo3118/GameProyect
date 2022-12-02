#ifndef __NIVEL3_SCENE_H__
#define __NIVEL3_SCENE_H__

#include "cocos2d.h"
#include <string>
extern int score;
class nivel3 : public cocos2d::Scene
{
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(nivel3);
private:
    cocos2d::Label* puntuacion;
    cocos2d::Sprite* fondo;
    cocos2d::Sprite* fondo2;
    cocos2d::Sprite* abajo;
    cocos2d::Sprite* cubito;

    cocos2d::Sprite* spike;
    cocos2d::Sprite* spike2;
    cocos2d::Sprite* spike3;
    cocos2d::Sprite* spike4;
    cocos2d::Sprite* spike5;

    cocos2d::Sprite* spikes;
    cocos2d::Sprite* spikes2;
    cocos2d::Sprite* spikes3;
    cocos2d::Sprite* spikes4;
    cocos2d::Sprite* spikes5;
    cocos2d::Sprite* spikes6;


    cocos2d::Sprite* bola;
    cocos2d::Sprite* bola2;


    cocos2d::Sprite* razor;
    cocos2d::Sprite* razor2;
    cocos2d::Sprite* razor3;
    cocos2d::Sprite* razor4;
    cocos2d::Sprite* razor5;


    cocos2d::Sprite* base;
    cocos2d::Sprite* base11;
    cocos2d::Sprite* base12;

    cocos2d::Sprite* base2;
    cocos2d::Sprite* base21;
    cocos2d::Sprite* base22;

    
    cocos2d::Sprite* base3;
    cocos2d::Sprite* base31;
    cocos2d::Sprite* base32;

    cocos2d::Sprite* base4;
    cocos2d::Sprite* base41;
    cocos2d::Sprite* base42;


    cocos2d::Sprite* base5;
    cocos2d::Sprite* base51;
    void update(float dt);
    void ImageButton(Ref* pSender);

    void nivel3::ScoreBoard(float points);
    std::string scoreS;

    cocos2d::PhysicsWorld* sceneWorld;

    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };

    bool onContactBegin(cocos2d::PhysicsContact& contact);

};

#endif // __NIVEL3_SCENE_H__
