/**********************/
/*
*文件说明：此文件包含游戏中主角对象的定义
*作者：陈乾
*时间：2017-5-29
*/
/**********************/

#include "player.h"
using namespace cocos2d;

int CPlayer::s_playerNum = 0;
CPlayer::CPlayer(CMap* curMap):
	playerID(0),
	m_iMaxBombNum(1),
	m_iSettledBobNum(0),
	m_iBombScale(1),
	m_iSpeed(4),
	m_pHero(NULL),
	m_pAnimate(NULL),
	m_currentState(EPLS_STAND),
	m_moveDirection(ECT_NUM),
	m_pCurrentMap(curMap)
{
	playerID = s_playerNum;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (s_playerNum == 1)
	{
		m_pHero = CCSprite::create(ROLE1, CCRectMake(0, 256 / 4, 288 / 6, 256 / 4));
		m_pHero->setAnchorPoint(ccp(0.5, 0.3));
		m_pHero->setPosition(ccp(100, 540));
	}
	else if (s_playerNum == 2)
	{
		m_pHero = CCSprite::create(ROLE2, CCRectMake(0, 268 / 4, 336 / 6, 268 / 4));
		m_pHero->setAnchorPoint(ccp(0.5, 0.3));
		m_pHero->setPosition(ccp(580, 540));
	}
	m_pHero->retain();
	
	m_pCurrentMap->addChild(m_pHero, 3);
	//设置update监听
	CCNode::onEnter();
	this->schedule(schedule_selector(CPlayer::myUpdate),0.005);

	/******状态表测试******/
	for (int i = 0; i < EPLS_NUM; i++)
		for (int j = 0; j < EPLS_NUM; j++)
			m_rgStateTable[i][j] = 0;

	m_rgStateTable[EPLS_STAND][EPLS_MOVE] = 1;
	m_rgStateTable[EPLS_MOVE][EPLS_STAND] = 1;
	m_rgStateTable[EPLS_PAOPAO][EPLS_MOVE] = 1;
	m_rgStateTable[EPLS_PAOPAO][EPLS_STAND] = 1;
	m_rgStateTable[EPLS_DEAD][EPLS_PAOPAO] = 1;

	
	
}


CPlayer* CPlayer::create(CMap * curMap)
{
	s_playerNum += 1;
	CPlayer* player = new CPlayer(curMap);
	player->autorelease();
	return player;
}

CCSprite * CPlayer::getSprite()
{
	return m_pHero;
}


void CPlayer::move(EControlType eCtrlType)
{
	if (!changeState(EPLS_MOVE))
		return;
	std::string aniName;
	if(playerID==1)aniName = ROLE1;
	else if (playerID == 2)aniName = ROLE2;
	char order = '0' + eCtrlType;
	aniName += order;
	m_pAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(aniName.c_str()));
	m_pHero->runAction(m_pAnimate);

	int dir[EPLS_NUM][2] = { {0,1},{0,-1},{-1,0},{1,0} };
	m_pMoveBy = CCMoveBy::create(m_iSpeed, ccp(dir[eCtrlType][0] * CONTENT_WIDTH, dir[eCtrlType][1] * CONTENT_WIDTH));
	m_pHero->runAction(m_pMoveBy);
	
	/**碰撞测试**/
	m_moveDirection = eCtrlType;
}

void CPlayer::stop(EControlType eCtrlType)
{
	if (!changeState(EPLS_STAND))
		return;

	m_pHero->stopAction(m_pAnimate);
	if(playerID==1)m_pHero->setTextureRect(CCRectMake(0 * 288 / 6, eCtrlType * 256 / 4, 288 / 6, 256 / 4));
	else if(playerID == 2)m_pHero->setTextureRect(CCRectMake(0 * 336 / 6, eCtrlType * 268 / 4, 336 / 6, 268 / 4));
	m_pHero->stopAction(m_pMoveBy);
}

void CPlayer::setBomb()
{
	if (m_iSettledBobNum < m_iMaxBombNum)
	{
		CBomb* bomb = CBomb::create(m_pHero->getPosition(), m_pCurrentMap,this);
		m_iSettledBobNum += 1;
	}
	
}

void CPlayer::trapped()
{
	m_pHero->stopAllActions();
	changeState(EPLS_PAOPAO);
	dead();
}

void CPlayer::dead()
{
	SimpleAudioEngine::sharedEngine()->playEffect("Snd/die.wav");

	CCAnimation* dieAni;
	if (playerID == 1)dieAni = CCAnimationCache::sharedAnimationCache()->animationByName("Pic/Role1Die.png0");
	else if (playerID == 2)dieAni = CCAnimationCache::sharedAnimationCache()->animationByName("Pic/Role2Die.png0");
	dieAni->setLoops(1);
	changeState(EPLS_DEAD);
	m_pHero->runAction(CCAnimate::create(dieAni));
}

void CPlayer::getItem()
{
	SimpleAudioEngine::sharedEngine()->playEffect("Snd/get.wav");
	CCPoint tilpos = m_pCurrentMap->tilePosFromLocation(m_pHero->getPosition());
	int itemID=m_pCurrentMap->itemPos[(int)tilpos.x][(int)tilpos.y];
	if (itemID == 1 && m_iMaxBombNum <= 4)m_iMaxBombNum += 1;
	else if (itemID == 2 && m_iSpeed >= 2.5)m_iSpeed -= 0.3;
	else if (itemID == 3 && m_iBombScale <= 7)m_iBombScale += 2;

	m_pCurrentMap->itemPos[(int)tilpos.x][(int)tilpos.y]=0;
	m_pCurrentMap->removeChild(m_pCurrentMap->itemPointerPos[(int)tilpos.x][(int)tilpos.y], true);
}

void CPlayer::handleInput(EControlType eCtrlType, EPressState ePrsState)
{
	switch (ePrsState)
	{
	case EPS_DOWN:
		handleDown(eCtrlType);
		break;
	case EPS_UP:
		handleUp(eCtrlType);
		break;
	default:
		return;
	}
}

void CPlayer::myUpdate(float dt)
{
	CCPoint pos = m_pCurrentMap->tilePosFromLocation(m_pHero->getPosition());
	if (m_currentState == EPLS_MOVE &&  m_pCurrentMap->isTilePosBlocked(this->posFlag()) || !isInBorder() || morePosJadge())
	{
		if (m_pCurrentMap->bombBlock[(int)pos.x][(int)pos.y] && m_pCurrentMap->isTilePosBlocked(m_pHero->getPosition()))
			return;
		m_pHero->stopAction(m_pMoveBy);
		backPos();
	}
	if (m_pCurrentMap->bombAttack[(int)pos.x][(int)pos.y])
	{
		trapped();
	}
		
	if (m_pCurrentMap->itemPos[(int)pos.x][(int)pos.y])
	{
		getItem();
	}
}

CCPoint CPlayer::posFlag()
{
	CCPoint pos;
	pos.x = this->m_pHero->getPositionX();              //获得hero的x坐标位置  
	pos.y = this->m_pHero->getPositionY();              //获得hero的y坐标位置  
													
	if (m_moveDirection == ECT_LEFT)
		pos.x -= ITV_LEFT;
	else if (m_moveDirection == ECT_UP)
		pos.y += ITV_UP;
	else if (m_moveDirection == ECT_RIGHT)
		pos.x += ITV_RIGHT;
	else if (m_moveDirection == ECT_DOWN)
		pos.y -= ITV_DOWN;

	return pos;

	//m_pHero->stopAction(m_pMoveBy);                     //停止位移动作  
  
	

}

bool CPlayer::morePosJadge()
{
	if (m_currentState != EPLS_MOVE)return false;
	CCPoint pos =  posFlag();
	if (m_pCurrentMap == NULL)return false;

	if (m_pCurrentMap->isTilePosBlocked(ccp(pos.x, pos.y + ITV_UP)))
	{
		if (m_moveDirection == ECT_UP|| m_moveDirection == ECT_DOWN);
		else return true;
	}
	if (m_pCurrentMap->isTilePosBlocked(ccp(pos.x, pos.y - ITV_DOWN)))
	{
		if (m_moveDirection == ECT_DOWN|| m_moveDirection == ECT_UP);
		else return true;
	}
	if (m_pCurrentMap->isTilePosBlocked(ccp(pos.x - ITV_LEFT, pos.y)))
	{
		if (m_moveDirection == ECT_LEFT|| m_moveDirection == ECT_RIGHT);
		else return true;
	}
	if (m_pCurrentMap->isTilePosBlocked(ccp(pos.x + ITV_RIGHT, pos.y)))
	{
		if (m_moveDirection == ECT_RIGHT|| m_moveDirection == ECT_LEFT);
		else return true;
	}

	return false;
}

void CPlayer::handleDown(EControlType eCtrlType)
{
	if (playerID == 2)
		eCtrlType = (EControlType)(eCtrlType - 6);
	switch (eCtrlType)
	{
	case ECT_UP:
		move(eCtrlType);
		break;
	case ECT_DOWN:
		move(eCtrlType);
		break;
	case ECT_LEFT:
		move(eCtrlType);
		break;
	case ECT_RIGHT:
		move(eCtrlType);
		break;
	
	}
	
		

}

void CPlayer::handleUp(EControlType eCtrlType)
{
	if (playerID == 2)
		eCtrlType = (EControlType)(eCtrlType - 6);
	switch (eCtrlType)
	{
	case ECT_UP:
		stop(eCtrlType);
		break;
	case ECT_DOWN:
		stop(eCtrlType);
		break;
	case ECT_LEFT:
		stop(eCtrlType);
		break;
	case ECT_RIGHT:
		stop(eCtrlType);
		break;
	case ECT_PRESS:
		setBomb();
		break;
	}
	
}

bool CPlayer::changeState(EPlayerLogicState toState)
{
	if(!m_rgStateTable[toState][m_currentState])
	return false;

	m_currentState = toState;
	return true;
}

void CPlayer::backPos()
{
	

	float x = this->m_pHero->getPositionX();              //获得hero的x坐标位置  
	float y = this->m_pHero->getPositionY();              //获得hero的y坐标位置  
	float offset = CONTENT_WIDTH/m_iSpeed*(1.0/60.0)+2;                             //遇到障碍物后防止卡死进行微小移动的偏移量  
												//当停止时向人物背向方向略微移动2象素,防止人物在图块中卡死.  
	if (m_moveDirection == ECT_LEFT)
		this->m_pHero->setPosition(ccp(x + offset, y));
	else if (m_moveDirection == ECT_UP)
		this->m_pHero->setPosition(ccp(x, y - offset));
	else if (m_moveDirection == ECT_RIGHT)
		this->m_pHero->setPosition(ccp(x - offset, y));
	else if (m_moveDirection == ECT_DOWN)
		this->m_pHero->setPosition(ccp(x, y + 3));
}

bool CPlayer::isInBorder()
{
	CCPoint pos;
	pos.x = m_pHero->getPositionX();
	pos.y = m_pHero->getPositionY();

	if (pos.x<CONTENT_WIDTH - ITV_RIGHT -5 && pos.y<CONTENT_HEIGHT-ITV_UP*3 && pos.x>ITV_LEFT && pos.y>ITV_DOWN*2)
		return true;
	else
	return false;
}

void CPlayer::setBornPosition()
{
	CCTMXTiledMap* map = this->m_pCurrentMap;
	CCTMXObjectGroup* group = map->objectGroupNamed("object1");
	CCDictionary* dictionary = group->objectNamed("born1");
	float x = dictionary->valueForKey("x")->floatValue();
	float y = dictionary->valueForKey("y")->floatValue();
	m_pHero->setPosition(ccp(x, y));
}

CPlayer::~CPlayer()
{
	m_pHero->release();
}
