#include "Poker.h"

Poker::Poker():m_isFront(true)
{
}
Poker::~Poker()
{
}
bool Poker::initWithNumColor(PokerColor color,PokerNum num)
{
	do{
		
		m_color = color;
		m_num = num;
		m_name = CCString::createWithFormat("poker_%d_%d.png",color,num);
		CC_BREAK_IF(!CCSprite::initWithSpriteFrameName(m_name->getCString()));
		
		return true;
	}while(0);
	return false;
}
Poker* Poker::create(PokerColor color,PokerNum num)
{
	Poker* pk = new Poker();
	if(pk && pk->initWithNumColor(color,num))
	{
		pk->autorelease();
		return pk;
	}
	CC_SAFE_DELETE(pk);
	return NULL;
}
Poker* Poker::copy()
{
	Poker* pk = Poker::create(getColor(),getNum());
	return pk;
}
void Poker::setFront()
{
	if(!m_isFront)
	{
		setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_name->getCString()));
	}
}
void Poker::setBack()
{
	if(m_isFront)
	{
		setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("poker_6_1.png"));
	}
}
void Poker::onEnter()
{
	CCSprite::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,true);
}
void Poker::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

bool Poker::ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent)
{
	return true;
}
void Poker::ccTouchMoved(CCTouch* pTouch,CCEvent* pEvent)
{
}
void Poker::ccTouchEnded(CCTouch* pTouch,CCEvent* pEvent)
{
}
void Poker::ccTouchCancelled(CCTouch* pTouch,CCEvent* pEvent)
{
}