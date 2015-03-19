#include "Player.h"
#include "Poker.h"
#include "GameScene.h"
#include "Tool.h"
Player::Player(void):gameMain(NULL),front(NULL),type(PLAYER),status(DEALCARD),isLord(false),callScore(0)
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
void Player::reset()
{
	status = DEALCARD;
	isLord = false;
	callScore = 0;
	clearCards();
	setStatus(DEALCARD);
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

		roundLabel = CCLabelTTF::create(a2u("不出").c_str(),"arial",40);
		roundLabel->setPosition(ccp(0,PokerH*1.5));
		roundLabel->retain();
		roundLabel->setVisible(false);
		addChild(roundLabel);
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
		setStatus(DISPLAY);
		pass();
	}
	else if(tag < 3)
	{
		callScore = tag;
		pass();
	}
	else if(tag == 3)
	{
		callScore = tag;
		gameMain->setLandLord();
	}
	else if(tag == 4)
	{
		outPokers();
	}
}
bool Player::canBeOut(OutData round)
{
	//getOutPokers();
	PokerClass pc = gameMain->analyPaixing(outs);
	OutData ground = gameMain->getRoundData();
	
	if ((pc != NOTHING) && (ground.paixing == NOTHING || (round.paixing == ground.paixing && round.num == ground.num && round.low > ground.low)))
	{
		return true;
	}
	return false;
}
void Player::getOutPokers()
{
	Poker* pk;
	outs->removeAllObjects();
	for(int i=0;i<pokers->count();i++)
	{
		pk = (Poker*)pokers->objectAtIndex(i);
		if(pk->getIsSelect())
			outs->addObject(pk);
	}
}
void Player::outPokers()
{
	getOutPokers();
	if(outs->count()<1)
		return;
	gameMain->sortPokers(outs);
	OutData round = gameMain->analyPokers(outs);
	if(canBeOut(round))
	{
		Poker* pk;
		for(int i=0;i<outs->count();i++)
		{
			pk = (Poker*)outs->objectAtIndex(i);
			pk->setCanTouch(false);
			CCLog("%d outcard：%d _ %d",type,pk->getColor(),pk->getNum());
			pokers->removeObject(pk);
		}
		//front->clearCards();
		//front->getPokers()->removeAllObjects();
		front->getPokers()->addObjectsFromArray(outs);
		front->updatePokerLoc();
		updatePokerLoc();   
		gameMain->setRoundData(round);
		setStatus(DISPLAY);
		pass();
	}else
	{
		Poker* pk;
		for(int i=0;i<outs->count();i++)
		{
			pk = (Poker*)outs->objectAtIndex(i);
			pk->setFront();
		}
		outs->removeAllObjects();
		resetPokers();
		if(type != PLAYER)
			CCLog("break auto");
	}
}
void Player::genPai(OutData round)
{
	CCLog("gen pai isnothing?%d,paixing %d",round.paixing == NOTHING,round.paixing);
	if (round.paixing == NOTHING)
	{
		if(type != PLAYER )
		{
			if(pokers->count()>0)
			{
				outs->removeAllObjects();
				outs->addObjectsFromArray(randomOut());
				for(int i=0;i<outs->count();i++)
					((Poker*)outs->objectAtIndex(i))->setIsSelect(true);
				outPokers();
			}else
			{
				CCLog(" player :%d  pass ",type);
				pass();
			}
		}
		return;
	}
	outs->removeAllObjects();
	CCArray* arr = gameMain->getPokersByCly(pokers,round.paixing,round.num,round.low);
	CCLog("genpai canbe out :%d  ",arr && arr->count()>0);
	if (arr && arr->count()>0)
	{
		outs->addObjectsFromArray(arr);
		for(int i=0;i<outs->count();i++)
		{
			((Poker*)outs->objectAtIndex(i))->setSelect();
		}
		CCLog(" player :%d  out ",type);
		if(type != PLAYER)
			outPokers();
		else
		{
			CCLog("player turn------");
		}
	}else
	{
		if(type != PLAYER)
		{
			CCLog(" player :%d  pass ",type);
			pass();
		}
	}
}

void Player::callLord()
{
	srand(time(NULL));
	callScore = rand()%4;
	if(callScore == 3)
		gameMain->setLandLord();
	else
		pass();
}
CCArray* Player::randomOut()
{
	CCArray* result = NULL;

	srand(time(NULL));
	PokerClass rpx = (PokerClass)(rand()%NOTHING);//NOTHING为最大类型，取nothing 之下的类型
	//debug paixing == 5
	//rpx = SANDAIER;
	for(int i=0;i<NOTHING;i++)
	{
		int num = 0;
		switch (rpx)
		{
		case DANZHANG:
			num = 1;
			break;
		case DUIZI:
		case SHUANGWANG:
			num = 2;
			break;
		case SANTIAO:
			num = 3;
			break;
		case SANDAIYI:
		case ZHADAN:
			num = 4;
			break;
		case SANDAIER:
		case SIDAIYI:
		case SHUNZI:
			num = 5;
			break;
		case LIANDUI:
		case FEIJI:
		case SIDAIER:
			num = 6;
			break;
		default:
			break;
		}
		CCLog("paixing %d  ranom num is %d",(rpx+i)%NOTHING,num);
		
		result = gameMain->getPokersByCly(pokers,(PokerClass)((rpx+i)%NOTHING),num,0);
		if(result && result->count() > 0)
			break;
	}
	if(result == NULL || result->count()<1)
	{
		result = CCArray::create();
		result->addObject(pokers->randomObject());
	}
	return result;
}
void Player::resetPokers()
{
	int count = pokers->count();
	Poker* pk;
	for(int i=0;i<count;i++)
	{
		pk = (Poker*)pokers->objectAtIndex(i);
		pk->setCanTouch(true);
		pk->setIsSelect(false);
	}
	count = outs->count();
	for(int i=0;i<count;i++)
	{
		pk = (Poker*)outs->objectAtIndex(i);
		pk->setIsSelect(false);
	}
	updatePokerLoc();
}
void Player::pass()
{
	if(pokers->count()>0)
		gameMain->pass();
	else
		gameMain->win();
}
void Player::clearCards()
{
	Poker* pk;
	for(int i=0;i<pokers->count();i++)
	{
		pk = (Poker*)pokers->objectAtIndex(i);
		pk->removeFromParent();	
	}
	pokers->removeAllObjects();
}
void Player::setStatus(PlayerStatus st)
{
	status = st;
	
	if(type == FRONT || type == DECK)
		return;
	resetPokers();
	switch (st)
	{
	case DEALCARD:
	case DISPLAY:
		turnMenu->setVisible(false);
		callMenu->setVisible(false);
		roundLabel->setVisible(false);
		break;
	case CALL:
		turnMenu->setVisible(false);
		roundLabel->setVisible(false);
		if(type == PLAYER)
			callMenu->setVisible(true);
		else
			callLord();
		break;
	case TOBEOUT:
		roundLabel->setVisible(false);
		callMenu->setVisible(false);
		front->clearCards();
		turnMenu->setVisible(true);
		//if(type != PLAYER)
		genPai(gameMain->getRoundData());
		break;
	case NOTOUT:
		turnMenu->setVisible(false);
		callMenu->setVisible(false);
		roundLabel->setVisible(true);
		gameMain->setNotOut(type);
		break;
	case OUTCARD:
		turnMenu->setVisible(false);
		callMenu->setVisible(false);
		roundLabel->setVisible(false);
		gameMain->setNotOut(type,false);
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
		addChild(pk);
		pk->setIsSelect(false);
		if(type != DECK)
		{
			int priority = -i-1;
			pk->setPokerPriority(priority);
		}
		pk->setCanTouch(false);
		switch (type)
		{
		case DECK:
			//pk->setPosition(ccp(0,0));
			if(status == DEALCARD)
			{
				pk->setPosition(ccp(0,0));
				pk->setBack();
			}
			else
			{
				pk->setPosition(ccp(x+i*PokerW,y+20));
				//pk->setColor(DIAMOND);
				pk->setFront();
			}
			pk->setCanTouch(false);
			break;
		case PLAYER:
			pk->setCanTouch(true);
		case FRONT:
			pk->setFront();
		case NPC:
		case NPC1:
			//pk->setFront();
		default:
			pk->setPosition(ccp(x+i*PokerB,y));
			break;
		}		
	}

}
