#ifndef _BASE_DEF_H_
#define _BASE_DEF_H_

#define FRAME_WIDTH 600
#define FRAME_HEIGHT 450
enum EControllType
{
	ECT_NONE,
	ECT_UP,
	ECT_DOWN,
	ECT_LEFT,
	ECT_RIGHT,
	ECT_PRESS,
	ECT_NUM
};

enum EPressState
{
	EPS_DOWN,
	EPS_UP
};

enum EBeginSceneEvent
{
	EBSE_Play
};

#endif