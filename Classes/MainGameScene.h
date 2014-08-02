//
//  MainGameScene.h
//  HelpAnimal
//
//  Created by lly on 14-7-30.
//
//

#ifndef HelpAnimal_MainGameScene_h
#define HelpAnimal_MainGameScene_h

#include "cocos2d.h"

class MainGameLayer:public cocos2d::CCLayer{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(MainGameLayer);
    
    void startGame(CCObject* object);
};


#endif
