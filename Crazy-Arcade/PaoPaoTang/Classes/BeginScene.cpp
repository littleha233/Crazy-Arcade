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
/**************动画小测试*****************/
	loadAni();//加载动画
	
	CCAnimation* animation=CCAnimationCache::sharedAnimationCache()->animationByName("morePic/custom_bubble_98.png0");//提取动画
	CCAnimate* animate=CCAnimate::create(animation);//创建动作
	CCSprite* sp=CCSprite::create();
	sp->setPosition(ccp(FRAME_WIDTH/2,FRAME_HEIGHT*0.7));
	mRootLayer->addChild(sp);
	sp->runAction(animate);
/**************动画小测试*****************/
}

void CBeginScene::onExitScene()
{
	mRootLayer->removeAllChildrenWithCleanup(true);
}