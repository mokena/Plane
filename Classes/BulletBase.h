#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BulletBase : public Sprite {

public:
	virtual void onEnter();
	virtual void onExit();

	void initWithName(std::string name);

	virtual void update(float dt);

	CREATE_FUNC(BulletBase);
};
