#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PlayScene.h"

USING_NS_CC;

class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void startMenuHandler(Ref* ref);
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
};

#endif // __HELLOWORLD_SCENE_H__
