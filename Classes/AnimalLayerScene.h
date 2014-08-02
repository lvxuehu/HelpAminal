//
//  AnimalLayerScene.h
//  HelpAnimal
//
//  Created by lly on 14-7-31.
//
//

#ifndef HelpAnimal_AnimalLayerScene_h
#define HelpAnimal_AnimalLayerScene_h
#include "cocos2d.h"
#include "Animal.h"

USING_NS_CC;

//拯救不同动物的分数
const int ANIMAL1_HELP_SCORE=100;
const int ANIMAL2_HELP_SCORE=600;
const int ANIMAL3_HELP_SCORE=3000;

//拯救不同动物需要点击次数
const int ANIMAL1_HELP_LIFE=1;
const int ANIMAL2_HELP_LIFE=2;
const int ANIMAL3_HELP_LIFE=3;


//丢失不同动物的要扣的玩家红心量，以半个为单位，玩家总共3个心，6积分
const int ANIMAL1_LOST_SCORE=1;
const int ANIMAL2_LOST_SCORE=2;
const int ANIMAL3_LOST_SCORE=3;


class AnimalLayer:public CCLayer{
public:
	AnimalLayer();
	~AnimalLayer();
    
	virtual bool init();
    
        
    static CCScene* scene();
    
	CREATE_FUNC(AnimalLayer);
    
    //添加动物
    void addAnimal1(float dt);
	//动物飞出顶端后的处理方法
    void animal1MoveFinished(CCNode* pSender);
    //销毁动物的方法，在动物飞出屏幕或者拯救成功后调用
    void removeAnimal(CCNode* pTarget, void* data);
    
    //添加动物
    void addAnimal2(float dt);
	//动物飞出顶端后的处理方法
    void animal2MoveFinished(CCNode* pSender);
    //销毁动物的方法，在动物飞出屏幕或者拯救成功后调用
    //void removeAnimal(CCNode* pTarget, void* data);


    
    

    
    
public:
    bool isAlive;
    CCArray* m_pAllAnimal;
    
private:
    CCSpriteFrame* animal1SpriteFrame;
    CCSpriteFrame* animal2SpriteFrame;
   
};

#endif
