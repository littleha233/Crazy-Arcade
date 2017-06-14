#ifndef _ITEM_H_
#define _ITEM_H_

#include "cocos2d.h"
#include "player.h"
#include "map.h"

class CMap;
class CItem:public cocos2d::CCNode
{
public:
	CItem(CMap* map,cocos2d::CCPoint tPos);
	static CItem* create(cocos2d::CCPoint,CMap*);

private:
	cocos2d::CCSprite* m_pSprite;
	CMap* m_pCurMap;
	cocos2d::CCAnimate* m_pAnimate;
	cocos2d::CCPoint m_settledPos;
	int m_iItemID;
};

#endif // !_ITEM_H_
