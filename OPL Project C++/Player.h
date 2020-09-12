#ifndef PLAYER_H
#define PLAYER_H
#include "Deck.h"

class Player
{

private:

	int score = 0;
	bool isTurn = false;


public:

	Player();
	~Player();

	void setTurn(bool turn);
	bool getIsTurn();

	void setScore(int score);
	int getScore();

	/* Get help and computer AI*/
	bool tripleCap(vector<Card> layout, vector<Card> deck, int &cardPosition);
	bool stackPair(vector<Card> layout, vector<Card> deck, vector<Card> capturePile, int& cardPosition);
	bool block(vector<Card> layout, vector<Card> deck, vector<Card> enemyCapturePile, int &cardPosition);
	bool pairFromStockPile(vector<Card> deck, vector<Card> stockPile, int& cardPosition);

	/* For human and computer moves */
	bool isStackPair(vector<Card> layout, int cardPosition);
	bool stackPairMatchesStockPile(vector<Card> layout, vector<Card> stockPile);
	bool tripleCapPositions(vector<Card> layout, vector<Card> deck, int choosenCard, int& layoutMatch1, int& layoutMatch2, int& layoutMatch3);


	virtual void play(vector<Card> stockPile, vector<Card> layout, vector<Card> humanDeck, vector<Card> humanCapture, vector<Card> computerCapture);


};
#endif
