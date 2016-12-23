#pragma once

#include "cocos2d.h"
#include "BulletBase.h"
#include "EnemyBase.h"

USING_NS_CC;

class ManagerBase {

protected:
	ManagerBase();
	virtual ~ManagerBase();

	static ManagerBase* instance;

	Vector<BulletBase*> bullets;
	Vector<EnemyBase*> enemies;

public:
	static ManagerBase* getInstance();
	static void deleteInstance();

	Vector<BulletBase*>* getBullets();
	Vector<EnemyBase*>* getEnemies();

	void addBullet(BulletBase* bt);
	void removeBullet(BulletBase* bt);

	void addEnemy(EnemyBase* enemy);
	void removeEnemy(EnemyBase* enemy);

};
