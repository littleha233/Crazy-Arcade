#include "cocos2d.h"
#include "CCEGLView.h"
#include "GameLogic.h"
#include "SimpleAudioEngine.h"
#include "BeginScene.h"
#include "PlayScene.h"
using namespace CocosDenshion;

USING_NS_CC;
GameLogic::GameLogic()
	:mSceneRoot(NULL)
	,mBeginScene(NULL)
{
}

GameLogic::~GameLogic()
{
    SimpleAudioEngine::end();
}

bool GameLogic::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//     pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
	
	//
	pDirector->getScheduler()->scheduleUpdateForTarget(this,0,false);

	mSceneRoot = CCScene::create();
	mBeginScene = new CBeginScene();
	mPlayScene = new CPlayScene();


	mSceneRoot->addChild(mBeginScene->getRootLayer());
	mCurrentScene = mBeginScene;
	mCurrentScene->onEnterScene();
    // run
    pDirector->runWithScene(mSceneRoot);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void GameLogic::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void GameLogic::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void GameLogic::handleEvent( int eventType,void* data /*= NULL*/ )
{
	switch(eventType)
	{
	case ESSE_Play:
		{
			mCurrentScene->onExitScene();
			mSceneRoot->removeChild(mCurrentScene->getRootLayer(),false);
			mCurrentScene = mPlayScene;
			mSceneRoot->addChild(mCurrentScene->getRootLayer());
			mCurrentScene->onEnterScene();
			return;
		}
	case ESSE_Exit:
		{
			mCurrentScene->onExitScene();
			mCurrentScene = NULL;
			CCDirector::sharedDirector()->end();

			delete mBeginScene;
			mBeginScene = NULL;
			delete mPlayScene;
			mPlayScene = NULL;
			return;
		}
	case ESSE_Back2Menu:
		{
			mCurrentScene->onExitScene();
			mSceneRoot->removeChild(mCurrentScene->getRootLayer(),false);
			mCurrentScene = mBeginScene;
			mSceneRoot->addChild(mCurrentScene->getRootLayer());
			mCurrentScene->onEnterScene();
			return;
		}
	}
	if(mCurrentScene)
		mCurrentScene->onHandleEvent(eventType,data);
}

void GameLogic::update( float dt )
{
	//to do..

	//...
	if(mCurrentScene)
		mCurrentScene->onUpdate(dt);
}