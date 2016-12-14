#pragma once

#include "BulletBase.h"
#include "EnemyBase.h"

USING_NS_CC;

class ManagerBase {

protected:
	ManagerBase();
	virtual ~ManagerBase();

	static ManagerBase* instance;

public:
	static ManagerBase* getInstance();
	static void deleteInstance();

};
