//
//  Animal.cpp
//  HelpAnimal
//
//  Created by lly on 14-7-31.
//
//

#include "Animal02.h"


Animal02::Animal02(GameLayer* game)
{
    gameLayer=game;
    helpScore=100;
    lostScore=1;
    helpLife=1;
    //动物的飞行速度系数
    speed=1.4;
}


Animal02::~Animal02(void)
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


Animal02* Animal02::create(GameLayer* gameLayer){
	Animal02* m=new Animal02(gameLayer);
    if(m&&m->initUi()){
        return m;
    }

        CC_SAFE_DELETE(m);
        return NULL;
}


bool Animal02::initUi(){
    bool bRet=false;
    do{
        CC_BREAK_IF(!this->initWithFile("02.png"));
        bRet=true;
    }while (0);
    
    return true;
}

void Animal02::event_animalClicked(){
    helpLife--;

    if (helpLife>0) {
        //播放被点击的声音
        animalClicked();
    }else{
        //解救成功，播放动画，删除自己
        animalHelpOk();
    }
}

void Animal02::animalClicked(){
    Animal::animalClicked();
}

void Animal02::animalHelpOk(){
    //解救成功，调用基类更新sumsorce，总分数。
    Animal::animalHelpOk();
    //动物延迟消失
    
    CCActionInterval* animalFadeout = CCFadeOut::create(1.3f);
    CCDelayTime* delayChange=CCDelayTime::create(0.2f);
    CCCallFunc* showAD=CCCallFunc::create(this,callfunc_selector(Animal02::removeAnimal));
    CCFiniteTimeAction* animalGoSequence=CCSequence::create(animalFadeout,delayChange,showAD,NULL);
    
    this->runAction(animalGoSequence);
}

void Animal02::removeAnimal(cocos2d::CCNode *pNode){
    gameLayer->removeAnimal(ANIMAL02, this);
}



