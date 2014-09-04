//
//  MainGameScene.cpp
//  HelpAnimal
//
//  Created by lly on 14-7-30.
//
//

#include "MainGameScene.h"
#include "GameLayerScene.h"

USING_NS_CC;

CCScene* MainGameLayer::scene(){
    CCScene* scene=CCScene::create();
    MainGameLayer* mainGameLayer=MainGameLayer::create();
    scene->addChild(mainGameLayer);
    return scene;
}

bool MainGameLayer::init(){
    bool bRet=false;
    do{
        CC_BREAK_IF(!CCLayer::init());
        
        CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        
        
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        CCLayer *layer = CCLayerColor::create(ccc4(0x23, 0x50, 0x80, 0x80), winSize.width, winSize.height);
        layer->ignoreAnchorPointForPosition(false);
        layer->setPosition(s.width / 2, s.height / 2);
        this->addChild(layer, 1, layer->getTag());

        //开始游戏按钮
		CCSprite* normalBackToGame=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play.png"));
		CCSprite* pressedBackToGame=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play.png"));
		CCMenuItemImage* pBackItem=CCMenuItemImage::create();
		pBackItem->initWithNormalSprite(normalBackToGame,pressedBackToGame,NULL,this,menu_selector(MainGameLayer::startGame));
		pBackItem->setPosition(ccp(winSize.width/2,winSize.height/2+10));
		CCMenu *menuBack=CCMenu::create(pBackItem,NULL);
		menuBack->setPosition(CCPointZero);
		this->addChild(menuBack);
        bRet = true;
    }while (0);
        return bRet;
    
    
    
}

void MainGameLayer::startGame(CCObject* object){
    CCScene* pScene=GameLayer::scene();
	CCTransitionMoveInB *animateScene=CCTransitionMoveInB::create(0.5f,pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);
}




