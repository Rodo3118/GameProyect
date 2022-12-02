
#include "Play.h"
#include "HelloWorldScene.h"
#include "nivel1.h"
#include "nivel3.h"
#include <cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* Play::createScene()
{
    return Play::create();
}

// Print useful error message instead of segfaulting when files are not there.

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Play::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto fondo = Sprite::create("fondo1.png");
    fondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    addChild(fondo, 0);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Play::menuCloseCallback, this));
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

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("PLAY", "fonts/Marker Felt.ttf", 60);
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


    auto nivel2 = MenuItemImage::create("stereo.jpg", "stereo.jpg", CC_CALLBACK_1(Play::Nivel1, this));
    auto nivel3 = MenuItemImage::create("jumper.jpg", "jumper.jpg", CC_CALLBACK_1(Play::Nivel3, this));
    auto Back = MenuItemImage::create("Back.jpg", "Back.jpg", CC_CALLBACK_1(Play::ImageButton, this));

    nivel2->setPosition(Point((visibleSize.width / 4) * 2, (visibleSize.height / 4)*3));
    nivel3->setPosition(Point((visibleSize.width / 4) * 2, (visibleSize.height / 4)*1));
    Back->setPosition(Point((visibleSize.width / 10) , (visibleSize.height / 10)*9));



    auto* menu2 = Menu::create( nivel2,nivel3, Back, NULL);
    menu2->setPosition(Point(0, 0));
    this->addChild(menu2);


    return true;
}



void Play::ImageButton(cocos2d::Ref* pSender)
{
   CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    auto Back = HelloWorld::createScene();
   Director::getInstance()->replaceScene(Back);
}

void Play::Nivel1(cocos2d::Ref* pSender)
{
    auto nivel2 = nivel1::createScene();
    Director::getInstance()->replaceScene(nivel2);
}
void Play::Nivel3(cocos2d::Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("playSound_01.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("playSound_01.mp3");
    auto nivel3 = nivel3::createScene();
    //Director::getInstance()->trans
    Director::getInstance()->replaceScene(TransitionFade::create(.2,nivel3));


}
void Play::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    int a = 0;
    Director::getInstance()->end();
}

