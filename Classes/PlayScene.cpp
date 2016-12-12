#include "PlayScene.h"

Scene* PlayScene::createScene() {
	Scene* scene = Scene::create();

	PlayScene* layer = PlayScene::create();
	scene->addChild(layer);

	return scene;
}

bool PlayScene::init() {
	if (Layer::init() == false) {
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	// running background
	bg1 = Sprite::create("bgs.png");
	bg1->setAnchorPoint(Vec2(0.5f, 0.5f));
	bg1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(bg1);

	bg2 = Sprite::create("bgs.png");
	bg2->setAnchorPoint(Vec2(0.5f, 0.5f));
	bg2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height + visibleSize.height / 2));
	addChild(bg2);

	// add hero
	initHeroPlane(1);

	scheduleUpdate();

	return true;
}

void PlayScene::initHeroPlane(int index) {
	Animation* animation = Animation::create();
	for (int i = 1; i <= 2; i++) {
		/*auto str = StringUtils::format("plane/heros%d_%d", index, i);*/
		auto str = StringUtils::format("plane/heros%d_%d.png", index, i);
		animation->addSpriteFrameWithFileName(str.c_str());
	}
	animation->setDelayPerUnit(0.4f);
	animation->setLoops(-1);
	Animate* anim = Animate::create(animation);

	hero = Sprite::create(StringUtils::format("plane/heros%d_1.png", index).c_str());
	hero->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.2f));
	addChild(hero);
	hero->runAction(anim);
}


void PlayScene::update(float dt) {

	if (bg1->getPositionY() < -visibleSize.height / 2) {
		bg1->setPositionY(visibleSize.height / 2 + visibleSize.height);
	}

	if (bg2->getPositionY() < -visibleSize.height / 2) {
		bg2->setPositionY(visibleSize.height / 2 + visibleSize.height);
	}

	bg1->setPositionY(bg1->getPositionY() - 5);
	bg2->setPositionY(bg2->getPositionY() - 5);
}