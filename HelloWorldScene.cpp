
#include "HelloWorldScene.h"
#include "Play.h"
#include <cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto fondo = Sprite::create("fondo33.png");
    fondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    addChild(fondo, 0);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    //auto cocos2d::MenuItemImage* test = MenuItemImage::create()

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(30);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("principel.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("principel.mp3");
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("CUBITO SALTANTE", "fonts/Marker Felt.ttf", 60);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

        auto menu_item_3 = MenuItemImage::create("PlayNN.png", "PlaySS.jpg", CC_CALLBACK_1(HelloWorld::Play, this));

        menu_item_3->setPosition(Point((visibleSize.width / 4) * 2, (visibleSize.height / 2)));


        
        auto* menu2 = Menu::create( menu_item_3,NULL);
        menu2->setPosition(Point(0, 0));
        this->addChild(menu2);
        //auto action = RepeatForever::create(RotateBy::create(0.5, 45));

    
    return true;
}


void HelloWorld::Play(cocos2d::Ref* pSender)
{
    auto Play = Play::createScene();
    Director::getInstance()->replaceScene(Play);

}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    int a = 0;
    Director::getInstance()->end();
}