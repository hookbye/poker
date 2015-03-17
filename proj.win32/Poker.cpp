#include "Poker.h"

Poker::Poker():m_isFront(true),m_isSel(false),m_color(SPADE),
	m_name(NULL),m_num(A),m_canTouch(false)
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
Poker* Poker::copyPoker()
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
		setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("poker_6_0.png"));
	}
}

void Poker::setSelect()
{
	if(m_isSel)
	{
		setPositionY(getPositionY()-10);
	}else
	{
		setPositionY(getPositionY()+10);
	}
	m_isSel = !m_isSel;
}

bool Poker::ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent)
{
	CCPoint pos = convertToNodeSpaceAR(pTouch->getLocation());
	CCRect rect(-PokerW/2,-PokerH/2,PokerW,PokerH);
	if(rect.containsPoint(pos)&&m_canTouch)
	{
		CCLog("poker :%d_%d,tag %d,in rect: %d,cantouch : %d",m_color,m_num,getTag(),rect.containsPoint(pos),m_canTouch);
		setSelect();
		return true;
	}else
	{
		return false;
	}
	
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
void Poker::setPokerPriority(int num)
{
	//CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(num,this);
}
void Poker::onEnter()
{
	CCSprite::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1000,true);
}
void Poker::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}