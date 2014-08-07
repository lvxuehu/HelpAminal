//
//  Animal.cpp
//  HelpAnimal
//
//  Created by lly on 14-8-2.
//
//

#include "Animal.h"

Animal::Animal(){
    
}


Animal::Animal(GameLayer* gameLayer){
    this->gameLayer=gameLayer;
    lostScore=0;
    helpLife=0;
    helpScore=0;
    speed=0.0;
}

Animal::~Animal(){
    
}

CCRect Animal::rect(){
    CCSize size = getTexture()->getContentSize();
    return CCRectMake(-size.width / 2 ,-size.height / 2, size.width ,size.height);
//    return CCRectMake(-70 ,-70, 130 ,130);
}

void Animal::onEnter(){
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}


void Animal::onExit(){
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

bool Animal::containTouchPoint(cocos2d::CCTouch* touch){
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Animal::ccTouchBegan(CCTouch *touch ,CCEvent *event){
    //CCLog("Poker ccTouchBegan ");
    
    if (containTouchPoint(touch))
    {
        event_animalClicked();
        return true;
    }
    
    return false;
}

void Animal::ccTouchMoved(CCTouch *touch ,CCEvent *event){
    //CCLog("Poker ccTouchMoved ");
}


void Animal::ccTouchEnded(CCTouch *touch ,CCEvent *event){
    //CCLog("Poker ccTouchEnded ");
}


float Animal::getAnimalSpeedByLevel(){
    int level=gameLayer->getGameLevel();
    float v=flySpeed[level]*speed;
    return v;
}

int Animal::getHelpScore(){
    return helpScore;
}


int Animal::getHelpLife(){
    return helpLife;
}

int Animal::getLostScore(){
    return lostScore;
}

int Animal::getComboScore(){
    return helpScore+(63%50+1)*63;
}



bool Animal::initUi(){
    return true;
}

//处理动物自己被点击的事件
void Animal::event_animalClicked(){
    //CCLog("animal base ccTouchEnded ");
    
}

//动物点击后的动画
void Animal::animalClicked(){
    //动物被点击后放大，之后缩小
    CCScaleTo* scalebig=CCScaleTo::create(0.1f,1.2f);
    CCScaleTo* scalelittle=CCScaleTo::create(0.1f,1.0f);
    CCFiniteTimeAction* sequence=CCSequence::create(scalebig,scalelittle,NULL);
    this->runAction(sequence);
}

//动物点击满足被解救的条件后，播放动画并消失
void Animal::animalHelpOk(){
    //去掉自己的监听点击事件
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    //播放点击效果
    animalClicked();
    winHelpOkScore();
    gameLayer->updateSumScore(this->helpScore);    
}

void Animal::winHelpOkScore(){
    //播放动物头顶的得分动画
    CCSize size=this->getContentSize();
    
    CCString* strScore=CCString::createWithFormat("%d",helpScore);
    
    CCLabelTTF* helpScoreItem = CCLabelTTF::create(strScore->m_sString.c_str(), "Arial", 20);
    helpScoreItem->setColor(ccc3(23,0,0));
    helpScoreItem->setPosition(ccp(size.width/2,size.height/2+50));
    this->addChild(helpScoreItem, 1);
    
    
    //先显示分数，然后播放放大效果动画
    
    CCMoveBy* moveOut=CCMoveBy::create(1.0f,ccp(0,100));
    CCScaleTo* scalebig=CCScaleTo::create(0.5f,3.0f);
    CCFiniteTimeAction* helpScoreSequence1=CCSequence::create(moveOut,scalebig,NULL);
    
    CCActionInterval* fadeout = CCFadeOut::create(1.5f);
    CCFiniteTimeAction* helpScoreSequence2=CCSequence::create(fadeout,NULL);
    CCSpawn* itemSpawn=CCSpawn::create(helpScoreSequence1,helpScoreSequence2);
    helpScoreItem->runAction(itemSpawn);
}

void Animal::removeAnimal(cocos2d::CCNode *pNode){
    
}
