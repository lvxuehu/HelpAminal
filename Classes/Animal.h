//
//  Animal.h
//  HelpAnimal
//
//  Created by lly on 14-7-30.
//
//
#ifndef HelpAnimal_Animal_h
#define HelpAnimal_Animal_h
#include "cocos2d.h"
#include "GameLayerScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

//拯救不同动物的分数
const int ANIMAL1_HELP_SCORE=100;
const int ANIMAL2_HELP_SCORE=100;
const int ANIMAL3_HELP_SCORE=100;

//拯救不同BOSS动物的分数
const int BOSS1_HELP_SCORE=1000;
const int BOSS2_HELP_SCORE=1000;

//拯救不同动物需要点击次数
//animal1表示普通动物
const int ANIMAL1_HELP_LIFE=1;
const int ANIMAL2_HELP_LIFE=2;
const int ANIMAL3_HELP_LIFE=3;

//拯救不同BOSS动物需要点击次数
//animal1表示普通动物
const int BOSS1_HELP_LIFE=5;
const int BOSS2_HELP_LIFE=6;
const int BOSS3_HELP_LIFE=7;


//丢失不同动物的要扣的玩家红心量，以半个为单位，玩家总共3个心，6积分
const int ANIMAL1_LOST_SCORE=1;
const int ANIMAL2_LOST_SCORE=1;
//BOSS丢失的红心数
const int BOSS1_LOST_SCORE=2;

//每一个游戏难度下动物的全局飞行速度，数值越小，飞的越快。
//数组的下标就是游戏难度，比如gamelevel=1时，flyspeed=flyspeed[1]=10；
//每种动物都有自己的飞行速度，因此动物在每个难度下的真实飞行速度是speed=anminalSpeed*flyspeed[gameLevel]；
const float flySpeed[10]={10,9,8,7,6,5,4,3,2,1};




class Animal:public CCSprite,public CCTargetedTouchDelegate{
public:
    Animal();
    Animal(GameLayer* gameLayer);
    virtual ~Animal();
    
    
    CCRect rect();
    void onEnter();
    void onExit();
    
    bool containTouchPoint(cocos2d::CCTouch* touch);
    
    bool ccTouchBegan(CCTouch *touch ,CCEvent *event);
    void ccTouchMoved(CCTouch *touch ,CCEvent *event);
    void ccTouchEnded(CCTouch *touch ,CCEvent *event);
    
    
    int getHelpScore();
    
    int getHelpLife();
    
    int getLostScore();
    
    int getComboScore();
    
    
    
    //根据当前的游戏难度得到动物上升的速度
    float getAnimalSpeedByLevel();
    
    //动物摇晃的方法
    bool animalShaky();
    
    
    /////////需要子类自己实现的方法///////////////
    
    
    //初始化动物的样子
    virtual bool initUi();
    
    //处理动物自己被点击的事件
    virtual void event_animalClicked();
    
    //动物点击后的动画
    virtual void animalClicked();
    
    //动物点击满足被解救的条件后，播放动画并消失
    virtual void animalHelpOk();
    
    //动物解救成功后，头部播放获得积分的效果
    virtual void winHelpOkScore();
    
    //动物被解救后，移除。
    virtual void removeAnimal(CCNode* pNode);
    


protected:
    //动物的飞行速度系数，取值范围1~2之间，动物的飞行时间为 speed*flySpeed[gameLevel]
    float speed;
    //拯救动物获得的积分
    int helpScore;
    //动物点击N次才能被拯救
    int helpLife;
    
    //动物如果被抓玩家失去的红心点数
    int lostScore;
    //主调用层的指针，用来在动物类中调用GameLayer的方法，比如销毁动物的方法。从集合中去掉自己。
    GameLayer* gameLayer;

    
    
    
    
};



#endif
