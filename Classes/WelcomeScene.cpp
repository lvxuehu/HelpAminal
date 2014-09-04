#include "WelcomeScene.h"
#include "GameLayerScene.h"
#include "SimpleAudioEngine.h"

WelcomeLayer::WelcomeLayer(void)
{
    ifPlayBkMusic=true;
}

WelcomeLayer::~WelcomeLayer(void)
{
}


CCScene* WelcomeLayer::scene(){
    CCScene* scene=CCScene::create();
    WelcomeLayer* welcomeLayer=WelcomeLayer::create();
    scene->addChild(welcomeLayer);
    return scene;

}

bool WelcomeLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
        preloadMusic();
        
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		//加入background
		CCSprite* background=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("b1.png"));
		background->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(background);

        
        //加入title
		CCSprite* title=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("titile.png"));
		title->setPosition(ccp(winSize.width/2,winSize.height/2+100));
		this->addChild(title);
        
        

        
        //加入开始游戏按钮
		CCSprite* normalPause=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play.png"));
        CCMenuItemSprite* pStartItem=CCMenuItemSprite::create(normalPause,NULL,this,menu_selector(WelcomeLayer::menuStartGameCallback));
        
        
        //添加music控制按钮
		CCSprite* musicNormalExit=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("stopmusicb.png"));
		CCSprite* musicPressedExit=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("startmusicb.png"));
        CCMenuItemSprite* stopMusic=CCMenuItemSprite::create(musicPressedExit, NULL);
        CCMenuItemSprite* startMusic=CCMenuItemSprite::create(musicNormalExit,NULL);
        CCMenuItemToggle* pMusicItem=CCMenuItemToggle::createWithTarget(this, menu_selector(WelcomeLayer::menuMusicGameCallback), stopMusic,startMusic,NULL);
		pMusicItem->setPositionX(200);
        
        
		CCMenu *menu=CCMenu::create(pStartItem,pMusicItem,NULL);
		menu->setPosition(ccp(winSize.width/2,winSize.height/2-100));
        menu->alignItemsHorizontallyWithPadding(40);
		this->addChild(menu,101);
        
        
		//加入copyright
//		CCSprite* copyright=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot_copyright.png"));
//		copyright->setAnchorPoint(ccp(0.5,0));
//		copyright->setPosition(ccp(winSize.width/2,winSize.height/2));
//		this->addChild(copyright);

		//加入loading
//		CCSprite* loading=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("10.png"));
//		loading->setPosition(ccp(winSize.width/2+100,winSize.height/2+40));
//		this->addChild(loading);

//		CCAnimation* animation=CCAnimation::create();
//		animation->setDelayPerUnit(0.2f);
//		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
//		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
//		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
//		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));
//
//		CCAnimate* animate=CCAnimate::create(animation);
//		CCRepeat* repeat=CCRepeat::create(animate,2);
//		CCCallFuncN* repeatdone=CCCallFuncN::create(this,callfuncN_selector(WelcomeLayer::loadingDone));
//		CCSequence* sequence=CCSequence::create(repeat,repeatdone,NULL);
        
//        CCMoveBy* moveBy=CCMoveBy::create(4, ccp(-60,0));
//        CCCallFuncN* repeatdone=CCCallFuncN::create(this,callfuncN_selector(WelcomeLayer::loadingDone));
//        CCSequence* sequence=CCSequence::create(moveBy,repeatdone,NULL);
//		loading->runAction(sequence);

		
        //连接服务器取玩家数据
        getHighestHistorySorce();//得到最高的分数

        //响应返回键
		this->setKeypadEnabled(true);

		bRet=true;
	} while (0);

	return bRet;
}



void WelcomeLayer::menuMusicGameCallback(cocos2d::CCObject *pSender){
    if(ifPlayBkMusic)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        ifPlayBkMusic=false;
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		ifPlayBkMusic=true;
	}
}


void WelcomeLayer::menuStartGameCallback(cocos2d::CCObject *pSender){
    CCScene* pScene=GameLayer::scene();
	CCTransitionMoveInB *animateScene=CCTransitionMoveInB::create(0.5f,pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);
}


//载入动画播放两遍后，进入GameScene场景
void WelcomeLayer::loadingDone(CCNode* pNode)
{
//	CCScene* pScene=GameLayer::scene();
//	CCTransitionMoveInB *animateScene=CCTransitionMoveInB::create(0.5f,pScene);
//	CCDirector::sharedDirector()->replaceScene(animateScene);
}

//覆盖返回键的方法，如果点击返回键，游戏结束。
void WelcomeLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool WelcomeLayer::isHaveSaveFile()
{
	if(!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml"))
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml", true);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore",0);
		CCUserDefault::sharedUserDefault()->flush();
		return false;
	}
	else
	{
		return true;
	}
}


void WelcomeLayer::preloadMusic(){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("click-01.wav");
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);//设置音量0.0-1.0</span>
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.wav",true);
    
}

void WelcomeLayer::getHighestHistorySorce()
{
	if (isHaveSaveFile())
	{
		int hscore=CCUserDefault::sharedUserDefault()->getIntegerForKey("HighestScore",0);
//		GameOverLayer::highestHistoryScore=hscore;//打开游戏时取得最高分数，初始化给GameOverlayer中的highestHistoryScore

	}
}