#ifndef ROUND_H
#define ROUND_H

#include "Deck.h"
#include "Computer.h"
#include "Human.h"
#include "Player.h"
#include "Serialization.h"

class Round
{

private:

	int round = 1;

	Card card;
	Deck deck;
	Player player;
	Human human;
	Computer computer;
	Serialization s;

	std::vector<Card> computerDeck;
	std::vector<Card> humanDeck;
	std::vector<Card> layout;
	std::vector<Card> deckOfCards;
	std::vector<Card> humanCapture;
	std::vector<Card> computerCapture;



public:

	Round();
	~Round();

	void setRound(int round);
	int getRound();

	void setHumanDeck(vector<Card> humanDeck);
	void setComputerDeck(vector<Card> computerDeck);
	void setHumanCapture(vector<Card> humanCapture);
	void setComputerCapture(vector<Card> computerCapture);
	void setLayout(vector<Card> layout);
	void setStockPile(vector<Card> deckOfCards);
	void setScores(int comScore, int humanScore);
	void isComputerTurn(bool isTurn);

	void setUpRound();
	void determinePlayer();
	void dealAgain();


	void display();
	void menu(); 
	void computerMenu();
	void checkHand();

	void switchPlayers();

	void move();
	void nextRound();
	void endRound();
	
	

};
#endif