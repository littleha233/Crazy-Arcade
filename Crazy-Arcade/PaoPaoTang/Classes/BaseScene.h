#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_
#include "cocos2d.h"
#include "StringTableMgr.h"
using namespace cocos2d;
class CBaseScene
{
public:
	CBaseScene()
	{
		mRootLayer = CCLayer::create();
		mRootLayer->retain();
	}
	virtual ~CBaseScene()
	{
		mRootLayer->release();
		mRootLayer = NULL;
	}
	CCLayer* getRootLayer()
	{
		return mRootLayer;
	}

public:
	virtual void onEnterScene(){}
	virtual void onExitScene(){}
	virtual void onUpdate(float dt)
	{

	}
	virtual void onHandleEvent(int eventType,void* data)
	{

	}
protected:
	CCLayer* mRootLayer;
};
#endif