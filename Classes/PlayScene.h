#pragma once
#include "cocos2d.h"
#include "EnemyBase.h"
#include "BulletBase.h"
#include "ManagerBase.h"
#include "Support.h"

USING_NS_CC;

class PlayScene : public Layer {
protected:
	Sprite* bg1, *bg2;
	Size visibleSize;
	Sprite* hero;
	Support* support;

public:
	static Scene* createScene();

	virtual bool init();
	void initHeroPlane(int index);
	void addEnemy(float dt);
	void addHeroBullet(float dt);
	void collide(float dt);
	void heroDied();
	void heroDiedActionDown();
	void addSupport(float dt);
	void changeBullet();
	void addSupportedBullet(float dt);
	bool rectCross(Rect r1, Rect r2);
	
	void update(float dt);

	CREATE_FUNC(PlayScene);
};
