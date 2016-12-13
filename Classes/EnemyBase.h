#pragma once
#include "cocos2d.h"

USING_NS_CC;

class EnemyBase : public Sprite {
protected:
	int index;

public:

	virtual void onEnter();
	virtual void onExit();
	
	void initEnemy(int index);
	void death();
	void update(float dt);
	CREATE_FUNC(EnemyBase);
};
