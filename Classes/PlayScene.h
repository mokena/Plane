#pragma once
#include "cocos2d.h"
#include "EnemyBase.h"
#include "BulletBase.h"
#include "ManagerBase.h"
#include "Support.h"
#include "SuspendLayer.h"

USING_NS_CC;

class PlayScene : public Layer {
protected:
	Sprite* bg1, *bg2;
	Size visibleSize;
	Sprite* hero;
	Label* bestScoreLabel;
	Label* scoreLabel;
	Support* support;
	int score;
	Dictionary *chnStr;

	const static String SCORE;
	const static String BEST_SCORE;

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

	void suspend(Ref* ref);
	void capture(bool succeed, const std::string& outputFile);
	
	void update(float dt);

	CREATE_FUNC(PlayScene);
};
