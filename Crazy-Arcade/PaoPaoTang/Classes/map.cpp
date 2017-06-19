/**********************/
/*
*文件说明：此文件包含游戏中瓦片地图创建及其坐标相关函数的定义
*作者：陈乾
*时间：2017-6-2
*/
/**********************/
#include "map.h"
#include "bomb.h"
using namespace cocos2d;
class CBomb;
CMap* CMap::initTileMap(const char *tmxfile, CBaseScene* curScene)
{
	CMap *map = new CMap(curScene);
	if (map->initWithTMXFile(tmxfile))
	{
		map->autorelease();
		return map;
	}

	CC_SAFE_DELETE(map);
	return NULL;
}

CMap::CMap(CBaseScene* curScene):
	m_pBelongedScene(curScene),
	m_pPlayer1(NULL),
	m_pPlayer2(NULL),
	judgeTime(0)
{
	memset(bombBlock, 0, sizeof(bombBlock));
	memset(bombAttack, 0, sizeof(bombAttack));
	memset(itemPos, 0, sizeof(itemPos));
	memset(itemPointerPos, 0, sizeof(itemPointerPos));
	memset(bombPointerPos, 0, sizeof(bombPointerPos));

	for (int i = 0; i < TILEDHEIGHT; i++) 
	{
		bombBlock[0][i] = 1;
		bombBlock[TILEDWIDTH-1][i] = 1;
	}
	for (int i = 0; i < TILEDWIDTH; i++)
	{
		bombBlock[i][0] = 1;
		bombBlock[i][TILEDHEIGHT-1] = 1;
	}
	
	CCSprite* pBG = CCSprite::create("Pic/BG.png");
	pBG->setAnchorPoint(CCPointZero);
	addChild(pBG, 1); 
	setPosition(ccp(-20, 0));
	pBG->setPosition(ccp(20, 0));
	m_pBelongedScene->getRootLayer()->addChild(this,1);
	m_pPlayer1 = CPlayer::create(this);
	m_pPlayer2 = CPlayer::create(this);
}

//通过指定的坐标转换为地图块坐标  
CCPoint CMap::tilePosFromLocation(CCPoint pos)
{
	int x = pos.x / this->getTileSize().width;
	int y = pos.y / this->getTileSize().height;

	y = this->getMapSize().height - y-1;
	return ccp(x, y);
}
//判断该瓦片是否为障碍  
bool CMap::isTilePosBlocked(CCPoint pos)
{
	//判断当前块是否为碰撞块  
	CCPoint tilpos = tilePosFromLocation(pos);                //将带入的坐标转为块坐标  
	CCTMXLayer *clayer = this->layerNamed("collision");      //通过层名字获得该层对象 


	int tileGID = clayer->tileGIDAt(tilpos);             //获得该块的GID标识别  
	if (tileGID != 0)
	{
		CCDictionary* properties = this->propertiesForGID(tileGID);
		if (strcmp(properties->valueForKey("Collidable")->getCString(), "true") == 0)
			return true;
	}
	if (bombBlock[(int)tilpos.x][(int)tilpos.y])
		return true;

	return false;
}
bool CMap::isTilePosBlocked(cocos2d::CCPoint pos, CPlayer* hero)
{
	//判断当前块是否为碰撞块  
	CCPoint spritePos = hero->getSprite()->getPosition();

	CCPoint tilSptitePos = tilePosFromLocation(spritePos);
	CCPoint tilpos = tilePosFromLocation(pos);                //将带入的坐标转为块坐标  
	CCTMXLayer *clayer = this->layerNamed("collision");      //通过层名字获得该层对象 


	int tileGID = clayer->tileGIDAt(tilpos);             //获得该块的GID标识别  
	if (tileGID != 0)
	{
		CCDictionary* properties = this->propertiesForGID(tileGID);
		if (strcmp(properties->valueForKey("Collidable")->getCString(), "true") == 0)
			return true;
	}
	CCPoint centre = toTiledPos(pos);
	float dx = fabs(centre.x - spritePos.x);
	float dy = fabs(centre.y - spritePos.y);

	bool m = (hero->getMoveDirection() == ECT_LEFT || hero->getMoveDirection() == ECT_RIGHT) && (dx < 20) && (dy < 20 + ITV_LEFT);
	bool n = (hero->getMoveDirection() == ECT_UP || hero->getMoveDirection() == ECT_DOWN) && (dx < 20 + ITV_UP) && (dy < 20);

	if (bombBlock[(int)tilpos.x][(int)tilpos.y] && !bombBlock[(int)tilSptitePos.x][(int)tilSptitePos.y] && !m && !n)
		return true;

	return false;
}


void CMap::setBombBlock(int x, int y,bool z)
{
	bombBlock[x][y] = z;
}

void CMap::setItem(CCPoint tPos)
{
	CItem* item = CItem::create(tPos,this);
}

void CMap::handleInput(EControlType eCtrlType, EPressState ePrsState)
{
	if (m_pPlayer1 != NULL)m_pPlayer1->handleInput(eCtrlType, ePrsState);
	if (m_pPlayer2 != NULL)m_pPlayer2->handleInput(eCtrlType, ePrsState);
}

void CMap::judge(float dt)
{
	if (judgeTime == 0)
	{
		if (!m_pPlayer1->isDead()&& m_pPlayer2->isDead())win(1);
		if (m_pPlayer1->isDead() && !m_pPlayer2->isDead())win(2);
		if (m_pPlayer1->isDead() && m_pPlayer2->isDead())win(-1);
		judgeTime += 1;
	}
}

void CMap::win(int ID)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playEffect("Snd/win.wav");
	if (ID == 1)
	{
		CCSprite* title = CCSprite::create("Pic/Player.png",CCRectMake(0,0,110,25));
		CCSprite* win = CCSprite::create("Pic/Win.png");
		title->setPosition(ccp(CONTENT_WIDTH / 2 - 100, CONTENT_HEIGHT / 2 + 100));
		win->setPosition(ccp(CONTENT_WIDTH / 2 - 100 + 55 + 102, CONTENT_HEIGHT / 2 + 100));
		addChild(title, 5);
		addChild(win, 5);
		
	}
	else if (ID == 2)
	{
		CCSprite* title = CCSprite::create("Pic/Player.png", CCRectMake(0, 25, 110, 25));
		CCSprite* win = CCSprite::create("Pic/Win.png");
		title->setPosition(ccp(CONTENT_WIDTH / 2 - 100, CONTENT_HEIGHT / 2 + 100));
		win->setPosition(ccp(CONTENT_WIDTH / 2 - 100 + 55 + 102, CONTENT_HEIGHT / 2 + 100));
		addChild(title, 5);
		addChild(win, 5);
	}
	else if (ID == -1)
	{
		CCSprite* draw = CCSprite::create("Pic/Draw.png");
		draw->setPosition(ccp(CONTENT_WIDTH / 2 - 100 + 55 + 102, CONTENT_HEIGHT / 2 + 100));
		addChild(draw, 5);
	}

	CCSprite* exit = CCSprite::create("back.png");
	CCMenuItemSprite * back_labelItem = CCMenuItemSprite::create(exit, exit, exit, CMenuSelectHandler::sharedHandler(), menu_selector(CMenuSelectHandler::onMenu_Back2Menu));
	back_labelItem->setScale(0.4);
	back_labelItem->setPosition(ccp(CONTENT_WIDTH/2, CONTENT_HEIGHT/2));
	CCMenu* pMenu = CCMenu::create(back_labelItem, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, 5);
	
}


cocos2d::CCPoint CMap::toTiledPos(cocos2d::CCPoint &pos)
{

	CCSize tiledSize = getTileSize();
	CCSize mapSize = getMapSize();

	pos.x = (int)(pos.x / tiledSize.width)*tiledSize.width + tiledSize.width / 2;
	pos.y = (int)(pos.y / tiledSize.height)*tiledSize.height + tiledSize.height / 2;

	return pos;
}