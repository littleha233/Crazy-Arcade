/**********************/
/*
*文件说明：此文件包含游戏中瓦片地图创建及其坐标相关函数的声明
*作者：陈乾
*时间：2017-6-2
*//**********************/
#define TILEDWIDTH 17
#define TILEDHEIGHT 15

#ifndef _MAP_H_
#define _MAP_H_

#include "cocos2d.h"
#include "item.h"
#include "BeginScene.h"
#include "player.h"
#include "bomb.h"

class CBomb;
class CPlayer;
class CMap :public cocos2d::CCTMXTiledMap
{
public:
	static CMap* initTileMap(const char* tmxFile, CBaseScene* curScene);
	CMap(CBaseScene* curScene);
	//通过指定坐标转换为地图块坐标
	cocos2d::CCPoint tilePosFromLocation(cocos2d::CCPoint pos);
	//判断瓦片是否为障碍
	bool isTilePosBlocked(cocos2d::CCPoint pos);
	bool bombBlock[TILEDWIDTH][TILEDHEIGHT];
	bool bombAttack[TILEDWIDTH][TILEDHEIGHT];
	int itemPos[TILEDWIDTH][TILEDHEIGHT];
	CCSprite* itemPointerPos[TILEDWIDTH][TILEDHEIGHT];
	CBomb* bombPointerPos[TILEDWIDTH][TILEDHEIGHT];
	void setBombBlock(int x, int y,bool z);
	void setItem(cocos2d::CCPoint);
	void handleInput(EControlType eCtrlType, EPressState ePrsState);
	CPlayer* m_pPlayer1;
	CPlayer* m_pPlayer2;
	CBaseScene* m_pBelongedScene;

};


#endif // !_MAP_H_
