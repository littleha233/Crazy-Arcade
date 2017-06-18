#include "MapScene.h"
#include "BaseDef.h"
#include "MenuSelectHandler.h"

void CMapScene::onEnterScene(int i)
{
	CCLabelTTF* title_label = CCLabelTTF::create(CStringTableMgr::getString("map"), "Arial", 36);
	title_label->setColor(ccc3(0, 255, 0));
	CCMenuItemLabel* title_labelItem = CCMenuItemLabel::create(title_label);
	title_labelItem->setPosition(FRAME_WIDTH / 2, FRAME_HEIGHT / 2 + 200);

	CCSprite* map1 = CCSprite::create("map1.png");
	CCMenuItemSprite* map1_item = CCMenuItemSprite::create(map1, map1, map1, CMenuSelectHandler::sharedHandler(), menu_selector(CMenuSelectHandler::onMenu_Map1));
	map1_item->setColor(ccc3(255, 255, 255));
	map1_item->setPosition(FRAME_WIDTH / 2 - 150, FRAME_HEIGHT / 2);

	CCSprite* map2 = CCSprite::create("map2.png");
	CCMenuItemSprite* map2_item = CCMenuItemSprite::create(map2, map2, map2, CMenuSelectHandler::sharedHandler(), menu_selector(CMenuSelectHandler::onMenu_Map2));
	map2_item->setColor(ccc3(255, 255, 255));
	map2_item->setPosition(FRAME_WIDTH / 2 + 150, FRAME_HEIGHT / 2);

	CCLabelTTF* back_label = CCLabelTTF::create(CStringTableMgr::getString("main_menu"), "Arial", 36);
	back_label->setColor(ccc3(0, 255, 0));
	CCMenuItemLabel * back_labelItem = CCMenuItemLabel::create(back_label, CMenuSelectHandler::sharedHandler(), menu_selector(CMenuSelectHandler::onMenu_Back2Menu));
	back_labelItem->setPosition(FRAME_WIDTH / 2, FRAME_HEIGHT / 2 - 200);

	CCMenu* pMenu = CCMenu::create(title_labelItem , back_labelItem ,map1_item ,map2_item , NULL);
	pMenu->setPosition(CCPointZero);
	mRootLayer->addChild(pMenu);
}

void CMapScene::onExitScene()
{
	mRootLayer->removeAllChildrenWithCleanup(true);
}
