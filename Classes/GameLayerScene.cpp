#include "GameLayerScene.h"
#include "cocos2d.h"
#include "Animal01.h"
#include "Animal02.h"
#include "Animal03.h"


GameLayer::GameLayer(){
    gameStartTime=0.0;
    gameLevel=1;
	sumScore=0;
    isAlive=true;
    sumScoreItem=NULL;
    m_pAllAnimal1=CCArray::create();
    m_pAllAnimal1->retain();
    m_pAllAnimal2=CCArray::create();
    m_pAllAnimal2->retain();
    m_pAllAnimal3=CCArray::create();
    m_pAllAnimal3->retain();
}

GameLayer::~GameLayer(){
    m_pAllAnimal1->release();
    m_pAllAnimal1=NULL;
    m_pAllAnimal2->release();
    m_pAllAnimal2=NULL;
    m_pAllAnimal3->release();
    m_pAllAnimal3=NULL;
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
        initUI();
        initAnimal();
        
        //addAnimal1(2.0);
        
        //addAnimal1(2.0);
        
        this->schedule(schedule_selector(GameLayer::addAnimal1),2.0f);//循环的加入敌机1，每隔0.5秒
		this->schedule(schedule_selector(GameLayer::addAnimal2),3.0f);
        this->schedule(schedule_selector(GameLayer::addAnimal3),4.0f);

        
        
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
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    sumScoreItem = CCLabelTTF::create("0", "Arial", 30);
    sumScoreItem->setColor(ccc3(143,146,147));
    sumScoreItem->setPosition(ccp(80,visibleSize.height-50));
    this->addChild(sumScoreItem, 1);

    
    return true;
}

//初始化动物的动画效果
bool GameLayer::initAnimal(){
    //先初始化好所有动物的第一帧；
    //    animal1SpriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png");
    //    animal2SpriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png");
    
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* background=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
    background->setPosition(ccp(winSize.width/2,winSize.height/2));
    this->addChild(background);
    
    
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


/************************************************************************/
// 游戏每一帧的控制
//根据游戏事件，设置游戏的难度等级
/************************************************************************/
void GameLayer::update(float delta){
    //level=1.2;

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
void GameLayer::addAnimal(AnimalType at)
{
    Animal* animal=NULL;
    switch (at) {
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
    
    switch (at) {
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
    
    CCString* strScore=CCString::createWithFormat("%d",sumScore);
    sumScoreItem->setString(strScore->m_sString.c_str());
    
}
