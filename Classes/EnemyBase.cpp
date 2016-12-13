#include "EnemyBase.h"

void EnemyBase::initEnemy(int index) {
	auto str = StringUtils::format("plane/enemy%d.png", index);
	this->initWithFile(str.c_str());

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto pos = ccp(CCRANDOM_0_1()*(visibleSize.width - this->getContentSize().width) + this->getContentSize().width / 2, visibleSize.height);
	setPosition(pos);
}

void EnemyBase::death() {

}

void EnemyBase::onEnter() {
	Sprite::onEnter();
	scheduleUpdate();
}

void EnemyBase::onExit() {
	Sprite::onExit();
	unscheduleUpdate();
}

void EnemyBase::update(float dt) {
	Sprite::update(dt);
	int y = getPositionY() - 5;
	setPositionY(y);
	if (y < 0) {
		removeFromParentAndCleanup(true);
	}
}