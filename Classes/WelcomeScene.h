#ifndef _WELCOMELAYER_H_
#define _WELCOMELAYER_H_
#include "cocos2d.h"

USING_NS_CC;


class WelcomeLayer:public CCLayer
{
public:
	WelcomeLayer(void);
	~WelcomeLayer(void);

	CREATE_FUNC(WelcomeLayer);
	virtual bool init();

    static CCScene* scene();
    
	void loadingDone(CCNode *pNode);
	virtual void keyBackClicked();
	bool isHaveSaveFile();

    void preloadMusic();
    
	void getHighestHistorySorce();
    
    void menuStartGameCallback(CCObject* pSender);
    
    void menuMusicGameCallback(CCObject* pSender);
    
public:

    
    //是否播放背景音乐
    bool ifPlayBkMusic;
};



#endif


