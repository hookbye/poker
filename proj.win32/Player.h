#pragma once
#include "cocos2d.h"
#include "Global.h"
class GameScene;
USING_NS_CC;
class Player :
	public CCNode
{
public:
	Player(void);
	~Player(void);
	void sortPokers();
	void updatePokerLoc();

	void menuCallback(CCObject* pSender);
	bool init();
	CREATE_FUNC(Player);
	CC_SYNTHESIZE(CCArray*,pokers,Pokers);
	CC_SYNTHESIZE(CCArray*,outs,Outs);
	CC_SYNTHESIZE(Player*,front,Front);
	CC_SYNTHESIZE(PlayerType,type,Type);
	void setStatus(PlayerStatus st);
	void clearCards();
	PlayerStatus getStatus(){return status;}
private:
	GameScene* gameScene;
	PlayerStatus status;
	CCMenu* turnMenu;
	CCMenu* callMenu;
};

