#pragma once
#include "cocos2d.h"

USING_NS_CC;

class PlayScene : public Layer {
protected:
	Sprite* bg1, *bg2;
	Size visibleSize;

public:
	static Scene* createScene();

	virtual bool init();

	void update(float dt);

	CREATE_FUNC(PlayScene);
};
