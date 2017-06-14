#ifndef _BASE_DEF_H_
#define _BASE_DEF_H_

#define FRAME_WIDTH 800
#define FRAME_HEIGHT 600
#define ITV_UP 12.0 //碰撞检测时向上间隔
#define ITV_DOWN 12.0 //碰撞检测时向下间隔
#define ITV_LEFT 12.0 //碰撞检测时向左间隔
#define ITV_RIGHT 12.0 //碰撞检测时向右间隔
#define CONTENT_WIDTH 680 //游戏界面宽度
#define CONTENT_HEIGHT 600 //游戏界面高度

#define ROLE1 "Pic/Role1.png"
#define ROLE2 "Pic/Role2.png"

enum EControlType
{
	ECT_UP,
	ECT_DOWN,
	ECT_LEFT,
	ECT_RIGHT,
	ECT_PRESS,
	ECT_NUM,
	ECT_UP2,
	ECT_DOWN2,
	ECT_LEFT2,
	ECT_RIGHT2,
	ECT_PRESS2,
	ECT_NUM2
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