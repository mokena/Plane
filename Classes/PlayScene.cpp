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

	// control the hero
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* t, Event* e) {
		Vec2 pos = t->getLocation();
		if (hero->getBoundingBox().containsPoint(pos)) {
			return true;
		}
		return false;
	};
	listener->onTouchMoved = [&](Touch* t, Event* e) {
		hero->setPosition(t->getLocation());
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	// add enemies
	schedule(schedule_selector(PlayScene::addEnemy), 0.5f);

	// add hero bullet
	schedule(schedule_selector(PlayScene::addHeroBullet), 0.2f);

	// is collided
	schedule(schedule_selector(PlayScene::collide), 0.2f);

	// add support 
	schedule(schedule_selector(PlayScene::addSupport), 2.0f);

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

void PlayScene::addEnemy(float dt) {
	int index = CCRANDOM_0_1() * 10;
	index = index > 6 ? 2 : 1;
	auto enemy = EnemyBase::create();
	enemy->initEnemy(index);
	addChild(enemy);
	ManagerBase::getInstance()->addEnemy(enemy);
}

void PlayScene::addHeroBullet(float dt)
{
	BulletBase* bullet = BulletBase::create();
	bullet->initWithName("bullet1.png");
	addChild(bullet);
	ManagerBase::getInstance()->addBullet(bullet);

	bullet->setPosition(Vec2(hero->getPositionX(), hero->getPositionY() + hero->getContentSize().height));
}

void PlayScene::collide(float dt)
{
	// enemies and bullets
	auto enemies = ManagerBase::getInstance()->getEnemies();
	auto bullets = ManagerBase::getInstance()->getBullets();
	for (int i = enemies->size() - 1; i >= 0; i--) {
		auto enemy = enemies->at(i);
		if (enemy->getHp() <= 0) { continue; }
		for (int j = 0; j < bullets->size(); j++) {
			auto bullet = bullets->at(j);
			if (enemy->getBoundingBox().containsPoint(bullet->getPosition())) {
				enemy->setHp(enemy->getHp() - 1);
				if (enemy->getHp() <= 0) {
					enemy->death();
				}
				bullet->removeFromParentAndCleanup(true);
				ManagerBase::getInstance()->removeBullet(bullet);
			}
		}
	}

	// hero and enemies
	for (int i = enemies->size() - 1; i >= 0; i--) {
		auto enemy = enemies->at(i);
		if (enemy->getHp() <= 0) { continue; }
		if (hero->getBoundingBox().containsPoint(enemy->getPosition())) {
			enemy->setHp(enemy->getHp() - 1);
			if (enemy->getHp() <= 0) {
				enemy->death();
			}
			heroDied();
		}
	}

	// hero and support
	if (support != nullptr) {
		if (hero->getBoundingBox().containsPoint(support->getPosition())) {
			changeBullet();
		}
	}
}

void PlayScene::heroDied()
{
	unschedule(schedule_selector(PlayScene::addHeroBullet));
	unschedule(schedule_selector(PlayScene::collide));

	Animation* animation = Animation::create();
	char str[20] = { 0 };
	for (int i = 1; i <= 4; i++) {
		sprintf(str, "plane/b%d.png", i);
		animation->addSpriteFrameWithFileName(str);
	}
	animation->setDelayPerUnit(0.3f);
	animation->setLoops(1);
	hero->runAction(Sequence::create(Animate::create(animation), 
		CallFunc::create(CC_CALLBACK_0(PlayScene::heroDiedActionDown, this)), NULL));
}

void PlayScene::heroDiedActionDown()
{
	unschedule(schedule_selector(PlayScene::addEnemy));
}

void PlayScene::addSupport(float dt)
{
	support = Support::create();
	support->initWithIndex(CCRANDOM_0_1() * 2 + 1);
	addChild(support);
}

void PlayScene::changeBullet() {
	unschedule(schedule_selector(PlayScene::addHeroBullet));
	schedule(schedule_selector(PlayScene::addSupportedBullet), 0.2, 50, 0);
	schedule(schedule_selector(PlayScene::addHeroBullet), 0.2f, CC_REPEAT_FOREVER, 10);
}

void PlayScene::addSupportedBullet(float dt) {
	BulletBase* bullet = BulletBase::create();
	int index = support->getIndex()==2?2:1;
	bullet->initWithName(StringUtils::format("plane/bullet_suspand%d.png", index).c_str());
	addChild(bullet);
	ManagerBase::getInstance()->addBullet(bullet);

	bullet->setPosition(Vec2(hero->getPositionX(), hero->getPositionY() + hero->getContentSize().height));
}

void PlayScene::update(float dt) {
	bg1->setPositionY(bg1->getPositionY() - 5);
	bg2->setPositionY(bg2->getPositionY() - 5);

	if (bg1->getPositionY() < -visibleSize.height / 2) {
		bg1->setPositionY(visibleSize.height / 2 + visibleSize.height);
	}

	if (bg2->getPositionY() < -visibleSize.height / 2) {
		bg2->setPositionY(visibleSize.height / 2 + visibleSize.height);
	}
}