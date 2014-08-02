#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_


#include "cocos2d.h"

USING_NS_CC;

//动物的种类
enum AnimalType{
    ANIMAL01,
    ANIMAL02,
    ANIMAL03,
};


class GameLayer:public CCLayer{
public:
	GameLayer();
	virtual ~GameLayer();

	virtual bool init();
    
    virtual bool initSound();
    virtual bool initUI();
    virtual bool initAnimal();
    
    
    static CCScene* scene();

	CREATE_FUNC(GameLayer);

	
	void update(float delta);

    //得到当前游戏的等级
	int getGameLevel();
    void updateSumScore(int score);
    
    
    
    //添加动物1
    void addAnimal1(float dt);
	//动物飞出顶端后的处理方法1
    void animal1MoveFinished(CCNode* pSender);
    
    //添加动物2
    void addAnimal2(float dt);
	//动物飞出顶端后的处理方法2
    void animal2MoveFinished(CCNode* pSender);
    
    //添加动物3
    void addAnimal3(float dt);
	//动物飞出顶端后的处理方法3
    void animal3MoveFinished(CCNode* pSender);
    
    //添加动物1
    void addAnimal(AnimalType at);
    
    //销毁动物的方法，在动物飞出屏幕或者拯救成功后调用
    void removeAnimal(AnimalType at, void* data);

    
    
private:
    //主角是否活着
    bool isAlive;
    //用来存放动物的集合
    CCArray* m_pAllAnimal1;
    CCArray* m_pAllAnimal2;
    CCArray* m_pAllAnimal3;
    
    //游戏的开始时间
    long gameStartTime;
    //游戏的当前等级
    int gameLevel;
    //游戏的总得分，玩家得分
    int sumScore;
    
    //用来显示总分数的对象；
    CCLabelTTF* sumScoreItem;
    
};





#endif //_GAMELAYER_H_