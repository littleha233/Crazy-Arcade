#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"
#include "BaseDef.h"
#include "Animation.h"
using namespace cocos2d;
/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  GameLogic : private cocos2d::CCApplication,private CCObject
{
public:
    GameLogic();
    virtual ~GameLogic();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

	void handleInput(EControlType ectType, EPressState epState);

	void handleEvent(int eventType,void* data = NULL);

	static GameLogic& sharedGameLogic()
	{
		return ((GameLogic&)CCApplication::sharedApplication());
	}
private:
	virtual void update(float dt);
private:
	CCScene* mSceneRoot;
	class CBeginScene* mBeginScene;
	class CPlayScene* mPlayScene;
	class CBaseScene* mCurrentScene;
};

#endif  // __APP_DELEGATE_H__

