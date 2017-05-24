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
	void beginScene_PlayItem(CCObject* sender)
	{
		GameLogic::sharedGameLogic().handleEvent(EBSE_Play);
	}
};
#endif