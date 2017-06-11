#ifndef _BASE_DEF_H_
#define _BASE_DEF_H_

#define FRAME_WIDTH 800
#define FRAME_HEIGHT 600
#define ITV_UP 5.0 //碰撞检测时向上间隔
#define ITV_DOWN 16 //碰撞检测时向下间隔
#define ITV_LEFT 16.0 //碰撞检测时向左间隔
#define ITV_RIGHT 16.0 //碰撞检测时向右间隔
#define CONTENT_WIDTH 800 //游戏界面宽度
#define CONTENT_HEIGHT 600 //游戏界面高度

#define ROLE "Pic/Role1.png"

enum EControlType
{
	ECT_UP,
	ECT_DOWN,
	ECT_LEFT,
	ECT_RIGHT,
	ECT_PRESS,
	ECT_NUM
};

enum EMoveDirection
{
	EMD_UP,
	EMD_DOWN,
	EMD_LEFT,
	EMD_RIGHT,
	EMD_NUM
};

enum EPressState
{
	EPS_NONE,
	EPS_DOWN,
	EPS_UP
};

enum ESceneSwitchEvent
{
	ESSE_Play,
	ESSE_Exit,
	ESSE_Back2Menu
};


enum EPlayerLogicState
{
	EPLS_STAND,
	EPLS_MOVE,
	EPLS_PAOPAO,
	EPLS_DEAD,
	EPLS_NUM
};

enum EplayerInput
{
	EPI_STOP,
	EPI_MOVE,
	EPI_KILL,
	EPI_NUM
};


#endif