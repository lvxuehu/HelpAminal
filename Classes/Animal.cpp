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



bool Animal::initUi(){
    return true;
}

//处理动物自己被点击的事件
void Animal::event_animalClicked(){
    //CCLog("animal base ccTouchEnded ");
    
}

//动物点击后的动画
void Animal::animalClicked(){
    
}

//动物点击满足被解救的条件后，播放动画并消失
void Animal::animalHelpOk(){
    gameLayer->updateSumScore(this->helpScore);
}
