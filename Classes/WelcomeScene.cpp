#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"


WelcomeScene::WelcomeScene(void)
{
	welcomeLayer=NULL;
}


WelcomeScene::~WelcomeScene(void)
{
}

bool WelcomeScene::init(){
	bool pRet=false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		welcomeLayer=WelcomeLayer::create();
		CC_BREAK_IF(!welcomeLayer);
		this->addChild(welcomeLayer);
		preloadMusic();
		pRet=true;
	} while (0);
	return pRet;
}


void WelcomeScene::preloadMusic(){
//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("game_music.wav");
//	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_music.wav",true);
}


