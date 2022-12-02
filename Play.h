#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"

class Play : public cocos2d::Scene
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
    CREATE_FUNC(Play);
    cocos2d::Sprite* cubito;

   
    void Nivel1(Ref* pSender);
    void Nivel3(Ref* pSender);
    void ImageButton(Ref* pSender);
};

#endif // __Settings_SCENE_H__
