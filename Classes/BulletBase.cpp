#include "BulletBase.h"
#include "ManagerBase.h"

void BulletBase::onEnter()
{
	Sprite::onEnter();
	scheduleUpdate();
}

void BulletBase::onExit()
{
	Sprite::onExit();
	unscheduleUpdate();
}

void BulletBase::initWithName(std::string name)
{
	std::string str = StringUtils::format("plane/%s", name.c_str());
	initWithFile(str.c_str());
}

void BulletBase::update(float dt)
{
	Sprite::update(dt);
	int posy = getPositionY() + 5;
	setPositionY(posy);

	if (posy > Director::getInstance()->getVisibleSize().height + getContentSize().height / 2) {
		removeFromParentAndCleanup(true);
		ManagerBase::getInstance()->removeBullet(this);
	}
}
