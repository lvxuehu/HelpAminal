#include "WelcomeLayer.h"
#include "MainGameScene.h"

WelcomeLayer::WelcomeLayer(void)
{
}

WelcomeLayer::~WelcomeLayer(void)
{
}

bool WelcomeLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		//png加入全局cache中
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animal.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui.plist");

		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		//加入background
		CCSprite* background=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(background);

		//加入copyright
//		CCSprite* copyright=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot_copyright.png"));
//		copyright->setAnchorPoint(ccp(0.5,0));
//		copyright->setPosition(ccp(winSize.width/2,winSize.height/2));
//		this->addChild(copyright);

		//加入loading
		CCSprite* loading=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("01.png"));
		loading->setPosition(ccp(winSize.width/2,winSize.height/2-40));
		this->addChild(loading);

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
        
        CCMoveBy* moveBy=CCMoveBy::create(2, ccp(60,0));
        CCCallFuncN* repeatdone=CCCallFuncN::create(this,callfuncN_selector(WelcomeLayer::loadingDone));
        CCSequence* sequence=CCSequence::create(moveBy,repeatdone,NULL);
		loading->runAction(sequence);

		
        //连接服务器取玩家数据
        getHighestHistorySorce();//得到最高的分数

        //响应返回键
		this->setKeypadEnabled(true);

		bRet=true;
	} while (0);

	return bRet;
}

//载入动画播放两遍后，进入GameScene场景
void WelcomeLayer::loadingDone(CCNode* pNode)
{
	CCScene* pScene=MainGameLayer::scene();
	CCTransitionMoveInB *animateScene=CCTransitionMoveInB::create(0.5f,pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);
}

//覆盖返回键的方法，如果点击返回键，游戏结束。
void WelcomeLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
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

void WelcomeLayer::getHighestHistorySorce()
{
	if (isHaveSaveFile())
	{
		int hscore=CCUserDefault::sharedUserDefault()->getIntegerForKey("HighestScore",0);
//		GameOverLayer::highestHistoryScore=hscore;//打开游戏时取得最高分数，初始化给GameOverlayer中的highestHistoryScore

	}
}