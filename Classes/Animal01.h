//
//  Animal.h
//  HelpAnimal
//
//  Created by lly on 14-7-30.
//
//

#ifndef HelpAnimal_Animal01_h
#define HelpAnimal_Animal01_h
#include "cocos2d.h"
#include "GameLayerScene.h"
#include "Animal.h"

USING_NS_CC;



class Animal01:public Animal{
public:
    Animal01(GameLayer* gameLayer);
    virtual ~Animal01();
    
    static Animal01* create(GameLayer* gameLayer);
    
    bool initUi();
    
    //处理动物自己被点击的事件
    void event_animalClicked();
    
    //动物点击后的动画
    void animalClicked();
    
    //动物点击满足被解救的条件后，播放动画并消失
    void animalHelpOk();

};



#endif
