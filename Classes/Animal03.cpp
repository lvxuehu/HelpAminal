//
//  Animal.cpp
//  HelpAnimal
//
//  Created by lly on 14-7-31.
//
//

#include "Animal03.h"


Animal03::Animal03(GameLayer* game)
{
    gameLayer=game;
    helpScore=300;
    lostScore=3;
    helpLife=3;
    //动物的飞行速度系数
    speed=1.2;
}


Animal03::~Animal03(void)
{
}



Animal03* Animal03::create(GameLayer* gameLayer){
	Animal03* m=new Animal03(gameLayer);
    if(m&&m->initUi()){
//    if(m&&m->initWithFile("enemy1.png")){
        return m;
    }

        CC_SAFE_DELETE(m);
        return NULL;
}


bool Animal03::initUi(){
    bool bRet=false;
    do{
        CC_BREAK_IF(!this->initWithFile("03.png"));
        bRet=true;
    }while (0);
    
    return true;
}

void Animal03::event_animalClicked(){
    helpLife--;

    if (helpLife>0) {
        //播放被点击的声音
        animalClicked();
    }else{
        //解救成功，播放动画，删除自己
        animalHelpOk();
    }
}

void Animal03::animalClicked(){
   Animal::animalClicked();
    
    
}

void Animal03::animalHelpOk(){
    //解救成功，调用基类更新sumsorce，总分数。
    Animal::animalHelpOk();
    //动物延迟消失
    
    CCActionInterval* animalFadeout = CCFadeOut::create(1.3f);
    CCDelayTime* delayChange=CCDelayTime::create(0.2f);
    CCCallFunc* showAD=CCCallFunc::create(this,callfunc_selector(Animal03::removeAnimal));
    CCFiniteTimeAction* animalGoSequence=CCSequence::create(animalFadeout,delayChange,showAD,NULL);
    
    this->runAction(animalGoSequence);
}

void Animal03::removeAnimal(cocos2d::CCNode *pNode){
    gameLayer->removeAnimal(ANIMAL03, this);
}



