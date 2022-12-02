#ifndef __NIVEL1_SCENE_H__
#define __NIVEL1_SCENE_H__

#include "cocos2d.h"

class nivel1 : public cocos2d::Scene
{

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(nivel1);

    void Play(Ref* pSender);
    void ImageButton(Ref* pSender);
};

#endif // __Settings_SCENE_H__
