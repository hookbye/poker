#pragma once
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

enum PlayerType{
	PLAYER,
	NPC,
	DECK,
};