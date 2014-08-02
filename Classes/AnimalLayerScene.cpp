//
//  AnimalLayerScene.cpp
//  HelpAnimal
//
//  Created by lly on 14-7-31.
//
//

#include "AnimalLayerScene.h"
#include "GameLayerScene.h"
#include "Animal01.h"


AnimalLayer::AnimalLayer(){
    animal1SpriteFrame=NULL;
    animal2SpriteFrame=NULL;
    
    isAlive=true;
    m_pAllAnimal=CCArray::create();
    m_pAllAnimal->retain();
    
}

AnimalLayer::~AnimalLayer(){
    m_pAllAnimal->release();
    m_pAllAnimal=NULL;
}

bool AnimalLayer::init(){
    bool bRet=false;
    do{
        CC_BREAK_IF(!CCLayer::init());
        
                
                

        this->schedule(schedule_selector(AnimalLayer::addAnimal1),2.0f);//循环的加入敌机1，每隔0.5秒
		this->schedule(schedule_selector(AnimalLayer::addAnimal2),3.0f);
        
        
        
        bRet=true;
    }while (0);
    return bRet;
}


//向屏幕添加动物1
void AnimalLayer::addAnimal1(float dt)
{
	//Animal* animal=Animal::create("enemy1.png",ANIMAL1_HELP_LIFE,ANIMAL1_HELP_SCORE,ANIMAL1_LOST_SCORE);
    Animal01* animal=Animal01::create(this);

	CCSize animalSize=animal->getContentSize();
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int minX=animalSize.width/2;
	int maxX=winSize.width-animalSize.width/2;
	int rangeX=maxX-minX;
	int actualX=(rand()%rangeX)+minX;//随机生成动物出现的x值
    
	animal->setPosition(ccp(actualX,0-animalSize.height/2));//将动物出现的位置设置在x轴下端
//    animal->setPosition(ccp(200,200));//将动物出现的位置设置在x轴下端
	this->addChild(animal);
	this->m_pAllAnimal->addObject(animal);
    
    int gameLevel=getGameLevel();
    float v=getGameV();
	
    float actualDuration=v/gameLevel;//10/1,10/2
    
	CCFiniteTimeAction* actionMove=CCMoveTo::create(actualDuration,ccp(actualX,winSize.height+animalSize.height/2));
	CCFiniteTimeAction* actionDone=CCCallFuncN::create(this,callfuncN_selector(AnimalLayer::animal1MoveFinished));
    
	CCSequence* sequence=CCSequence::create(actionMove,actionDone,NULL);
	animal->runAction(sequence);
    
}


//向屏幕添加动物1
void AnimalLayer::addAnimal2(float dt)
{
	//Animal* animal=Animal::create("enemy1.png",ANIMAL1_HELP_LIFE,ANIMAL1_HELP_SCORE,ANIMAL1_LOST_SCORE);
    Animal01* animal=Animal01::create();
    
	CCSize animalSize=animal->getContentSize();
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int minX=animalSize.width/2;
	int maxX=winSize.width-animalSize.width/2;
	int rangeX=maxX-minX;
	int actualX=(rand()%rangeX)+minX;//随机生成敌机出现的x值
    
	animal->setPosition(ccp(actualX,0-animalSize.height/2));//将动物出现的位置设置在x轴下端
	this->addChild(animal);
	this->m_pAllAnimal->addObject(animal);
    
	//float minDuration,maxDuration;//速度
    int gameLevel=GameLayer::getGameLevel();
    float v=GameLayer::getGameV();
	
	//int rangeDuration=maxDuration-minDuration;
	//int actualDuration=(rand()%rangeDuration)+minDuration;//随机生成速度
    float actualDuration=v/gameLevel;//10/1,10/2
    
	CCFiniteTimeAction* actionMove=CCMoveTo::create(actualDuration,ccp(actualX,winSize.height+animalSize.height/2));
	CCFiniteTimeAction* actionDone=CCCallFuncN::create(this,callfuncN_selector(AnimalLayer::animal2MoveFinished));
    
	CCSequence* sequence=CCSequence::create(actionMove,actionDone,NULL);
	animal->runAction(sequence);
    
}


//动物飞出界面后的处理
void AnimalLayer::animal1MoveFinished(CCNode* pSender)
{
	removeAnimal(NULL, pSender);
}

//动物飞出界面后的处理
void AnimalLayer::animal2MoveFinished(CCNode* pSender)
{
	removeAnimal(NULL, pSender);
}



//移除动物的方法
void AnimalLayer::removeAnimal(CCNode* pTarget, void* data)
{
	Animal* anima=(Animal*)data;
	if (anima!=NULL)
	{
		m_pAllAnimal->removeObject(anima);
		this->removeChild(anima,true);
	}
}

