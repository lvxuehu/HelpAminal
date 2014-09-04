#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_


#include "cocos2d.h"
#include "cocos-ext.h"
#include "NoTouchLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

//动物的种类
//修改动物的类型是必须修改以下值
//int animalTypeCount=3;
//int bossTypeCount=3;
enum AnimalType{
    ANIMAL01,
    ANIMAL02,
    ANIMAL03,
};

//Boss的种类
enum BossType{
    BOSS01,
    BOSS02,
    BOSS03,
};


//每一级游戏难度结束的累计秒数，比如：第一级累计到10秒，第二级累计到15秒，等等
const float timesByLevel[10]={10,15,30,50,60,75,85,100,120,200};
//每一个游戏难度下对应的添加动物的定时器周期，单位秒。
//周期的计算公式：period=每一个难度出现的动物数/(timesByLevel[gamelevel]-timesByLevel[gamelevel-1])。
const float periodByLevel[10]={1.33,1.17,1.25,1.33,1.17,1.23,1.14,1.19,1.24,1.22};


class GameLayer:public CCLayer{
public:
	GameLayer();
	virtual ~GameLayer();
    
	virtual bool init();
    virtual bool initImage();
    virtual bool initSound();
    virtual bool initUI();
    virtual bool initAnimal();
    
    
    static CCScene* scene();

	CREATE_FUNC(GameLayer);

	
	void update(float delta);

    //得到当前游戏的等级
	int getGameLevel();
    
    //得到当前游戏积分
	int getGameScore();
    
    //得到当前游戏的剩余血量
	int getGameLife();
    
    //得到当前游戏执行时间
	int getGameTime();
    
    
    //更新游戏的最新分数显示
    void updateSumScore(int score);
    //更新最新的游戏等级
    void updateGameLevel(float dt);
    
    //更新血量
    void updateGameLife(int life);
    
    
    
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
    
    //添加动物,方法中随机计算添加的动物种类
    void addAnimal(float dt);
    
    //销毁动物的方法，在动物飞出屏幕或者拯救成功后调用
    void removeAnimal(AnimalType at, void* data);
    
    //游戏结束，切换到gameover的场景
    void gameOver();
    //暂停游戏
    void menuPauseCallback(CCObject* pSender);\
    
public:
    //是否播放背景音乐
    bool ifPlayBkMusic;
    
    
private:
    //主角是否活着
    bool isAlive;
    
    
    //修改动物的类型是必须修改以下值
    int animalTypeCount;
    int bossTypeCount;
    
    //用来存放动物
    CCArray* m_pAllAnimal;
    //存放Boss
    CCArray* m_pAllBossAnimal;
    //存放所有炸弹的集合
    CCArray* m_pAllBomb;
    
    
    //游戏时间计数器，每一秒加1，定时器每一秒调用一次。
    int timer;
    //游戏的当前等级,最小为1级
    int gameLevel;
    //游戏的总得分，玩家得分
    int sumScore;
    //玩家当前游戏血量
    int gameLife;
    
    //用来显示总分数的对象；
    CCLabelTTF* sumScoreItem;
    
    //用来显示当前游戏等级对象；
    CCLabelTTF* gameLevelItem;
    
    //用来显示游戏运行时间的对象；
    CCLabelTTF* gameTimerItem;
    
    //用来显示游戏血量的对象；
    CCLabelTTF* gameLifeItem;
    
    //CCMenuItemImage* pPauseItem;//暂停的按钮
    
    //NoTouchLayer* noTouchLayer;
    
};





#endif //_GAMELAYER_H_