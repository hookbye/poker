#pragma once
#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class Player :
	public CCNode
{
public:
	Player(void);
	~Player(void);
	void updatePokerLoc();
	CREATE_FUNC(Player);
	CC_SYNTHESIZE(CCArray*,pokers,Pokers);
	CC_SYNTHESIZE(PlayerType,type,Type);
	 
};

