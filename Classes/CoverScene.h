//
//  CoverScene.h
//  HelpAnimal
//
//  Created by lly on 14-8-31.
//
//

#ifndef __HelpAnimal__CoverScene__
#define __HelpAnimal__CoverScene__

#include "cocos2d.h"

USING_NS_CC;

class CoverLayer:public CCLayer{
public:
    CoverLayer(void);
    ~CoverLayer(void);
    
    CREATE_FUNC(CoverLayer);
    
    static CCScene* scene();
    
    virtual bool init();
    
    void startWelcomeScene(CCObject* object);
};

#endif /* defined(__HelpAnimal__CoverScene__) */
