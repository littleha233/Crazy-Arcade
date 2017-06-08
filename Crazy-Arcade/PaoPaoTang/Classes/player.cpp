/**********************/
/*
*文件说明：此文件包含游戏中主角对象的定义
*作者：陈乾
*时间：2017-5-29
*/
/**********************/

#include "player.h"

#define ITV_UP 10.0 //碰撞检测时向上间隔
#define ITV_DOWN 0.0 //碰撞检测时向下间隔
#define ITV_LEFT 20.0 //碰撞检测时向左间隔
#define ITV_RIGHT 20.0 //碰撞检测时向右间隔
#define CONTENT_WIDTH 800 //游戏界面宽度
#define CONTENT_HEIGHT 600 //游戏界面高度


using namespace cocos2d;


CPlayer::CPlayer():
	m_iMaxBombNum(1),
	m_iSettledBobNum(0),
	m_iBombScale(1),
	m_iSpeed(3),
	m_pHero(NULL),
	m_pAnimate(NULL),
	m_currentState(EPLS_STAND),
	m_pCurrentMap(NULL),
	m_moveDirection(ECT_NUM)
{
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_pHero = CCSprite::create("Pic/Role1.png", CCRectMake(0, 256 / 4, 288 / 6, 256 / 4));
	m_pHero->retain();
	m_pHero->setAnchorPoint(ccp(0.5, 0.1));
	m_pHero->setPosition(ccp(40,40));
	//设置update监听
	CCNode::onEnter();
	this->schedule(schedule_selector(CPlayer::myUpdate));

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

CCSprite * CPlayer::getSprite()
{
	return m_pHero;
}

void CPlayer::setMap(CMap* amap)
{
	m_pCurrentMap = amap;
	setBornPosition();
}

void CPlayer::move(EControlType eCtrlType)
{
	if (!changeState(EPLS_MOVE))
		return;

	std::string aniName = ROLE;
	char order = '0' + eCtrlType;
	aniName += order;
	m_pAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(aniName.c_str()));
	m_pHero->runAction(m_pAnimate);

	int dir[EPLS_NUM][2] = { {0,1},{0,-1},{-1,0},{1,0} };
	m_pMoveBy = CCMoveBy::create(m_iSpeed, ccp(dir[eCtrlType][0] * CONTENT_WIDTH, dir[eCtrlType][1] * CONTENT_HEIGHT));
	m_pHero->runAction(m_pMoveBy);
	
	/**碰撞测试**/
	m_moveDirection = eCtrlType;
}

void CPlayer::stop(EControlType eCtrlType)
{
	if (!changeState(EPLS_STAND))
		return;

	m_pHero->stopAction(m_pAnimate);
	m_pHero->setTextureRect(CCRectMake(0 * 288 / 6, eCtrlType * 256 / 4, 288 / 6, 256 / 4));
	m_pHero->stopAction(m_pMoveBy);
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
	if (m_currentState == EPLS_MOVE &&  m_pCurrentMap->isTilePosBlocked(this->posFlag()) || !isInBorder())
	{
		m_pHero->stopAction(m_pMoveBy);
		backPos();
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

void CPlayer::handleDown(EControlType eCtrlType)
{

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
	float offset = 2;                             //遇到障碍物后防止卡死进行微小移动的偏移量  
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

	if (pos.x<CONTENT_WIDTH - ITV_RIGHT -5 && pos.y<CONTENT_HEIGHT-ITV_UP*2 && pos.x>ITV_LEFT && pos.y>ITV_DOWN*2)
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
