//
//  GameOverScene.h
//  HelpAnimal
//
//  Created by lly on 14-8-7.
//
//

#ifndef __HelpAnimal__GameOverScene__
#define __HelpAnimal__GameOverScene__

#include "cocos2d.h"
#include "GameLayerScene.h"
USING_NS_CC;


class GameOverLayer:public CCLayer{
public:
    GameOverLayer();
    GameOverLayer(GameLayer* gameLayer);
    virtual ~GameOverLayer();
    
    static GameOverLayer* create(GameLayer* gameLayer);
    
    virtual bool init();
    
    virtual bool initUi();
    
    static CCScene* scene(GameLayer* gameLayer);
    
    void replayGame();
    
    
    
    
    
private:
    //主调用层的指针，用来在动物类中调用GameLayer的方法，比如销毁动物的方法。从集合中去掉自己。
    GameLayer* gameLayer;
    
    
    CCLabelTTF* gameScoreItem;
    CCLabelTTF* gameTimeItem;
    CCLabelTTF* gameLifeItem;
};
#endif /* defined(__HelpAnimal__GameOverScene__) */
