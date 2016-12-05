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

	bg1 = Sprite::create("bgs.png");
	bg1->setAnchorPoint(Vec2(0.5f, 0.5f));
	bg1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(bg1);

	bg2 = Sprite::create("bgs.png");
	bg2->setAnchorPoint(Vec2(0.5f, 0.5f));
	bg2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height + visibleSize.height / 2));
	addChild(bg2);

	scheduleUpdate();

	return true;
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