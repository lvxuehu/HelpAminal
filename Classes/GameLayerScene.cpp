#include "GameLayerScene.h"
#include "cocos2d.h"
#include "Animal01.h"
#include "Animal02.h"
#include "Animal03.h"


GameLayer::GameLayer(){
    timer=0;
    gameLevel=1;
	sumScore=0;
    isAlive=true;
    animalTypeCount=3;
    bossTypeCount=3;
    sumScoreItem=NULL;
    gameLevelItem=NULL;
    m_pAllAnimal1=CCArray::create();
    m_pAllAnimal1->retain();
    m_pAllAnimal2=CCArray::create();
    m_pAllAnimal2->retain();
    m_pAllAnimal3=CCArray::create();
    m_pAllAnimal3->retain();
    
    m_pAllBossAnimal1=CCArray::create();
    m_pAllBossAnimal1->retain();
    
}

GameLayer::~GameLayer(){
    m_pAllAnimal1->release();
    m_pAllAnimal1=NULL;
    m_pAllAnimal2->release();
    m_pAllAnimal2=NULL;
    m_pAllAnimal3->release();
    m_pAllAnimal3=NULL;
    
    m_pAllBossAnimal1->release();
    m_pAllBossAnimal1=NULL;
}


CCScene* GameLayer::scene(){
    CCScene* scene=CCScene::create();
    GameLayer* gameLayer=GameLayer::create();
    scene->addChild(gameLayer);
    return scene;
}

bool GameLayer::init(){
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
        
        initSound();
        initImage();
        initUI();
        initAnimal();
        
		//触发update方法
		this->scheduleUpdate();

		bRet=true;

	} while (0);

	return bRet;
}

//初始化游戏用到的声音元素
bool GameLayer::initSound(){
    //在重来一次中使用，如果背景音乐没有播放，则重新播放
    //		if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    //		{
    //			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_music.wav",true);
    //		}
    
    return true;
}

//初始化主游戏的界面
bool GameLayer::initUI(){
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    //初始化背景
    CCSprite* background=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
    //CCLog("siez h=%f",background->getContentSize().height);
    background->setPosition(ccp(winSize.width/2,winSize.height/2));
    this->addChild(background,0);
    
    //加入前景
    CCSprite* frontground=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("grass.png"));
    frontground->setAnchorPoint(ccp(0,0));
    frontground->setPosition(ccp(0,0));
    this->addChild(frontground,255);
    
    //当前游戏分数
    sumScoreItem = CCLabelTTF::create("积分:0", "Arial", 30);
    sumScoreItem->setColor(ccc3(0,0,0));
    sumScoreItem->setPosition(ccp(80,visibleSize.height-50));
    this->addChild(sumScoreItem, 1);
    
    //当前游戏等级
    gameLevelItem = CCLabelTTF::create("游戏等级:1", "Arial", 30);
    gameLevelItem->setColor(ccc3(0,0,0));
    gameLevelItem->setPosition(ccp(sumScoreItem->getPositionX()+sumScoreItem->getContentSize().width+80,visibleSize.height-50));
    this->addChild(gameLevelItem, 1);
    
    
    //当前游戏运行时间
    gameTimerItem = CCLabelTTF::create("游戏时间:0", "Arial", 30);
    gameTimerItem->setColor(ccc3(0,0,0));
    gameTimerItem->setPosition(ccp(gameLevelItem->getPositionX()+gameLevelItem->getContentSize().width+20,visibleSize.height-50));
    this->addChild(gameTimerItem, 1);


    
    return true;
}

bool GameLayer::initImage(){
    //先初始化好所有动物的第一帧；
    //    animal1SpriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png");
    //    animal2SpriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png");
    
    //缓存点击的动画
    CCAnimation* animationClicked1=CCAnimation::create();
    animationClicked1->setDelayPerUnit(0.1f);
    animationClicked1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
    animationClicked1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
    animationClicked1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
    animationClicked1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));
    
    //缓存解救成功的动画
    CCAnimation* animationHelpOk1=CCAnimation::create();
    animationHelpOk1->setDelayPerUnit(0.1f);
    animationHelpOk1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
    animationHelpOk1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
    animationHelpOk1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
    animationHelpOk1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));
    
    //缓存解救成功的动画
    CCAnimation* animationLost1=CCAnimation::create();
    animationLost1->setDelayPerUnit(0.1f);
    animationLost1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
    animationLost1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
    animationLost1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
    animationLost1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));
    
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(animationClicked1,"Enemy1Blowup");//把初始化好的动画缓存起来
    CCAnimationCache::sharedAnimationCache()->addAnimation(animationHelpOk1,"Enemy2Blowup");
    CCAnimationCache::sharedAnimationCache()->addAnimation(animationLost1,"Enemy2Blowup");
    
    
    return true;
}

//初始化游戏
bool GameLayer::initAnimal(){
    //增加一个1秒钟一次的定时器，用来计时，设置游戏的当前等级。
    this->schedule(schedule_selector(GameLayer::updateGameLevel),2.0f);
    this->schedule(schedule_selector(GameLayer::addAnimal),periodByLevel[0]);
//    this->schedule(schedule_selector(GameLayer::addAnimal2),3.0f);//加入boss的定时器
//    this->schedule(schedule_selector(GameLayer::addAnimal3),4.0f);
    return true;
}


/************************************************************************/
// 游戏每一帧的控制
//根据游戏事件，设置游戏的难度等级
/************************************************************************/
void GameLayer::update(float delta){
    

}


void GameLayer::addAnimal1(float dt){
    addAnimal(ANIMAL01);
}

void GameLayer::addAnimal2(float dt){
    addAnimal(ANIMAL02);
}

void GameLayer::addAnimal3(float dt){
    addAnimal(ANIMAL03);
}



//向屏幕添加动物1
void GameLayer::addAnimal(float dt)
{
    //随机添加动物
    srand((unsigned)time(NULL));
    int r1=rand();
    int aimal=r1%animalTypeCount;
    
    
    Animal* animal=NULL;
    switch (aimal) {
        case ANIMAL01:
            animal=Animal01::create(this);
            break;
        case ANIMAL02:
            animal=Animal02::create(this);
            break;
        case ANIMAL03:
            animal=Animal03::create(this);
            break;
        default:
            break;
    }
    
	CCSize animalSize=animal->getContentSize();
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int minX=animalSize.width/2;
	int maxX=winSize.width-animalSize.width/2;
	int rangeX=maxX-minX;
    srand((unsigned)time(NULL));
    int r=rand();
	int actualX=(r%rangeX)+minX;//随机生成动物出现的x值
    
	animal->setPosition(ccp(actualX,0-animalSize.height/2));//将动物出现的位置设置在x轴下端
	this->addChild(animal);
    
    
    
	//得到动物的上升速度
    float actualDuration=animal->getAnimalSpeedByLevel();
    
	CCFiniteTimeAction* actionMove=CCMoveTo::create(actualDuration,ccp(actualX,winSize.height+animalSize.height/2));
	
    CCFiniteTimeAction* actionDone=NULL;
    
    switch (aimal) {
        case ANIMAL01:
            this->m_pAllAnimal1->addObject(animal);
            actionDone=CCCallFuncN::create(this,callfuncN_selector(GameLayer::animal1MoveFinished));
            break;
        case ANIMAL02:
            this->m_pAllAnimal2->addObject(animal);
            actionDone=CCCallFuncN::create(this,callfuncN_selector(GameLayer::animal2MoveFinished));
            break;
        case ANIMAL03:
            this->m_pAllAnimal3->addObject(animal);
            actionDone=CCCallFuncN::create(this,callfuncN_selector(GameLayer::animal3MoveFinished));
            break;
        default:
            break;
    }
    
	CCSequence* sequence=CCSequence::create(actionMove,actionDone,NULL);
	animal->runAction(sequence);
    
}





//动物飞出界面后的处理1
void GameLayer::animal1MoveFinished(CCNode* pSender)
{
	removeAnimal(ANIMAL01,pSender);
}

//动物飞出界面后的处理2
void GameLayer::animal2MoveFinished(CCNode* pSender)
{
	removeAnimal(ANIMAL02,pSender);
}

//动物飞出界面后的处理3
void GameLayer::animal3MoveFinished(CCNode* pSender)
{
	removeAnimal(ANIMAL03,pSender);
}


//移除动物的方法
void GameLayer::removeAnimal(AnimalType at, void* data)
{
    Animal* anima=(Animal*)data;
	if (anima!=NULL)
	{
        switch (at) {
            case ANIMAL01:
                m_pAllAnimal1->removeObject(anima);
                break;
            case ANIMAL02:
                m_pAllAnimal2->removeObject(anima);
                break;
            case ANIMAL03:
                m_pAllAnimal3->removeObject(anima);
                break;
            default:
                break;
        }
    
//		CCLog("%d",m_pAllAnimal1->count());
		this->removeChild(anima,true);
	}
}




int GameLayer::getGameLevel(){
	return gameLevel;
}


void GameLayer::updateSumScore(int score){
    sumScore+=score;
    
    CCString* strScore=CCString::createWithFormat("积分:%d",sumScore);
    sumScoreItem->setString(strScore->m_sString.c_str());
    
    //根据sumscore来设定游戏等级，取消，改为根据游戏进行的时间来设定游戏等级；
    
//    if (sumScore>1000&&sumScore<=2000) {
//        updateGameLevel(2);
//        CCLog("game gamelevel=%d",gameLevel);
//    }else if(sumScore>2000&&sumScore<=3000){
//        updateGameLevel(3);
//        CCLog("game gamelevel=%d",gameLevel);
//    }
    
}

//定时器每一秒调用一次这个方法，时间计数器加1，并且根据计数器的值，设定游戏等级
void GameLayer::updateGameLevel(float dt){
    timer++;
    CCString* strTimer=CCString::createWithFormat("游戏时间:%d秒",timer);
    gameTimerItem->setString(strTimer->m_sString.c_str());

    
    //CCLog("timer=%d",timer);
    
    if (timer==timesByLevel[gameLevel-1]) {
        gameLevel+=1;
        CCString* strLevel=CCString::createWithFormat("游戏等级:%d",gameLevel);
        gameLevelItem->setString(strLevel->m_sString.c_str());
        
        //添加动物的定时器，会根据游戏的等级变换定时器周期
        //删除之前的定时器
        this->unschedule(schedule_selector(GameLayer::addAnimal));
        //添加一个新的定时器
        this->schedule(schedule_selector(GameLayer::addAnimal),periodByLevel[gameLevel-1]);
    }
    
    CCLog("timer=%d,gamelevel=%d",timer,gameLevel);
   
}
