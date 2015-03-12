#pragma once
#define TURNTIME 2
const int PokerW = 71;
const int PokerH = 96;
const int PokerB = 20;
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
};
enum PokerClass{
	DANZHANG,
	DUIZI,
	SANTIAO,
	SANDAIYI,
	SANDAIER,
	LIANDUI,
	FEIJI,
	SHUNZI,
	ZHADAN,
	SHUANGWANG,
};
enum PlayerType{
	PLAYER,
	NPC,
	FRONT,
	DECK,
};

enum PlayerStatus{
	DEALCARD,
	CALL,
	OUTCARD,
};



