/*************************************************************
* Name:  Bryan Francis
* Project : GoStop C++
* Class : OPL Spring 2020
* Date : 3/11/2020
*************************************************************/
#include "stdafx.h"
#include "Deck.h"


/* *********************************************************************
Function Name: Deck
Purpose: The constructor of the class
Parameters:
			None
Assistance Received: http://www.cplusplus.com/forum/general/94712/
********************************************************************* */
Deck::Deck() {

	/* Create Deck */
	vector <Card> newDeck;

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 4; j++) {

			newDeck.push_back(Card(i,j));
		
		}
	}

	deckOfCards = newDeck;
}

/* *********************************************************************
Function Name: ~Deck
Purpose: The deconstructor of the class
Parameters:
			None
Assistance Received: none
********************************************************************* */
Deck::~Deck() {


}

/* *********************************************************************
Function Name: setDeck
Purpose: Sets the deck
Parameters:
			Vector<Card>
Assistance Received: none
********************************************************************* */
void Deck::setDeck(vector<Card> deckOfCards) {

	this->deckOfCards = deckOfCards;
}

/* *********************************************************************
Function Name: getDeck
Purpose: Gets the deck
Parameters:
			None
Assistance Received: none
********************************************************************* */
vector<Card> Deck::getDeck() {

	return this->deckOfCards;
}

/* *********************************************************************
Function Name: shuffleCards
Purpose: Randomly shuffles cards
Parameters:
			None
Assistance Received: none
********************************************************************* */
void Deck::shuffleCards() {
	/*Shuffle Cards*/

	srand(time(NULL));
	random_shuffle(deckOfCards.begin(), deckOfCards.end());

}

/* *********************************************************************
Function Name: printVector
Purpose: printVector prints the vector when called with print from the
card class
Parameters:
			Vector<Card>
Assistance Received: none
********************************************************************* */
void Deck::printVector(vector<Card> v) {

	for (int i = 0; i < v.size(); i++) {

		v[i].print();
	}

}


/* *********************************************************************
Function Name: deleteFive
Purpose: Deletes five cards from the deck
Parameters:
			None
Assistance Received: none
********************************************************************* */
void Deck::deleteFive() {

	deckOfCards.erase(deckOfCards.begin(), deckOfCards.begin() + 5);
}

/* *********************************************************************
Function Name: deleteFour
Purpose: Deletes four cards from teh deck
Parameters:
			None
Assistance Received: none
********************************************************************* */
void Deck::deleteFour() {

	deckOfCards.erase(deckOfCards.begin(), deckOfCards.begin() + 4);

}