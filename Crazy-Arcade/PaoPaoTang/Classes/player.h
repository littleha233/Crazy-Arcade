/**********************/
/*
*文件说明：此文件包含游戏中主角对象的声明
*作者：陈乾
*时间：2017-5-29 
*/
/**********************/
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"cocos2d.h"
#include "BaseDef.h"
#include <string>
#include "map.h"
#include "bomb.h"
#include "BaseScene.h"
#include "music.h"
class CBaseScene;
class CBomb;
class CPlayer :public cocos2d::CCNode
{
	friend class CBomb;
public:
	//初始化角色
	CPlayer(CMap* curMap);
	static CPlayer* create(CMap* curMap);
	//获取精灵
	cocos2d::CCSprite* getSprite();
	//走动函数
	void move(EControlType);
	//停下
	void stop(EControlType);
	//放置炸弹
	void setBomb();
	//角色被泡泡包围
	void trapped();
	//角色死亡
	void dead();
	bool isDead();
	void win(int ID);

	//获得道具
	void getItem();
	//键盘控制
	void handleInput(EControlType,EPressState);
	//更新函数
	void myUpdate(float dt);
	//碰撞检测函数
	cocos2d::CCPoint posFlag();
	bool morePosJadge();
	//设置出生点
	void setBornPosition();
	//销毁retain精灵
	EControlType getMoveDirection();
	~CPlayer();

	static int s_playerNum;

private:

	//handleInput内调用,用于接受按下的操作
	void handleDown(EControlType);
	//handleInput内调用,用于接受放开的操作
	void handleUp(EControlType);
	//改变主角状态
	bool changeState(EPlayerLogicState);
	//碰撞后回退
	void backPos();
	//边界检测
	bool isInBorder();
	


	int m_iMaxBombNum;//最大炸弹放置数
	int m_iSettledBobNum;//已放置炸弹数
	int m_iBombScale;//炸弹范围
	int m_iSpeed;//移动速度
	int playerID;
	
	/****状态表测试******/
	EPlayerLogicState m_currentState;//当前状态
	EControlType m_moveDirection;//记录移动时的方向
	bool m_rgStateTable[EPLS_NUM][EPLS_NUM];//状态表
	/*************/


	cocos2d::CCSprite* m_pHero;//主角精灵指针
	cocos2d::CCAnimate* m_pAnimate;//当前动画
	cocos2d::CCMoveBy* m_pMoveBy;//当前移动动作
	CMap* m_pCurrentMap;//当前加载地图
	
	

};





#endif // !_PLAYER_H_
