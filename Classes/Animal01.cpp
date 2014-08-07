//
//  Animal.cpp
//  HelpAnimal
//
//  Created by lly on 14-7-31.
//
//

#include "Animal01.h"


Animal01::Animal01(GameLayer* game)
{
    gameLayer=game;
    helpScore=100;
    lostScore=1;
    helpLife=1;
    //动物的飞行速度系数
    speed=1.1;
}


Animal01::~Animal01(void)
{
}


//降落伞效果
//CCMoveBy* move1=CCMoveBy::create(0.2f,ccp(0,-150));
//CCMoveBy* move2=CCMoveBy::create(0.7f,ccp(0,100));
//CCSequence* upAndDownAction=CCSequence::create(move1,move2,NULL);
//摇摆效果
//p_ufo->setRotation(20);
//CCActionInterval* rotate2=CCRotateBy::create(0.5f,-40);
//CCSequence* rotateSequence=CCSequence::create(rotate2,rotate2->reverse(),NULL);
//p_ufo->runAction(CCRepeatForever::create(rotateSequence));


Animal01* Animal01::create(GameLayer* gameLayer){
	Animal01* m=new Animal01(gameLayer);
    if(m&&m->initUi()){
//    if(m&&m->initWithFile("enemy1.png")){
        return m;
    }

        CC_SAFE_DELETE(m);
        return NULL;
}


bool Animal01::initUi(){
    bool bRet=false;
    do{
        CC_BREAK_IF(!this->initWithFile("01.png"));
        bRet=true;
    }while (0);
    
    return true;
}

void Animal01::event_animalClicked(){
    helpLife--;//动物每被点击一次，拯救分数减一，直到等于0，解救成功；

    if (helpLife>0) {
        //播放被点击的声音
        animalClicked();
    }else{
        //解救成功，播放动画，删除自己
        animalHelpOk();
    }
}

void Animal01::animalClicked(){
    Animal::animalClicked();
}

//解救成功，播放的效果
void Animal01::animalHelpOk(){
    
    //解救成功，调用基类更新sumsorce，总分数。
    Animal::animalHelpOk();
    //动物延迟消失

    CCActionInterval* animalFadeout = CCFadeOut::create(1.3f);
    CCDelayTime* delayChange=CCDelayTime::create(0.2f);
    CCCallFunc* showAD=CCCallFunc::create(this,callfunc_selector(Animal01::removeAnimal));
    CCFiniteTimeAction* animalGoSequence=CCSequence::create(animalFadeout,delayChange,showAD,NULL);
    
    this->runAction(animalGoSequence);
    
}

void Animal01::removeAnimal(CCNode* pNode){
    gameLayer->removeAnimal(ANIMAL01, this);
}



