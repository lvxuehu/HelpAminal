#include "ControlLayer.h"
#include "SimpleAudioEngine.h"


ControlLayer::ControlLayer(void)
{
	//scoreItem=NULL;
//	pPauseItem=NULL;
//    pExitItem=NULL;
	noTouchLayer=NULL;
}


ControlLayer::~ControlLayer(void)
{
}


bool ControlLayer::init(){
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
        
        CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        

		//添加暂停按钮
		CCSprite* startSprite=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pause.png"));
		CCSprite* stopSprite=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("playsmall.png"));
        
        CCMenuItemSprite* startlItem=CCMenuItemSprite::create(startSprite, NULL);
        CCMenuItemSprite* stopItem=CCMenuItemSprite::create(stopSprite, NULL);
        CCMenuItemToggle* toggleItem=CCMenuItemToggle::createWithTarget(this,menu_selector(ControlLayer::menuPauseCallback),startlItem,stopItem,NULL);

        
        
        //添加退出按钮
		CCSprite* exitSprite=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("X.png"));
        CCMenuItemSprite* exitItem=CCMenuItemSprite::create(exitSprite,NULL,this,menu_selector(ControlLayer::menuExitCallback));
        
        
		CCMenu *menuPause=CCMenu::create(toggleItem,exitItem,NULL);
        menuPause->alignItemsVerticallyWithPadding(20);
		menuPause->setPosition(ccp(startSprite->getContentSize().width/2+30, winSize.height-startSprite->getContentSize().height/2-70));
		this->addChild(menuPause,101);
        
        
        
        //添加金币图标
        CCSprite* coinSprite=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("coin.png"));
        coinSprite->setPosition(ccp(140, winSize.height-coinSprite->getContentSize().height/2-25));
        this->addChild(coinSprite);
        
        
        //添加金币数
//        CCLabelBMFont *coinScore = CCLabelBMFont::create("876", "font-issue1343.fnt");
//        coinScore->setAnchorPoint(ccp(0.5f, 0.5f));
//        coinScore->setColor(ccRED);
        
        CCLabelTTF* coinScore=CCLabelTTF::create("231", "Arial", 60);
//        coinScore->setColor(ccc3(0,0,0));
        coinScore->setColor(ccYELLOW);
        
        coinScore->setPosition(ccp(coinSprite->getPositionX()+coinSprite->getContentSize().width+25, coinSprite->getPositionY()-3));

        this->addChild(coinScore,0,tag_coinScore);
        
        
		bRet=true;
	} while (0);
	return bRet;
}


//点击暂停按钮之后
void ControlLayer::menuPauseCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click-01.wav");
	if(!CCDirector::sharedDirector()->isPaused())
	{
		
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		CCDirector::sharedDirector()->pause();
		noTouchLayer=NoTouchLayer::create();
        this->addChild(noTouchLayer);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		CCDirector::sharedDirector()->resume();
		this->removeChild(noTouchLayer,true);
	}
}

//点击退出按钮之后
void ControlLayer::menuExitCallback(CCObject* pSender)
{
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click-01.wav");
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
