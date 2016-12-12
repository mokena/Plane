#include "StartScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "background" splash screen"
    auto sprite = Sprite::create("bg.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

	// add start menu 
	auto *chnStrings = Dictionary::createWithContentsOfFile("res.xml");
	const char *startGmStr = ((String*)chnStrings->objectForKey("start_game"))->getCString();
	Label* startGameLbl = Label::createWithSystemFont(startGmStr, "Arial", 24);	

	MenuItem* startGame = MenuItemLabel::create(startGameLbl, this, menu_selector(StartScene::startMenuHandler));
	startGame->setContentSize(startGameLbl->getContentSize());
	Menu* menu = Menu::create(startGame, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height*0.3f + origin.y));
	this->addChild(menu);

	// add animation
	Animation* animation = Animation::create();
	char str[20] = { 0 };
	for (int i = 1; i < 5; i++) {
		sprintf(str, "start%d.png", i);
		animation->addSpriteFrameWithFileName(str);
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);
	Animate* animate = Animate::create(animation);
	Sprite* startAnim = Sprite::create("start1.png");
	startAnim->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(startAnim);
	startAnim->runAction(animate);
    
    return true;
}

void StartScene::startMenuHandler(Ref* ref) {
	Scene* playScene = PlayScene::createScene();
	auto reScene =CCTransitionFadeTR::create(0.5f, playScene);
	
	Director::getInstance()->replaceScene(reScene);
}


void StartScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
