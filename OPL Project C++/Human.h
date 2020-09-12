#ifndef HUMAN_H
#define HUMAN_H
#include "Player.h"

class Human :
	public Player
{

public:
	
	Human();
	~Human();

	void play(vector<Card> &deckOfCards, vector<Card> &layout, vector<Card> &humanDeck, vector<Card> &humanCapture);

	};
#endif

