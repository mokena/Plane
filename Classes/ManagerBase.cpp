#include "ManagerBase.h"

ManagerBase* ManagerBase::instance = nullptr;

ManagerBase::ManagerBase()
{
}

ManagerBase::~ManagerBase()
{
}

ManagerBase * ManagerBase::getInstance()
{
	if (instance == nullptr) {
		instance = new ManagerBase();
	}
	return instance;
}

void ManagerBase::deleteInstance()
{
	delete instance;
	instance = nullptr;
}

Vector<BulletBase*>* ManagerBase::getBullets()
{
	return &bullets;
}

Vector<EnemyBase*>* ManagerBase::getEnemies()
{
	return &enemies;
}

void ManagerBase::addBullet(BulletBase * bt)
{
	bullets.pushBack(bt);
}

void ManagerBase::removeBullet(BulletBase * bt)
{
	bullets.eraseObject(bt);
}

void ManagerBase::addEnemy(EnemyBase * enemy)
{
	enemies.pushBack(enemy);
}

void ManagerBase::removeEnemy(EnemyBase * enemy)
{
	enemies.eraseObject(enemy);
}
