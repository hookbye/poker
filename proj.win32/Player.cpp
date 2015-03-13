#include "Player.h"
#include "Poker.h"
#include "GameScene.h"
#include "Tool.h"
Player::Player(void):gameMain(NULL),front(NULL),status(DEALCARD),isLord(false)
{
	pokers = CCArray::create();
	pokers->retain();
	outs = CCArray::create();
	outs->retain();
}

Player::~Player(void)
{
	CC_SAFE_RELEASE(pokers);
	CC_SAFE_RELEASE(outs);
}
bool Player::init()
{
	do
	{
		CC_BREAK_IF(!CCNode::init());
		CCMenuItemFont * oneScore = CCMenuItemFont::create(a2u("1分").c_str(),this,menu_selector(Player::menuCallback));
		oneScore->setTag(1);
		CCMenuItemFont * twoScore = CCMenuItemFont::create(a2u("2分").c_str(),this,menu_selector(Player::menuCallback));
		twoScore->setTag(2);
		CCMenuItemFont * threeScore = CCMenuItemFont::create(a2u("3分").c_str(),this,menu_selector(Player::menuCallback));
		threeScore->setTag(3);
		CCMenuItemFont * notCall = CCMenuItemFont::create(a2u("不叫").c_str(),this,menu_selector(Player::menuCallback));
		notCall->setTag(0);
		CCArray* menuItems = CCArray::create(oneScore,twoScore,threeScore,notCall,NULL); 
		callMenu = CCMenu::createWithArray(menuItems);
		callMenu->alignItemsHorizontallyWithPadding(5.0f);
		callMenu->setPosition(0,PokerH*1.5);
		addChild(callMenu);
		//callMenu->setVisible(false);
		menuItems->release();

		CCMenuItemFont * outCard = CCMenuItemFont::create(a2u("出牌").c_str(),this,menu_selector(Player::menuCallback));
		outCard->setTag(4);
		CCMenuItemFont * pass = CCMenuItemFont::create(a2u("不出").c_str(),this,menu_selector(Player::menuCallback));
		pass->setTag(5);
		menuItems = CCArray::create(outCard,pass,NULL); 
		turnMenu = CCMenu::createWithArray(menuItems);
		turnMenu->alignItemsHorizontallyWithPadding(5.0f);
		turnMenu->setPosition(0,PokerH*1.5);
		addChild(turnMenu);
		/*turnMenu->setVisible(false);*/
		menuItems->release();
		setStatus(status);
		return true;
	}while(0);
	return false;
}
void Player::menuCallback(CCObject* pSender)
{
	int tag = ((CCMenuItem*)pSender)->getTag();
	Poker* pk;
	if(tag == 5 || tag == 0)
	{
		CCArray* ar = gameMain->getDuiZis(pokers);
		CCObject* obj;
		CCARRAY_FOREACH(ar,obj)
		{
			CCLog("sigles ::   %d",((Poker*)obj)->getNum());
		}
		CCLog("===============================================");
		gameMain->pass();
	}
	else if(tag < 3)
	{
		callScore = tag;
		gameMain->pass();
	}
	else if(tag == 3)
	{
		callScore = tag;
		gameMain->setLandLord();
	}
	else if(tag == 4)
	{
		outs->removeAllObjects();
		for(int i=0;i<pokers->count();i++)
		{
			pk = (Poker*)pokers->objectAtIndex(i);
			if(pk->getIsSelect())
				outs->addObject(pk);
		}
		for(int i=0;i<outs->count();i++)
		{
			pk = (Poker*)outs->objectAtIndex(i);
			pk->setCanTouch(false);
			pokers->removeObject(pk);
		}
		front->clearCards();
		front->getPokers()->removeAllObjects();
		front->getPokers()->addObjectsFromArray(outs);
		front->updatePokerLoc();
		updatePokerLoc();
	}
}
void Player::clearCards()
{
	Poker* pk;
	for(int i=0;i<pokers->count();i++)
	{
		pk = (Poker*)pokers->objectAtIndex(i);
		pk->removeFromParent();	
	}
}
void Player::setStatus(PlayerStatus st)
{
	status = st;
	if(type == FRONT || type == DECK)
		return;
	switch (st)
	{
	case DEALCARD:
		turnMenu->setVisible(false);
		callMenu->setVisible(false);
		break;
	case CALL:
		callMenu->setVisible(true);
		break;
	case OUTCARD:
		turnMenu->setVisible(true);
		break;
	default:
		break;
	}
}
void Player::sortPokers()
{
	int count = pokers->count();
	if(count < 2)
		return;
	
	Poker* pk1;
	Poker* pk2;
	for(int i=0;i<count-1;i++)
	{
		for(int j=0;j<count-i-1;j++)
		{
			pk1 = (Poker*)pokers->objectAtIndex(j);
			pk2 = (Poker*)pokers->objectAtIndex(j+1);
			if((pk1->getNum() < pk2->getNum()) || (pk1->getNum() == pk2->getNum() && pk1->getColor()<pk2->getColor()))
			{
				pokers->exchangeObject(pk1,pk2);
			}
		}
	}
}
void Player::updatePokerLoc()
{
	int count = pokers->count();
	if(count < 1)
		return;
	sortPokers();
	int x = -((count-1)*PokerB+PokerW)/2,y = PokerH/2+PokerB;
	//CCLog("%d,%f,",getRotation()>0.1f,getRotation());
	
	if(getRotation()>270.1f)
	{
		x -= (winWidth-winHeight+PokerH)/2;
	}else if(getRotation()>90.1f)
	{
		x += (winWidth-winHeight-PokerH)/2;
	}
	Poker* pk;
	for(int i=0;i<count;i++)
	{
		Poker* pk = (Poker*)pokers->objectAtIndex(i);
		pk->removeFromParent();
		switch (type)
		{
		case DECK:
			//pk->setPosition(ccp(0,0));
			if(status == DEALCARD)
				pk->setPosition(ccp(0,0));
			else
				pk->setPosition(ccp(x+i*PokerW,y));
			////pk->setBack();
			break;
		case PLAYER:
			//pk->setCanTouch(true);
		case NPC:
			pk->setCanTouch(true);
		case FRONT:
		default:
			pk->setPosition(ccp(x+i*PokerB,y));
			pk->setPokerPriority(i);
			break;
		}
		addChild(pk);
	}
	
}
