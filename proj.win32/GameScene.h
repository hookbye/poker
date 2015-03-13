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

	//获得牌型                        src         类型     最小值   最小值
	CCArray* getPokersByCly(CCArray* pks,PokerClass cly,int num=1,int low=0,bool caipai = true);
	CCArray* getDanZhangs(CCArray* pks);
	CCArray* getDuiZis(CCArray* pks);
	CCArray* getSanTiaos(CCArray* pks);
	 
	virtual bool ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch,CCEvent* pEvent);
	void update(float dt);
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
	int round;
	
	CCLabelTTF* timer;
};

