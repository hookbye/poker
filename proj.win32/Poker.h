#pragma once
#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class Poker :
	public CCSprite,public CCStandardTouchDelegate
{
public:
	Poker();
	~Poker();
	virtual bool initWithNumColor(PokerColor color,PokerNum num);
	static Poker* create(PokerColor color,PokerNum num);
	Poker* copyPoker();
	void setFront();
	void setBack();
	void setSelect();
	void setPokerPriority(int num);

	void onEnter();
	void onExit();

	virtual bool ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchCancelled(CCTouch* pTouch,CCEvent* pEvent);
	
	CC_SYNTHESIZE(PokerNum ,m_num,Num);
	CC_SYNTHESIZE(PokerColor ,m_color,Color);
	CC_SYNTHESIZE(CCString* ,m_name,Name);
	CC_SYNTHESIZE(bool ,m_isFront,IsFront);
	CC_SYNTHESIZE(bool ,m_isSel,IsSelect);
	CC_SYNTHESIZE(bool ,m_canTouch,CanTouch);
	CC_SYNTHESIZE(int  ,touchPriority,TouchPriority);
	
private:

};

