#ifndef _CONTROLLAYER_H_
#define _CONTROLLAYER_H_
#include "cocos2d.h"
#include "NoTouchLayer.h"


USING_NS_CC;

//enum {
//    kTagTileMap = 1,
//    kTagSpriteManager = 1,
//    kTagAnimation1 = 1,
//    kTagBitmapAtlas1 = 1,
//    kTagBitmapAtlas2 = 2,
//    kTagBitmapAtlas3 = 3,
//};

enum {
    tag_startGame,
    tag_stopGame,
    tag_coin,
    tag_coinScore,
    tag_score,
};

class ControlLayer:public CCLayer
{
public:
	ControlLayer(void);
	~ControlLayer(void);

	virtual bool init();
	CREATE_FUNC(ControlLayer);

	void menuPauseCallback(CCObject* pSender);
    void menuExitCallback(CCObject* pSender);
	void updateScore(int score);

public:

    
	NoTouchLayer* noTouchLayer;//暂停后的屏蔽层
};



#endif





