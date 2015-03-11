#include "GameScene.h"

USING_NS_CC;
GameScene::GameScene()
{
	pokers = CCArray::create();
	pokers->retain();
}
GameScene::~GameScene()
{
	CC_SAFE_RELEASE(pokers);
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
	this->addChild(pSprite, 0);

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pokers.plist","pokers.png");
	//����������
	
	initPlayers();
	initPokers();
	checkPokers();


    return true;
}
bool GameScene::initPlayers()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	player = Player::create();
	player->retain();
	player->setType(PLAYER);
	player->setPosition(ccp(size.width/2,0));
	addChild(player);
	
	npcOne = Player::create();
	npcOne->retain();
	npcOne->setType(NPC);
	npcOne->setPosition(ccp(0,size.height/2));
	addChild(npcOne);

	npcTwo = Player::create();
	npcTwo->retain();
	npcOne->setType(NPC);
	npcTwo->setPosition(ccp(size.width,size.height/2));
	addChild(npcTwo);
	
	deck = Player::create();
	deck->retain();
	deck->setType(DECK);
	deck->setPosition(ccp(size.width/2,size.height/2));
	addChild(deck);
	
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
	deck->getPokers()->addObjectsFromArray(pokers);
	deck->updatePokerLoc();
	return true;
}
void GameScene::checkPokers()
{
}
void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
