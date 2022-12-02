
#include "winner.h"
#include "HelloWorldScene.h"
#include "nivel3.h"
#include <cocostudio/SimpleAudioEngine.h>
USING_NS_CC;

Scene* winner::createScene()
{
    return winner::create();
}
bool winner::init()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

   
    auto playagain = MenuItemImage::create("playagain.png", "playagain.png", CC_CALLBACK_1(winner::ImageButton, this));
    playagain->setPosition(Point((visibleSize.width / 4) * 1, (visibleSize.height / 2)));

    auto mainmenu = MenuItemImage::create("mainmenu.png", "mainmenu.png", CC_CALLBACK_1(winner::mainmenu, this));
    mainmenu->setPosition(Point((visibleSize.width / 4) * 2, (visibleSize.height / 2)));

    auto exitgame = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(winner::exit, this));
    exitgame->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 2)));





    auto* menu2 = Menu::create(playagain,mainmenu,exitgame, NULL);
    menu2->setPosition(Point(0, 0));
    this->addChild(menu2);
    auto nombre = Label::createWithTTF("Winner Winner Chicken Dinner", "fonts/Marker Felt.ttf", 100);
    nombre->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - nombre->getContentSize().height));
    this->addChild(nombre, 1);

    return true;
}

void winner::ImageButton(cocos2d::Ref* pSender)
{
    auto Back = nivel3::createScene();
    Director::getInstance()->replaceScene(Back);
}
void winner::mainmenu(cocos2d::Ref* pSender)
{
    auto Back = HelloWorld::createScene();
    Director::getInstance()->replaceScene(Back);
}
void winner::exit(cocos2d::Ref* pSender)
{
    Director::getInstance()->end();
}












