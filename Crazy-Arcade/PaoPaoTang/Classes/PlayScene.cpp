#include "PlayScene.h"
#include "MenuSelectHandler.h"
#include "Animation.h"




CPlayScene::CPlayScene():
	hero()
{
}

void CPlayScene::onEnterScene()
{
	mRootLayer->setAnchorPoint(CCPointZero);
	CCSprite* pBG = CCSprite::create("Pic/BG.png");
	pBG->setAnchorPoint(CCPointZero);
	mRootLayer->addChild(pBG);
	/**************����С����*****************/

	//CCAnimation* animation=CCAnimationCache::sharedAnimationCache()->animationByName("Pic/Role1.png0");//��ȡ����
	//CCAnimate* animate=CCAnimate::create(animation);//��������
	//CCSprite* sp=CCSprite::create();
	//sp->setPosition(ccp(FRAME_WIDTH/2,FRAME_HEIGHT*0.7));
	//mRootLayer->addChild(sp);
	//sp->runAction(animate);
	CMap* amap = CMap::initTileMap("amap.tmx");
	hero.setMap(amap);
	mRootLayer->addChild(amap,1);
	amap->addChild(hero.getSprite(), 2);
	/**************����С����*****************/

	CCLabelTTF* back_label = CCLabelTTF::create(CStringTableMgr::getString("main_menu"),"Arial",24);
	back_label->setColor(ccc3(0, 255, 0));
	CCMenuItemLabel * back_labelItem = CCMenuItemLabel::create(back_label,CMenuSelectHandler::sharedHandler(),menu_selector(CMenuSelectHandler::onMenu_Back2Menu));
	back_labelItem->setPosition(ccp(755,20));
	CCMenu* pMenu = CCMenu::create(back_labelItem,NULL);
	pMenu->setPosition(CCPointZero);
	mRootLayer->addChild(pMenu,1);

	
}

void CPlayScene::onExitScene()
{
	mRootLayer->removeAllChildrenWithCleanup(true);
}

void CPlayScene::handleInput(EControlType eCtrlType, EPressState ePrsState)
{
	hero.handleInput(eCtrlType, ePrsState);
}