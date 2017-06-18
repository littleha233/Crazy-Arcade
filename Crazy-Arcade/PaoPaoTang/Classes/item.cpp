#include "item.h"
#include "ctime"

using namespace cocos2d;

CItem::CItem(CMap * map,CCPoint tPos):
	m_settledPos(tPos),
	m_pCurMap(map),
	m_pAnimate(NULL)
{
	


	m_pSprite = CCSprite::create();
	srand(((int)&m_pSprite)+time(NULL));
	m_iItemID = rand() % 8;


	if(m_iItemID==1)m_pAnimate=CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("Pic/Gift1.png0"));
	else if (m_iItemID == 2)m_pAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("Pic/Gift2.png0"));
	else if (m_iItemID == 3)m_pAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("Pic/Gift3.png0"));
	
	
	
		if (m_pAnimate != NULL)
	{
		CCPoint tilpos = m_pCurMap->tilePosFromLocation(m_settledPos);
		m_pCurMap->itemPos[(int)tilpos.x][(int)tilpos.y] = m_iItemID;
		m_pCurMap->itemPointerPos[(int)tilpos.x][(int)tilpos.y] = m_pSprite;
		m_pSprite->runAction(m_pAnimate);
		m_pSprite->setPosition(tPos);
		m_pCurMap->addChild(m_pSprite,2);
	}
	

	
}

CItem * CItem::create(CCPoint tPos,CMap* map)
{
	CItem *item = new CItem(map,tPos);
	item->autorelease();
	

	return item;
}
