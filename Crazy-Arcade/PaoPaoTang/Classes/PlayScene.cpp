#include "PlayScene.h"
#include "MenuSelectHandler.h"
#include "Animation.h"

void CPlayScene::onEnterScene()
{
	mRootLayer->setAnchorPoint(CCPointZero);
	mRootLayer->setScale(0.75);
	CCSprite* pBG = CCSprite::create("Pic/BG.png");
	pBG->setAnchorPoint(CCPointZero);
	mRootLayer->addChild(pBG);

	CCLabelTTF* back_label = CCLabelTTF::create(CStringTableMgr::getString("main_menu"),"Arial",24);
	CCMenuItemLabel * back_labelItem = CCMenuItemLabel::create(back_label,CMenuSelectHandler::sharedHandler(),menu_selector(CMenuSelectHandler::onMenu_Back2Menu));
	back_labelItem->setPosition(ccp(715,25));
	CCMenu* pMenu = CCMenu::create(back_labelItem,NULL);
	pMenu->setPosition(CCPointZero);
	mRootLayer->addChild(pMenu,1);
}

void CPlayScene::onExitScene()
{
	mRootLayer->removeAllChildrenWithCleanup(true);
}
