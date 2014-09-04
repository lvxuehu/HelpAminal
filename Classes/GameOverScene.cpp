//
//  GameOverScene.cpp
//  HelpAnimal
//
//  Created by lly on 14-8-7.
//
//

#include "GameOverScene.h"

GameOverLayer::GameOverLayer(GameLayer *gl){
    gameLayer=gl;
}

GameOverLayer::~GameOverLayer(){
    
}

GameOverLayer* GameOverLayer::create(GameLayer *gameLayer){
    GameOverLayer* m=new GameOverLayer(gameLayer);
    if(m&&m->init()){
        //    if(m&&m->initWithFile("enemy1.png")){
        return m;
    }
    
    CC_SAFE_DELETE(m);
    return NULL;

}


bool GameOverLayer::init(){
    bool bRet=false;
    do{
        CC_BREAK_IF(!CCLayer::init());        
        CC_BREAK_IF(!initUi());
        bRet=true;
    }while (0);
    return bRet;
}

//初始化界面
bool GameOverLayer::initUi(){
    bool bRet=false;
    do{
        
        CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        
		//加入background
		CCSprite* background=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("b1.png"));
		background->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(background);
        
        //当前游戏分数
        int score=gameLayer->getGameScore();
//        CCLog("score=%d",score);
        CCString* strScore=CCString::createWithFormat("积分:%d",score);
        gameScoreItem = CCLabelTTF::create(strScore->m_sString.c_str(), "Arial", 30);
        gameScoreItem->setColor(ccc3(0,0,0));
        gameScoreItem->setPosition(ccp(winSize.width/2,winSize.height/2+50));
        this->addChild(gameScoreItem, 1);
        
        
        //当前游戏时间
        int gametime=gameLayer->getGameTime();
//        CCLog("gametime=%d",gametime);
        CCString* strTime=CCString::createWithFormat("时间:%d",gametime);
        gameTimeItem = CCLabelTTF::create(strTime->m_sString.c_str(), "Arial", 30);
        gameTimeItem->setColor(ccc3(0,0,0));
        gameTimeItem->setPosition(ccp(winSize.width/2,gameScoreItem->getPositionY()-50));
        this->addChild(gameTimeItem, 1);
        
        //当前游戏血量
        int lefe=gameLayer->getGameLife();
//        CCLog("lefe=%d",lefe);
        CCString* strLife=CCString::createWithFormat("血量:%d",lefe);
        gameLifeItem = CCLabelTTF::create(strLife->m_sString.c_str(), "Arial", 30);
        gameLifeItem->setColor(ccc3(0,0,0));
        gameLifeItem->setPosition(ccp(winSize.width/2,gameTimeItem->getPositionY()-50));
        this->addChild(gameLifeItem, 1);
        
        
        
        //重新游戏按钮
		CCSprite* normalBackToGame=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bt.png"));
		CCSprite* pressedBackToGame=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bt.png"));
		CCMenuItemImage* pBackItem=CCMenuItemImage::create();
		pBackItem->initWithNormalSprite(normalBackToGame,pressedBackToGame,NULL,this,menu_selector(GameOverLayer::replayGame));
		pBackItem->setPosition(ccp(winSize.width/2,winSize.height/2-80));
		CCMenu *menuBack=CCMenu::create(pBackItem,NULL);
		menuBack->setPosition(CCPointZero);
		this->addChild(menuBack);

        
        

        
        bRet=true;
    }while (0);
    return bRet;
}



CCScene* GameOverLayer::scene(GameLayer* gameLayer){
    CCScene* scene=CCScene::create();
    GameOverLayer* gameOverLayer=GameOverLayer::create(gameLayer);
    scene->addChild(gameOverLayer);
    return scene;
}

void GameOverLayer::replayGame(){
    CCScene* pScene=GameLayer::scene();
	CCTransitionMoveInB *animateScene=CCTransitionMoveInB::create(0.5f,pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);

}
