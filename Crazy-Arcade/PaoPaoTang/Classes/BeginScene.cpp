#include "cocos2d.h"
#include "BeginScene.h"
#include "BaseDef.h"
#include "MenuSelectHandler.h"
#include "Animation.h"
#include "music.h"

void CBeginScene::onEnterScene(int i)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Snd/bg/Prepare.mp3",true);

	CCSprite* backGround = CCSprite::create("Pic/timg.jpg");
	backGround->setScale(0.78);
	backGround->setPosition(ccp(FRAME_WIDTH/2,FRAME_HEIGHT/2));
	mRootLayer->addChild(backGround);

	CCSprite* play = CCSprite::create("play.png");
	CCMenuItemSprite* play_labelItem = CCMenuItemSprite::create(play, play, play,CMenuSelectHandler::sharedHandler(),menu_selector(CMenuSelectHandler::onMenu_Play));
	play_labelItem->setScale(0.15);
	play_labelItem->setPosition(FRAME_WIDTH / 2, FRAME_HEIGHT / 2 + 80);

	CCSprite* exit = CCSprite::create("exit.png");
	CCMenuItemSprite* exit_labelItem = CCMenuItemSprite::create(exit, exit, exit, CMenuSelectHandler::sharedHandler(), menu_selector(CMenuSelectHandler::onMenu_Exit));
	exit_labelItem->setScale(0.4);
	exit_labelItem->setPosition(FRAME_WIDTH / 2, FRAME_HEIGHT / 2 - 80);

	CCMenu* pMenu = CCMenu::create(play_labelItem,exit_labelItem,NULL);
	pMenu->setPosition(CCPointZero);
	mRootLayer->addChild(pMenu,1);

}

void CBeginScene::onExitScene()
{
	mRootLayer->removeAllChildrenWithCleanup(true);
}