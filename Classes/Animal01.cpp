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
    speed=1.2;
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
//    CCLog("animal01 ccTouchEnded ");
    helpLife--;
//    CCLog("helpLife=%d",helpLife);

    if (helpLife>0) {
        //播放被点击的声音
        animalClicked();
    }else{
        //解救成功，播放动画，删除自己
        animalHelpOk();
    }
}

void Animal01::animalClicked(){
    //动物被点击后放大，之后缩小
    CCScaleTo* scalebig=CCScaleTo::create(0.1f,1.2f);
    CCScaleTo* scalelittle=CCScaleTo::create(0.1f,1.0f);
    CCFiniteTimeAction* sequence=CCSequence::create(scalebig,scalelittle,NULL);
    this->runAction(sequence);
    
    
}

void Animal01::animalHelpOk(){
    animalClicked();
    Animal::animalHelpOk();
    gameLayer->removeAnimal(ANIMAL01, this);
}



