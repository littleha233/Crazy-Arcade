#ifndef _BASE_DEF_H_
#define _BASE_DEF_H_

#define FRAME_WIDTH 600
#define FRAME_HEIGHT 450

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