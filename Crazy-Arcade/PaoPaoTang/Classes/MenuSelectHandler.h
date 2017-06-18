#ifndef _MENU_SELECT_HANDLER_H_
#define _MENU_SELECT_HANDLER_H_
#include "cocos2d.h"
#include "GameLogic.h"
#include "BaseDef.h"
using namespace cocos2d;

extern int MAPTAG;
class CMenuSelectHandler:public CCObject
{
private:
	CMenuSelectHandler(){}
public:
	static CMenuSelectHandler* sharedHandler()
	{
		static CMenuSelectHandler* instance = NULL;
		if(instance==NULL)
			instance = new CMenuSelectHandler();
		return instance;
	}
public:
	void onMenu_Play(CCObject* pSender)
	{
		GameLogic::sharedGameLogic().handleEvent(ESSE_Play);
	}
	void onMenu_Exit(CCObject* pSender)
	{
		GameLogic::sharedGameLogic().handleEvent(ESSE_Exit);
	}
	void onMenu_Back2Menu(CCObject* pSender)
	{
		GameLogic::sharedGameLogic().handleEvent(ESSE_Back2Menu);
	}
	void onMenu_Map1(CCObject* pSender)
	{
		MAPTAG = 1;
		GameLogic::sharedGameLogic().handleEvent(ESSE_Map);
	}
	void onMenu_Map2(CCObject* pSender)
	{
		MAPTAG = 2;
		GameLogic::sharedGameLogic().handleEvent(ESSE_Map);
	}
};
#endif