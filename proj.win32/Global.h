#pragma once
#include "cocos2d.h"
#define TURNTIME 10
const int PokerW = 71;
const int PokerH = 96;
const int PokerB = 20;
const cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
const int winWidth = 800;//winSize.width;
const int winHeight = 600;//winSize.height;
enum PokerColor{
	SPADE = 1,
	HEART,
	DIAMOND,
	CLUB,
	JOKER,
};
enum PokerNum{
	THREE = 1,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	J,
	Q,
	K,
	A,
	TWO,
	XIAOGUI,
	DAGUI,
};
enum PokerClass{
	DANZHANG,
	DUIZI,
	SANTIAO,
	SANDAIYI,
	LIANDUI,
	SANDAIER,
	SIDAIYI,
	FEIJI,
	SIDAIER,
	SHUNZI,
	ZHADAN,
	SHUANGWANG,
	NOTHING,
};
enum PlayerType{
	PLAYER,
	NPC,
	NPC1,
	FRONT,
	DECK,
};

enum PlayerStatus{
	DEALCARD,
	CALL,
	TOBEOUT,
	NOTOUT,
	OUTCARD,
	DISPLAY,
};

struct OutData{
	//cocos2d::CCArray* pokers;
	PokerClass paixing;
	int num;
	int low;
};


