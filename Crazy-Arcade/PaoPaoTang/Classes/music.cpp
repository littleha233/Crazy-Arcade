#include "music.h"

void preLoadMusic()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Snd/bg/Prepare.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Snd/bg/Village.mp3");

	SimpleAudioEngine::sharedEngine()->preloadEffect("Snd/die.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Snd/explode.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Snd/get.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Snd/win.wav");

}
