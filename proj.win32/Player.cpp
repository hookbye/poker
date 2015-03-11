#include "Player.h"
#include "Poker.h"

Player::Player(void)
{
	pokers = CCArray::create();
	pokers->retain();
}


Player::~Player(void)
{
	CC_SAFE_RELEASE(pokers);
}

void Player::updatePokerLoc()
{
	int count = pokers->count();
	if(count < 1)
		return;
	int x = -((count-1)*PokerB+PokerW)/2,y = PokerH;

	Poker* pk;
	for(int i=0;i<count;i++)
	{
		Poker* pk = (Poker*)pokers->objectAtIndex(i);
		pk->removeFromParent();
		switch (type)
		{
		case DECK:
			pk->setPosition(ccp(0,0));
			//pk->setBack();
			break;
		case PLAYER:
		case NPC:
		default:
			pk->setPosition(ccp(x+i*PokerB,y));
			break;
		}
		addChild(pk);
	}
}
