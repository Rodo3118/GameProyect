
#include "nivel1.h"
#include "Play.h"
#include <cocostudio/SimpleAudioEngine.h>
USING_NS_CC;

Scene* nivel1::createScene()
{
    return nivel1::create();
}
bool nivel1::init()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

   
    auto Back = MenuItemImage::create("Back.jpg", "Back.jpg", CC_CALLBACK_1(nivel1::ImageButton, this));
    Back->setPosition(Point((visibleSize.width / 10), (visibleSize.height / 10) * 9));



    auto* menu2 = Menu::create(Back, NULL);
    menu2->setPosition(Point(0, 0));
    this->addChild(menu2);
    auto label = Label::createWithTTF("COMING SOON...", "fonts/Marker Felt.ttf", 200);

  
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,visibleSize.height /2));
        this->addChild(label, 1);

    return true;
}

void nivel1::ImageButton(cocos2d::Ref* pSender)
{
    auto Back = Play::createScene();
    Director::getInstance()->replaceScene(Back);
}












