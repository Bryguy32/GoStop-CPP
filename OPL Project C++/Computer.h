#ifndef COMPUTER_H
#define COMPUTER_H
#include "Player.h"

class Computer :
	public Player
{

public:

	Computer();
	~Computer();

	void play(vector<Card>& deckOfCards, vector<Card>& layout, vector<Card>& computerDeck, vector<Card>& computerCapture, vector<Card> humanCapture);

};
#endif