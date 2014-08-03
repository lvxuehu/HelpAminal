//
//  Animal.h
//  HelpAnimal
//
//  Created by lly on 14-7-30.
//
//

#ifndef HelpAnimal_Animal02_h
#define HelpAnimal_Animal02_h
#include "cocos2d.h"
#include "GameLayerScene.h"
#include "Animal.h"

USING_NS_CC;



class Animal02:public Animal{
public:
    Animal02(GameLayer* gameLayer);
    virtual ~Animal02();
    
    static Animal02* create(GameLayer* gameLayer);
    
    bool initUi();
    
    //处理动物自己被点击的事件
    void event_animalClicked();
    
    //动物点击后的动画
    void animalClicked();
    
    //动物点击满足被解救的条件后，播放动画并消失
    void animalHelpOk();
    
    //动物被解救后，移除。
    void removeAnimal(CCNode* pNode);

};



#endif
