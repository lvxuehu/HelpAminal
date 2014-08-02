//
//  Animal.h
//  HelpAnimal
//
//  Created by lly on 14-7-30.
//
//

#ifndef HelpAnimal_Animal03_h
#define HelpAnimal_Animal03_h
#include "cocos2d.h"
#include "GameLayerScene.h"
#include "Animal.h"

USING_NS_CC;



class Animal03:public Animal{
public:
    Animal03(GameLayer* gameLayer);
    virtual ~Animal03();
    
    static Animal03* create(GameLayer* gameLayer);
    
    bool initUi();
    
    //处理动物自己被点击的事件
    void event_animalClicked();
    
    //动物点击后的动画
    void animalClicked();
    
    //动物点击满足被解救的条件后，播放动画并消失
    void animalHelpOk();

};



#endif
