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
    CREATE_FUNC(GameScene);
private:
	Player* player;
	Player* npcOne;
	Player* npcTwo;

	Player* deck;
	
	CCArray* pokers;
};

