#ifndef _MENU_SELECT_HANDLER_H_
#define _MENU_SELECT_HANDLER_H_
#include "cocos2d.h"
#include "GameLogic.h"
#include "BaseDef.h"
using namespace cocos2d;
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
};
#endif