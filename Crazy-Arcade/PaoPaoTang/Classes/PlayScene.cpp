#include "PlayScene.h"
#include "MenuSelectHandler.h"
#include "Animation.h"
#include "music.h"





CPlayScene::CPlayScene():
m_pMap(NULL)
{
}

void CPlayScene::onEnterScene(int i)
{
	mRootLayer->setAnchorPoint(CCPointZero);

	if (MAPTAG == 1)m_pMap = CMap::initTileMap("amap1.tmx",this);
	if (MAPTAG == 2)m_pMap = CMap::initTileMap("amap2.tmx", this);

	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Snd/bg/Village.mp3", true);


	CCSprite* exit = CCSprite::create("back.png");
	CCMenuItemSprite * back_labelItem = CCMenuItemSprite::create(exit, exit, exit, CMenuSelectHandler::sharedHandler(), menu_selector(CMenuSelectHandler::onMenu_Back2Menu));
	back_labelItem->setPosition(ccp(715,25));
	back_labelItem->setScale(0.4);
	back_labelItem->setScaleX(0.6);
	CCMenu* pMenu = CCMenu::create(back_labelItem,NULL);
	pMenu->setPosition(CCPointZero);
	mRootLayer->addChild(pMenu,1);

	
}

void CPlayScene::onExitScene()
{
	m_pMap->m_pPlayer1->unschedule(schedule_selector(CPlayer::myUpdate, m_pMap->m_pPlayer1));
	m_pMap->m_pPlayer2->unschedule(schedule_selector(CPlayer::myUpdate, m_pMap->m_pPlayer2));
	m_pMap->m_pPlayer1->s_playerNum = 0;
	mRootLayer->removeAllChildrenWithCleanup(true);

	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void CPlayScene::handleInput(EControlType eCtrlType, EPressState ePrsState)
{
	
	if (m_pMap != NULL)m_pMap->handleInput(eCtrlType, ePrsState);
}