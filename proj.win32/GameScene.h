#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "Poker.h"
USING_NS_CC;

class GameScene :
	public CCLayer
{
public:
	GameScene();
	~GameScene();
    virtual bool init();  
	static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    
	bool initPlayers();
	bool initPokers();
	void checkPokers();
	void dealPokers();
	void dealPokerCallback(CCObject* sender);

	void pass();
	void setLandLord();

	void movePokerTo(Player* src,Player* dest,int index = -1);
	void sortPokers(CCArray* pks);

	CCArray* getPokersByCly(CCArray* pks,PokerClass cly,int num=1,int low=0,bool caipai = true);
	CCArray* getDanZhangs(CCArray* pks,int low = 0);
	CCArray* getDuiZis(CCArray* pks,int num = DUIZI,int low = 0);
	CCArray* getPokersFromArray(CCArray* pks,int num = 1,bool fromTop=true);
	OutData analyPokers(CCArray* pks);
	PokerClass analyPaixing(CCArray* pks,bool re = false); 
	bool isYiLian(CCArray* pks,int num=0);
	virtual bool ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch,CCEvent* pEvent);
	void update(float dt);
	CC_SYNTHESIZE(OutData,roundData,RoundData);
	CREATE_FUNC(GameScene);
private:
	Player* player;
	Player* npcOne;
	Player* npcTwo;
	Player* frontOne;
	Player* frontTwo;
	Player* frontThree;
	Player* deck;
	
	PokerClass paixing;
	CCArray* pokers;
	CCArray* players;
	int turnCount;
	float turnTime;
	bool isDealing;
	bool isCalling;
	int callCount;
	int roundCount;

	OutData outData;
	
	CCLabelTTF* timer;
};

