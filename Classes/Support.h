#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Support : public Sprite {

public:
	Support();
	virtual ~Support();

	virtual bool init();

	void initWithIndex(int index);

	CREATE_FUNC(Support);
};
