#include "GameScene.h"
#include "Tool.h"
USING_NS_CC;
GameScene::GameScene():turnCount(0),turnTime(0),callCount(0),paixing((PokerClass)0),
	isDealing(true),isCalling(false),roundCount(0)
{
	pokers = CCArray::create();
	pokers->retain();
	players = CCArray::create();
	players->retain();

	roundData.paixing = NOTHING;
	roundData.num = 0;
	roundData.low = 0;

}
GameScene::~GameScene()
{
	CC_SAFE_RELEASE(pokers);
	CC_SAFE_RELEASE(players);
}
CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    CCSprite* pSprite = CCSprite::create("bk.png");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite, -1);

	timer = CCLabelTTF::create(a2u("¼ÆÊ±").c_str(),"Marker Felt",40);
	timer->setPosition(ccp(visibleSize.width/2,visibleSize.height - PokerB));
	addChild(timer,1);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pokers.plist","pokers.png");

	initPlayers();
	initPokers();
	checkPokers();

	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);
	//this->scheduleUpdate();
    return true;
}
bool GameScene::initPlayers()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	player = Player::create();
	player->retain();
	player->setType(PLAYER);
	player->setPosition(ccp(size.width/2,0));
	player->setGameMain(this);
	player->setTag(0);
	addChild(player);
	players->addObject(player);
	
	npcOne = Player::create();
	npcOne->retain();
	npcOne->setType(NPC);
	npcOne->setPosition(ccp(0,size.height/2));
	npcOne->setRotation(90);
	npcOne->setGameMain(this);
	npcOne->setTag(1);
	addChild(npcOne);
	players->addObject(npcOne);

	npcTwo = Player::create();
	npcTwo->retain();
	npcTwo->setType(NPC);
	npcTwo->setGameMain(this);
	npcTwo->setPosition(ccp(size.width,size.height/2));
	npcTwo->setRotation(270);
	npcTwo->setTag(2);
	addChild(npcTwo);
	//npcTwo->setVisible(false);
	players->addObject(npcTwo);

	frontOne = Player::create();
	frontOne->retain();
	frontOne->setType(FRONT);
	frontOne->setPosition(ccp(size.width/2,1.5*PokerH));
	player->setFront(frontOne);
	addChild(frontOne);
	//players->addObject(frontOne);
	
	 
	frontTwo = Player::create();
	frontTwo->retain();
	frontTwo->setType(FRONT);
	frontTwo->setPosition(ccp(1.5*PokerH,size.height/2));
	frontTwo->setRotation(90);
	addChild(frontTwo);
	npcOne->setFront(frontTwo);
	//players->addObject(frontTwo);

	frontThree = Player::create();
	frontThree->retain();
	frontThree->setType(FRONT);
	frontThree->setPosition(ccp(size.width-PokerH*1.5,size.height/2));
	frontThree->setRotation(270);
	addChild(frontThree);
	npcTwo->setFront(frontThree);
	//players->addObject(frontThree);

	deck = Player::create();
	deck->retain();
	deck->setType(DECK);
	deck->setPosition(ccp(size.width/2,size.height/2+PokerH));
	deck->setStatus(DEALCARD);
	addChild(deck,0);
	//players->addObject(deck);

	return true;
}
bool GameScene::initPokers()
{
	Poker* poker;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<13;j++)
		{
			poker = Poker::create((PokerColor)(i+1),(PokerNum)(j+1));
			pokers->addObject(poker);
			//addChild(poker);
		}
	}
	poker = Poker::create((PokerColor)5,(PokerNum)14);
	pokers->addObject(poker);

	poker = Poker::create((PokerColor)5,(PokerNum)15);
	pokers->addObject(poker);

	deck->getPokers()->addObjectsFromArray(pokers);
	deck->updatePokerLoc();
	return true;
}
void GameScene::checkPokers()
{
	Poker* pk;
	Poker* pk1;
	CCObject* object;
	srand((unsigned)time(NULL));
	CCARRAY_FOREACH(pokers,object)
	{
		pk = (Poker*)object;
		pk1 = (Poker*)pokers->randomObject();
		if (pk != pk1)
		{
			pokers->exchangeObject(pk,pk1);
		}
	}
	deck->updatePokerLoc();
}
void GameScene::sortPokers(CCArray* pks)
{
	int count = pks->count();
	if(count < 2)
		return;

	Poker* pk1;
	Poker* pk2;
	for(int i=0;i<count-1;i++)
	{
		for(int j=0;j<count-i-1;j++)
		{
			pk1 = (Poker*)pks->objectAtIndex(j);
			pk2 = (Poker*)pks->objectAtIndex(j+1);
			if((pk1->getNum() < pk2->getNum()) || (pk1->getNum() == pk2->getNum() && pk1->getColor()<pk2->getColor()))
			{
				pks->exchangeObject(pk1,pk2);
			}
		}
	}
}
void GameScene::movePokerTo(Player* src,Player* dest,int index)
{
	int srcCount  = src->getPokers()->count();
	if(srcCount<1)
		return;
	CCPoint pos;
	Poker* pk ;
	if(index>-1 && index<srcCount)
		pk = (Poker*)src->getPokers()->objectAtIndex(index);
	else
		pk = (Poker*)src->getPokers()->randomObject();
	src->getPokers()->removeObject(pk);
	Player* temp = dest;
	
	pos = deck->convertToNodeSpaceAR(dest->getPosition());
	dest->getPokers()->addObject(pk);
	deck->getPokers()->removeObject(pk);
	pk->setTag(dest->getTag());	
	CCMoveTo* move = CCMoveTo::create(0.1f,pos);
	CCCallFuncO* callback = CCCallFuncO::create(this,SEL_CallFuncO(&GameScene::dealPokerCallback),pk);
	CCSequence* seq = CCSequence::createWithTwoActions(move,callback);
	pk->runAction(seq);
}
void GameScene::dealPokers()
{
	if (deck->getPokers()->count()<4)
	{
		isDealing = false;
		isCalling = true;
		deck->setStatus(DISPLAY);
		deck->updatePokerLoc();
		//debug not update
		if (player->getStatus() == DEALCARD)
		{
			turnCount = player->getTag();
			player->setStatus(CALL);
		}
		
		return;
	}
	isDealing = true;
	
	Player* temp = (Player*)players->objectAtIndex(turnCount++%3);
	movePokerTo(deck,temp);
}
void GameScene::dealPokerCallback(CCObject* sender)
{
	Poker* pk = (Poker*)sender;
	((Player*)players->objectAtIndex(pk->getTag()))->updatePokerLoc();
	dealPokers();
}
void GameScene::setLandLord()
{
	Player* temp;
	Player* lord = NULL;
	int maxScore = 0;
	int score;
	for(int i=0;i<3;i++)
	{
		temp = (Player*)players->objectAtIndex(i);
		temp->setStatus(DISPLAY);
		score = temp->getCallScore();
		if(score > 0)
		{
			maxScore = maxScore < score ? score:maxScore;
			if(score >= maxScore)
				lord = temp;
		}
	}
	if(!lord)
	{
		lord = player;
	}
	lord->setIsLord(true);
	lord->setStatus(OUTCARD);
	turnCount = lord->getTag();
	turnTime = TURNTIME;
	callCount = 4;
	CCArray* arr = CCArray::create();
	Poker* pk;
	for(int i=0;i<3;i++)
	{
		pk = (Poker*)deck->getPokers()->objectAtIndex(i);
		arr->addObject(pk->copyPoker());
	}
	for(int i=0;i<3;i++)
		movePokerTo(deck,lord);
	deck->getPokers()->addObjectsFromArray(arr);
	deck->updatePokerLoc();
}
void GameScene::pass()
{
	turnTime = 0;
	int timerCount = TURNTIME - ceil(turnTime);
	timer->setString(a2u(CCString::createWithFormat("%d",timerCount%TURNTIME+1)->getCString()).c_str());
	Player* temp;
	for(int i=0;i<3;i++)
	{
		temp = (Player*)players->objectAtIndex(i);
		temp->setStatus(DISPLAY);
	}
	
	temp = ((Player*)players->objectAtIndex(++turnCount%3));
	if(isCalling && callCount < 3)
	{
		temp->setStatus(CALL);
		callCount++;
		
	}
	else
	{
		if(callCount == 3)
		{
			setLandLord();
			callCount++;
		}
		isCalling = false;
		temp->setStatus(OUTCARD);
	}
	if (!isCalling)
	{
		roundCount = ++roundCount%3;
		if(roundCount == 0)
		{
			roundData.paixing = NOTHING;
		}
		CCLog("round Count %d",roundCount);
	}
}
void GameScene::update(float dt)
{
	
	if(isDealing)
		return;
	turnTime += dt;
	int timerCount = TURNTIME - ceil(turnTime);
	timer->setString(a2u(CCString::createWithFormat("%d",timerCount%TURNTIME+1)->getCString()).c_str());
	if(turnTime > TURNTIME)
	{
		pass();
		if(!isCalling)
		{

		}
	}
}

CCArray* GameScene::getDanZhangs(CCArray* pks,int low)
{
	int count = pks->count();
	if (!pks || count<1)
	{
		return NULL;
	}
	CCArray* result = CCArray::create();
	Poker* pk;
	Poker* pk1;
	for(int i=0;i<count-1;i++)
	{
		pk = (Poker*)pks->objectAtIndex(i);
		result->addObject(pk);
	}
	for(int i=0;i<count-1;i++)
	{
		pk = (Poker*)pks->objectAtIndex(i);
		for(int j=i+1;j<count;j++)
		{
			pk1 = (Poker*)pks->objectAtIndex(j);
			if(pk1->getNum() == pk->getNum())
			{
				result->removeObject(pk);
				result->removeObject(pk1);
			}
		}
		if (pk->getNum()<=low)
		{
			result->removeObject(pk);
		}
	}
	//sortPokers(result);
	return result;
}
CCArray* GameScene::getDuiZis(CCArray* pks,int num,int low)
{
	int count = pks->count();
	if (!pks || count<1)
	{
		return NULL;
	}
	CCArray* result = CCArray::create();
	Poker* pk;
	Poker* pk1;
	
	for(int i=0;i<count-num;i++)
	{
		pk = (Poker*)pks->objectAtIndex(i);
		pk1 = (Poker*)pks->objectAtIndex(i+num);
		if(pk->getNum() == pk1->getNum() && pk->getNum()>low)
		{
			for(int j=i;j<=i+num;j++)
			{
				pk = (Poker*)pks->objectAtIndex(j);
				result->addObject(pk);
			}
			i+= num;
		}
	}
	return result;
}
CCArray* GameScene::getPokersFromArray(CCArray* pks,int num,bool fromTop)
{
	
	int count = pks->count();
	if (!pks || count<1)
	{
		return NULL;
	}
	CCArray* result = CCArray::create();
	Poker* pk;
	
	if (fromTop)
	{
		for (int i = count-1;i>=count - num;i--)
		{
			pk = (Poker*)pks->objectAtIndex(i);
			result->addObject(pk);
		}
	}else
	{
		
		for (int i = 0;i<num;i++)
		{
			pk = (Poker*)pks->objectAtIndex(i);
			result->addObject(pk);
		}
	}
	
	return result;
}
CCArray* GameScene::getPokersByCly(CCArray* pks,PokerClass cly,int num,int low,bool caipai)
{
	int count = pks->count();
	if (!pks || count<1)
	{
		return NULL;
	}
	CCArray* result = CCArray::create();
	CCArray* temp;
	switch (cly)
	{
	case DANZHANG:
		temp = getPokersFromArray(getDanZhangs(pks,low),1);
		if (temp)
		{
			result->addObjectsFromArray(temp);
		}
		break;
	case DUIZI:
		temp = getPokersFromArray(getDuiZis(pks,1,low),2);
		if (temp)
		{
			result->addObjectsFromArray(temp);
		}
		break;
	case SANTIAO:
		temp = getPokersFromArray(getDuiZis(pks,2,low),3);
		if (temp)
		{
			result->addObjectsFromArray(temp);
		}
		break;
	case SANDAIYI:
		break;
	case SANDAIER:
		break;
	case LIANDUI:
		break;
	case FEIJI:
		break;
	case SHUNZI:
		break;
	case ZHADAN:
		break;
	case SHUANGWANG:
		break;
	default:
		break;
	}
	return result;
}
OutData GameScene::analyPokers(CCArray* pks)
{
	OutData data;
	int count = pks->count();
	data.num = count;
	data.low = ((Poker*)pks->objectAtIndex(count-1))->getNum();
	//data.pokers = pks;
	data.paixing = analyPaixing(pks);

	return data;
}
PokerClass GameScene::analyPaixing(CCArray* pks,bool re)
{
	PokerClass px = NOTHING;
	int count = pks->count();
	Poker* pk;
	Poker* pk1;
	if (count == 1)
	{
		return DANZHANG;
	}else if (count == 2)
	{
		pk = (Poker*)pks->objectAtIndex(0);
		pk1 = (Poker*)pks->objectAtIndex(1);
		if (pk->getNum() == pk1->getNum())
		{
			return DUIZI;
		}
	}else if (count == 3)
	{
		pk = (Poker*)pks->objectAtIndex(0);
		pk1 = (Poker*)pks->objectAtIndex(2);
		if (pk->getNum() == pk1->getNum())
		{
			return SANTIAO;
		}
	}else if (count == 4)
	{
		pk = (Poker*)pks->objectAtIndex(0);
		pk1 = (Poker*)pks->objectAtIndex(3);
		if (pk->getNum() == pk1->getNum())
		{
			return ZHADAN;
		}else
		{
			pk1 = (Poker*)pks->objectAtIndex(2);
			if (pk->getNum() == pk1->getNum())
			{
				return SANDAIYI;
			}
		}
		pk1 = (Poker*)pks->objectAtIndex(2);
		if (pk->getNum() == pk1->getNum())
		{
			return SANDAIYI;
		}
		pk1 = (Poker*)pks->objectAtIndex(1);
		if (pk->getNum() == pk1->getNum())
		{
			pk = (Poker*)pks->objectAtIndex(1); 
			pk1 = (Poker*)pks->objectAtIndex(2);
			if (pk->getNum() == pk1->getNum())
			{
				return LIANDUI;
			}
		}
	}
	else if (count == 5)
	{
		pk = (Poker*)pks->objectAtIndex(0);
		pk1 = (Poker*)pks->objectAtIndex(3);
		if (pk->getNum() == pk1->getNum())
		{
			return SIDAIYI;
		}

		pk = (Poker*)pks->objectAtIndex(0);
		pk1 = (Poker*)pks->objectAtIndex(3);
		if (pk->getNum() == pk1->getNum())
		{
			return SANDAIER;
		}
		bool shunZi = true;
		for (int i=0;i<count-1;i++)
		{
			pk = (Poker*)pks->objectAtIndex(i);
			pk1 = (Poker*)pks->objectAtIndex(i+1);
			if (pk->getNum()-1 != pk1->getNum())
			{
				shunZi = false;
			}
		}
		if (shunZi)
		{
			return SHUNZI;
		}
	}
	else
	{
		if (count == 6)
		{
			pk = (Poker*)pks->objectAtIndex(0);
			pk1 = (Poker*)pks->objectAtIndex(3);
			if (pk->getNum() == pk1->getNum())
			{
				return SIDAIER;
			}
		}
		
		if (isYiLian(pks,1))
		{
			return SHUNZI;
		}
		if (isYiLian(pks,2))
		{
			return LIANDUI;
		}
		if (isYiLian(pks,3))
		{
			return FEIJI;
		}

	}
	if (!re)
	{
		CCArray* reverseArray = CCArray::create();
		for (int i=count - 1;i>=0;i--)
		{
			pk = (Poker*)pks->objectAtIndex(i);
			reverseArray->addObject(pk);
		}
		analyPaixing(reverseArray,true);
	}
	
	return NOTHING;
}
bool GameScene::isYiLian(CCArray* pks,int num)
{
	int count = pks->count();
	if((count < num) || (num>1 && (count < 4 || count/num < 2)) || (num == 1 && count< 5))
		return false;
	bool isYilian = true;
	Poker* pk;
	Poker* pk1;

	for (int i=0;i<count-num;i+=num)
	{
		pk = (Poker*)pks->objectAtIndex(i);
		pk1 = (Poker*)pks->objectAtIndex(i+num);
		if (pk->getNum() == pk1->getNum()+1)
		{
			isYilian =  false;
		}
	}
	return isYilian;
}
bool GameScene::ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent)
{
	//CCPoint pos = convertToNodeSpaceAR(pTouch->getLocation());
	
	return true;
}
void GameScene::ccTouchMoved(CCTouch* pTouch,CCEvent* pEvent)
{
}
void GameScene::ccTouchEnded(CCTouch* pTouch,CCEvent* pEvent)
{
}
void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    //CCDirector::sharedDirector()->end();
	dealPokers();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
