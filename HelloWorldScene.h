#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    bool onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    cocos2d::Sprite *cubito;

    void Play(Ref* pSender);
    void Settings(Ref* pSender);
    void Highscores(Ref* pSender);

};

#endif // __HELLOWORLD_SCENE_H__
