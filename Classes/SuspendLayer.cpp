#include "SuspendLayer.h"

SuspendLayer::SuspendLayer() {

}

SuspendLayer::~SuspendLayer() {

}

bool SuspendLayer::init()
{
	if (Layer::init() == false) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto suspendImgPath = FileUtils::getInstance()->getWritablePath() + "suspend.png";
	Sprite* suspendImg = Sprite::create(suspendImgPath);
	suspendImg->setAnchorPoint(Vec2(0, 0));
	addChild(suspendImg);

	auto *chnStr = Dictionary::createWithContentsOfFile("res.xml");
	const char* resumeStr = ((String*)chnStr->objectForKey("resume"))->getCString();
	Label* resumeLbl = Label::create();
	resumeLbl->setString(resumeStr);
	resumeLbl->setSystemFontSize(30);
	MenuItemLabel* menuLbl = MenuItemLabel::create(resumeLbl, CC_CALLBACK_1(SuspendLayer::resume, this));

	Menu* menu = Menu::createWithItem(menuLbl);
	menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	addChild(menu);

	return true;
}

void SuspendLayer::resume(Ref* ref) {
	Director::getInstance()->popScene();
}