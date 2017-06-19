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
	/*CCSprite* pBG = CCSprite::create("Pic/BG.png");
	pBG->setAnchorPoint(CCPointZero);
	mRootLayer->addChild(pBG,2);*/
	/**************动画小测试*****************/

	//CCAnimation* animation=CCAnimationCache::sharedAnimationCache()->animationByName("Pic/Role1.png0");//提取动画
	//CCAnimate* animate=CCAnimate::create(animation);//创建动作
	//CCSprite* sp=CCSprite::create();
	//sp->setPosition(ccp(FRAME_WIDTH/2,FRAME_HEIGHT*0.7));
	//mRootLayer->addChild(sp);
	//sp->runAction(animate);
	if (MAPTAG == 1)m_pMap = CMap::initTileMap("amap1.tmx",this);
	if (MAPTAG == 2)m_pMap = CMap::initTileMap("amap2.tmx", this);

	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Snd/bg/Play.mp3", true);

	/*amap->addChild(hero.getSprite(),3);*/
	/**************动画小测试*****************/

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