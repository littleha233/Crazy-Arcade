#ifndef MAP_SCENE_H_
#define MAP_SCENE_H_
#include "cocos2d.h"
#include "BaseScene.h"
using namespace cocos2d;
class CMapScene :public CBaseScene
{
public:
	CMapScene()
	{

	}
	virtual void onEnterScene(int i);
	virtual void onExitScene();
	virtual void onUpdate(float dt)
	{

	}
};
#endif
