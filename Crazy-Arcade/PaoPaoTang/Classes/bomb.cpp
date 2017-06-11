/******************************/
/*文件说明：泡泡类的定义
*作者：陈乾
*日期：2017-6-10
*/
/******************************/
#include "bomb.h"


using namespace cocos2d;

CBomb::CBomb(cocos2d::CCPoint pos, CMap * layer,CPlayer* hero):
		m_settedPos(pos),
		m_pHero(hero),
		m_sprite(NULL),
		m_ani(NULL),
		m_act(NULL),
		m_pCurMap(layer)
	{
		m_sprite = CCSprite::create();
		m_sprite->setPosition(toTiledPos(pos));

		CCPoint tilpos = m_pCurMap->tilePosFromLocation(pos);
		m_pCurMap->setBombBlock(tilpos.x, tilpos.y, true);

		m_pCurMap->addChild(m_sprite, 2);
		m_ani = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("Pic/Popo.png0"));
		m_sprite->runAction(m_ani);
		CCNode::onEnter();
		scheduleOnce(schedule_selector(CBomb::explode), 3.0);
	}

CBomb* CBomb::create(CCPoint pos, CMap* layer,CPlayer* hero)
{
	CBomb *bomb = new CBomb(pos,layer,hero);   
	bomb->autorelease();
	return bomb;
}


void CBomb::erase()
{
	m_sprite->stopAllActions();
	m_pCurMap->removeChild(m_sprite,1);
	m_pCurMap->removeChild(up, 1);
	m_pCurMap->removeChild(down, 1);
	m_pCurMap->removeChild(left, 1);
	m_pCurMap->removeChild(right, 1);

	CCPoint pos = m_pCurMap->tilePosFromLocation(m_settedPos);
	m_pCurMap->setBombBlock(pos.x, pos.y, false);
}

void CBomb::explode(float dt)
{
	int blockedScale = expoldeBlock();

	CCPoint pos = m_sprite->getPosition();
	up = CCSprite::create("Pic/paopaoup.png");
	down = CCSprite::create("Pic/paopaodown.png");
	left = CCSprite::create("Pic/paopaoleft.png");
	right = CCSprite::create("Pic/paopaoright.png");

	

	up->setAnchorPoint(ccp(0.5, 0));
	down->setAnchorPoint(ccp(0.5, 1.0));
	left->setAnchorPoint(ccp(1.0, 0.5));
	right->setAnchorPoint(ccp(0, 0.5));
	up->setScaleY(0.1);
	down->setScaleY(0.1);
	left->setScaleX(0.1);
	right->setScaleX(0.1);

	CCScaleBy *_up = CCScaleBy::create(0.2, 1.0, blockedScale/1000*10);
	CCScaleBy *_down = CCScaleBy::create(0.2, 1.0, (blockedScale%1000)/100*10);
	CCScaleBy *_left = CCScaleBy::create(0.2, (blockedScale % 100) / 10*10, 1.0);
	CCScaleBy *_right = CCScaleBy::create(0.2, (blockedScale % 10) / 1*10, 1.0);
	
	CCCallFunc* callFun = CCCallFunc::create(this, callfunc_selector(CBomb::erase));
	CCAction *callFun_right = CCSequence::create(_right, callFun, NULL);
	
	up->setPosition(ccp(pos.x, pos.y + 20));
	down->setPosition(ccp(pos.x, pos.y - 20));
	left->setPosition(ccp(pos.x - 20, pos.y));
	right->setPosition(ccp(pos.x + 20, pos.y));
	m_pCurMap->addChild(up,2);
	m_pCurMap->addChild(down,2);
	m_pCurMap->addChild(left,2);
	m_pCurMap->addChild(right,2);

	CCAnimationCache::sharedAnimationCache()->animationByName("Pic/paopao.png0")->setDelayPerUnit(0.2 / 4.0);
	m_sprite->runAction(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("Pic/paopao.png0")));
	up->runAction(_up);
	down->runAction(_down);
	left->runAction(_left);
	right->runAction(callFun_right);

	
}

int CBomb::expoldeBlock()
{
	CCSize tiledSize = m_pHero->m_pCurrentMap->getTileSize();
	CCPoint pos =m_sprite->getPosition();
	int blockedScale = 0;
	CCPoint tp1 = pos;
	CCPoint tp2 = pos;
	CCPoint tp3 = pos;
	CCPoint tp4 = pos;

	for (int i = 0; i < m_pHero->m_iBombScale; i++)
	{
		
		tp1.y += tiledSize.height;
		if (isInBorder(tp1) == false )
		{
			blockedScale += 1000 * i;
			break;
		}
		else if(m_pCurMap->isTilePosBlocked(tp1) == true)
		{
			deleteTile(tp1);
			blockedScale += 1000 * i;
			break;

		}
		else if(i == m_pHero->m_iBombScale - 1)
		{
			blockedScale += 1000 * (i+1) ;
			break;
		}
		
	}
	for (int i = 0; i < m_pHero->m_iBombScale; i++)
	{
		
		tp2.y -= tiledSize.height;
		if (isInBorder(tp2) == false )
		{
			blockedScale += 100 * i;
			break;
		}
		else if (m_pCurMap->isTilePosBlocked(tp2) == true)
		{
			deleteTile(tp2);
			blockedScale += 100 * i;
			break;
		}
		else if (i == m_pHero->m_iBombScale - 1)
		{
			blockedScale += 100 * (i + 1);
			break;
		}
	}
	for (int i = 0; i < m_pHero->m_iBombScale; i++)
	{
		
		tp3.x -= tiledSize.height;
		if (isInBorder(tp3) == false  )
		{
			blockedScale += 10 * i;
			break;
		}
		else if (m_pCurMap->isTilePosBlocked(tp3) == true)
		{
			deleteTile(tp3);
			blockedScale += 10 * i;
			break;
		}
		else if (i == m_pHero->m_iBombScale - 1)
		{
			blockedScale += 10 * (i + 1);
			break;
		}
	}
	for (int i = 0; i < m_pHero->m_iBombScale; i++)
	{
		
		tp4.x += tiledSize.height;
		if (isInBorder(tp4) == false  )
		{
			blockedScale += 1 * i;
			break;
		}
		else if (m_pCurMap->isTilePosBlocked(tp4) == true)
		{
			deleteTile(tp4);
			blockedScale += 1 * i;
			break;
		}
		else if (i == m_pHero->m_iBombScale - 1)
		{
			blockedScale += 1 * (i + 1);
			break;
		}
	}

	return blockedScale;
}

CBomb::~CBomb()
{
	
}

bool CBomb::isInBorder(CCPoint pos)
{
	if (pos.x<CONTENT_WIDTH  && pos.y<CONTENT_HEIGHT  && pos.x>0 && pos.y>0)
		return true;
	else
		return false;
}

void CBomb::deleteTile(cocos2d::CCPoint pos)
{
	//判断当前块是否为碰撞块  
	CCPoint tilpos = m_pCurMap->tilePosFromLocation(pos);                //将带入的坐标转为块坐标  
	CCTMXLayer *clayer = m_pCurMap->layerNamed("collision");      //通过层名字获得该层对象 


	int tileGID = clayer->tileGIDAt(tilpos);             //获得该块的GID标识别  
	if (tileGID != 0)
	{
		CCDictionary* properties = m_pCurMap->propertiesForGID(tileGID);
		if (strcmp(properties->valueForKey("destroyable")->getCString(), "true") == 0)
		{
			clayer->removeTileAt(tilpos);
		}
	}
	
	return;
}

CCPoint CBomb::toTiledPos(CCPoint &pos)
{
	CCSize tiledSize = m_pCurMap->getTileSize();
	CCSize mapSize = m_pCurMap->getMapSize();

	pos.x = (int)(pos.x / tiledSize.width)*tiledSize.width + tiledSize.width / 2;
	pos.y = (int)(pos.y / tiledSize.height)*tiledSize.height + tiledSize.height / 2;
	
	return pos;
}
