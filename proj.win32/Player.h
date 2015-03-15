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
	CC_SYNTHESIZE(GameScene*,gameMain,GameMain);
	CC_SYNTHESIZE(bool,isLord,IsLord);
	CC_SYNTHESIZE(int,callScore,CallScore);
	void setStatus(PlayerStatus st);
	void clearCards();
	void resetPokers();
	void getOuts();
	void outPokers();
	PlayerStatus getStatus(){return status;}
	void genPai(OutData round);
	CCArray* randomOut(PokerClass &cly);
private:
	 ;
	PlayerStatus status;
	CCMenu* turnMenu;
	CCMenu* callMenu;
};

