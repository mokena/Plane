#pragma once

#include "cocos2d.h"

USING_NS_CC;

class SuspendLayer : public Layer {
public:
	SuspendLayer();
	virtual ~SuspendLayer();

	virtual bool init();

	void resume(Ref* ref);

	CREATE_FUNC(SuspendLayer);

};
