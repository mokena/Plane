#pragma once
#include "cocos2d.h"

USING_NS_CC;

class EnemyBase : public Sprite {
protected:
	int index; // indicate which plane used by enemy
	int hp; // the hp of enemy
public:

	virtual void onEnter();
	virtual void onExit();
	
	void initEnemy(int index);
	void death();
	void removeFromList();
	void update(float dt);

	int getHp();
	void setHp(int h);

	CREATE_FUNC(EnemyBase);
};
