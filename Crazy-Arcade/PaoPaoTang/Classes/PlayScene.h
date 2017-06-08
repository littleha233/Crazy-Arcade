#ifndef _PLAY_SCENE_H_
#define _PLAY_SCENE_H_
#include "cocos2d.h"
#include "BaseScene.h"
#include "player.h"
#include "map.h"
using namespace cocos2d;

class CPlayScene:public CBaseScene
{
public:
	CPlayScene();
	
	virtual void onEnterScene();
	virtual void onExitScene();
	virtual void onUpdate(float dt)
	{

	}

	/*****¼üÅÌ¼àÌý********/
	void handleInput(EControlType eCtrlType, EPressState ePrsState);

private:
	CPlayer hero;
};
#endif