//
//  CoverScene.cpp
//  HelpAnimal
//
//  Created by lly on 14-8-31.
//
//

#include "CoverScene.h"
#include "WelcomeScene.h"


CoverLayer::CoverLayer(void){
    
}

CoverLayer::~CoverLayer(void){
    
}


CCScene* CoverLayer::scene(){
    CCScene* scene=CCScene::create();
    CoverLayer* coverLayer=CoverLayer::create();
    scene->addChild(coverLayer);
    return scene;
}


bool CoverLayer::init(){
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
        
        //png加入全局cache中
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("animal.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("gameui.plist");
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("gb.plist");
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bg1.plist");
        
        CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* bg=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("cover.png"));
        bg->setPosition(ccp(winSize.width/2,winSize.height/2));
        
        this->addChild(bg);
        
        this->schedule(schedule_selector(CoverLayer::startWelcomeScene),2.0f);
        
        bRet=true;
    }while (0);
    
    return bRet;
}


void CoverLayer::startWelcomeScene(cocos2d::CCObject *object){
    CCScene* pScene=WelcomeLayer::scene();
	CCTransitionFade *animateScene=CCTransitionFade::create(1.5f,pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);

}