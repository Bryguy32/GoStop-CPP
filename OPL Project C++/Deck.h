#ifndef DECK_H
#define DECK_H
#include "Card.h"

class Deck 
{
private:

	std::vector<Card> deckOfCards;

public:
	
	Deck(); 
	~Deck(); 

	/* Setter, Getter */
	void setDeck(vector<Card> deckOfCards);
	vector<Card> getDeck();

	void shuffleCards(); 

	/* Print Vectors */
	void printVector(vector<Card> v);
	
	void deleteFive();
	void deleteFour();
	


	
};
#endif

