#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Support : public Sprite {
protected:
	int index;

public:
	Support();
	virtual ~Support();

	virtual bool init();

	void initWithIndex(int index);

	int getIndex() { return index; };

	CREATE_FUNC(Support);
};
