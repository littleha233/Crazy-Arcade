#include "cocos2d.h"
#include "BeginScene.h"
#include "BaseDef.h"
#include "MenuSelectHandler.h"
#include "Animation.h"
void CBeginScene::onEnterScene()
{
	CCSprite* backGround = CCSprite::create("Pic/begin1.jpg");
	backGround->setPosition(ccp(FRAME_WIDTH/2,FRAME_HEIGHT/2));
	mRootLayer->addChild(backGround);

	CCLabelTTF* title_label = CCLabelTTF::create(CStringTableMgr::getString("title"),"Arial",60);
	title_label->setColor(ccc3(0,0,0));
	CCMenuItemLabel* title_labelItem = CCMenuItemLabel::create(title_label);
	title_labelItem->setPosition(FRAME_WIDTH/2,FRAME_HEIGHT/2+150);

	CCLabelTTF* play_label = CCLabelTTF::create(CStringTableMgr::getString("play"),"Arial",24);
	play_label->setColor(ccc3(238,130,238));
	CCMenuItemLabel* play_labelItem = CCMenuItemLabel::create(play_label,CMenuSelectHandler::sharedHandler(),menu_selector(CMenuSelectHandler::onMenu_Play));
	play_labelItem->setPosition(FRAME_WIDTH/2,FRAME_HEIGHT/2);

	CCLabelTTF* exit_label = CCLabelTTF::create(CStringTableMgr::getString("exit"),"Arial",24);
	exit_label->setColor(ccc3(238,130,238));
	CCMenuItemLabel* exit_labelItem = CCMenuItemLabel::create(exit_label,CMenuSelectHandler::sharedHandler(),menu_selector(CMenuSelectHandler::onMenu_Exit));
	exit_labelItem->setPosition(FRAME_WIDTH/2,FRAME_HEIGHT/2-50);

	CCMenu* pMenu = CCMenu::create(play_labelItem,exit_labelItem,title_labelItem,NULL);
	pMenu->setPosition(CCPointZero);
	mRootLayer->addChild(pMenu,1);

}

void CBeginScene::onExitScene()
{
	mRootLayer->removeAllChildrenWithCleanup(true);
}