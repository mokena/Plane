#include "Support.h"

Support::Support()
{
}

Support::~Support()
{
}

bool Support::init()
{
	if (Sprite::init() == false) {
		return false;
	}
	return true;
}

void Support::initWithIndex(int index)
{
	char file[50] = {0}; 
	sprintf(file, "plane\bullet_suspand%d.png", index);

	initWithFile(file);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto contentSize = getContentSize();

	// position
	auto posx = CCRANDOM_0_1()*(visibleSize.width - contentSize.width) + contentSize.width / 2;
	setPosition(ccp(posx, visibleSize.height));

	ccBezierConfig bConfig;
	auto px = CCRANDOM_0_1()*(visibleSize.width - contentSize.width) + contentSize.width / 2;
	auto py = CCRANDOM_0_1()*(visibleSize.height - contentSize.height) + contentSize.height / 2;
	bConfig.controlPoint_1 = ccp(px, py);

	px = CCRANDOM_0_1()*(visibleSize.width - contentSize.width) + contentSize.width / 2;
	py = CCRANDOM_0_1()*(visibleSize.height - contentSize.height) + contentSize.height / 2;
	bConfig.controlPoint_2 = ccp(px, py);

	px = CCRANDOM_0_1()*(visibleSize.width - contentSize.width) + contentSize.width / 2;
	bConfig.endPosition = ccp(px, -contentSize.height);

	auto bezier = CCBezierTo::create(2.0, bConfig);

	this->runAction(Sequence::create(bezier, RemoveSelf::create(), NULL));
}
