#include "EnemyBase.h"
#include "ManagerBase.h"

void EnemyBase::initEnemy(int index) {
	hp = index; // user index as hp

	auto str = StringUtils::format("plane/enemy%d.png", index);
	this->initWithFile(str.c_str());

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto pos = ccp(CCRANDOM_0_1()*(visibleSize.width - this->getContentSize().width) + this->getContentSize().width / 2, visibleSize.height);
	setPosition(pos);
}

void EnemyBase::death() {
	Animation* animation = Animation::create();
	char str[50] = {0};
	for (int i = 1; i <= 4; i++) {
		sprintf(str, "plane/enemy1_down%d.png", i);
		animation->addSpriteFrameWithFileName(str);
	}
	animation->setDelayPerUnit(0.3f);
	Animate* anim = Animate::create(animation);
	this->runAction(Sequence::create(anim, RemoveSelf::create(), 
		CallFunc::create(CC_CALLBACK_0(EnemyBase::removeFromList, this)), NULL));
}

void EnemyBase::removeFromList()
{
	ManagerBase::getInstance()->removeEnemy(this);
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
		ManagerBase::getInstance()->removeEnemy(this);
	}
}

int EnemyBase::getHp()
{
	return hp;
}

void EnemyBase::setHp(int h)
{
	hp = h;
}
