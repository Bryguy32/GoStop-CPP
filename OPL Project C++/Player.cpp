/*************************************************************
* Name:  Bryan Francis
* Project : GoStop C++
* Class : OPL Spring 2020
* Date : 3/11/2020
*************************************************************/
#include "stdafx.h"
#include "Player.h"


/* *********************************************************************
Function Name: Player
Purpose: The constructor of the class
Parameters:
			None
Assistance Received: none
********************************************************************* */
Player::Player() {

}

/* *********************************************************************
Function Name: ~Player
Purpose: The deconstructor of the class
Parameters:
			None
Assistance Received: none
********************************************************************* */
Player::~Player() {

}

/* *********************************************************************
Function Name: setTurn
Purpose: sets the turn for the human and comptuer class
Parameters:
			bool turn
Assistance Received: none
********************************************************************* */
void Player::setTurn(bool turn) {

	this->isTurn = turn;

}

/* *********************************************************************
Function Name: getIsTurn
Purpose: gets the turn
Parameters:
			None
Assistance Received: none
********************************************************************* */
bool Player::getIsTurn() {

	return this->isTurn;
}

/* *********************************************************************
Function Name: setScore
Purpose: Sets the score for the human and computer class
Parameters:
			int score
Assistance Received: none
********************************************************************* */
void Player::setScore(int score) {

	this->score = score;
}

/* *********************************************************************
Function Name: getScore
Purpose: Gets the score
Parameters:
			None
Assistance Received: none
********************************************************************* */
int Player::getScore() {

	return this->score;
}


/* *********************************************************************
Function Name: tripleCap
Purpose: Checks for a possible triple cap
Parameters:
			vector<Card> layout, vector<Card> deck, int &cardPosition
Local Variables: None
Algorithm: (1) Check for triple cap
			(2) Get the position of the first card in triple cap

Assistance Received: none
********************************************************************* */
bool Player::tripleCap(vector<Card> layout, vector<Card> deck, int& cardPosition) {

	int count = 0;

	// check to see if there are three matching cards
	for (int i = 0; i < layout.size(); i++) {
		for (int j = i + 1; j < layout.size(); j++) {

			if (layout[i].getFace() == layout[j].getFace()) {

				count++;
			}

			if (count == 2) {

				// Check if humanDeck has matching card
				for (int k = 0; k < deck.size(); k++) {

					if (layout[i].getFace() == deck[k].getFace()) {

						cardPosition = k;

						return true;
					}
				}
			}
		}
		count = 0;
	}
	return false;
}


/* *********************************************************************
Function Name: stackPair
Purpose: Finds stack pair
Parameters:
			vector<Card> layout, vector<Card> deck, vector<Card> capturePile,
			int& cardPosition
Local Variables: None
Algorithm: (1) Check for stack pair that can be matched with an already captured
			stackPair to get a point
			(2) Find a stack pair
			(3) Get position of card

Assistance Received: none
********************************************************************* */
bool Player::stackPair(vector<Card> layout, vector<Card> deck, vector<Card> capturePile, int& cardPosition) {

	/* Check to see if stackPair already captured that can be matched
	else return stack pair */

	int count = 0;

	for (int i = 0; i < layout.size(); i++) {
		for (int j = 0; j < deck.size(); j++) {

			if (layout[i].getFace() == deck[j].getFace()) {

				cardPosition = j;

				//If stack pair check if face is in capture pile to add point
				for (int k = 0; k < capturePile.size(); k++) {

					if (deck[j].getFace() == capturePile[k].getFace()) {

						count++;
					}
				}

				/* If stack pair will add point use, otherwise search
				for another card that will */
				if (count == 2 || count == 6) {

					return true;
				}
			}

			count = 0;

		}
	}

	if (cardPosition != 0) {

		return true;
	}

	return false;

}

/* *********************************************************************
Function Name: block
Purpose: Takes a possible stack pair away from enemy
Parameters:
			vector<Card> layout, vector<Card> deck, vector<Card> enemyCapturePile,
			int& cardPosition
Local Variables: None
Algorithm: (1) Looks to match with stackPair that enemy could use to get a point

Assistance Received: none
********************************************************************* */
bool Player::block(vector<Card> layout, vector<Card> deck, vector<Card> enemyCapturePile, int& cardPosition) {

	int count = 0;
	int blockCard;

	for (int i = 0; i < enemyCapturePile.size(); i++) {
		for (int j = i + 1; j < enemyCapturePile.size(); j++) {

			if (enemyCapturePile[i].getFace() == enemyCapturePile[j].getFace()) {

				count++;
			}
		}

		if (count == 2 || count == 6) {

			blockCard = i;
			break;

		}
		count = 0;
	}

	if (count == 2 || count == 6) {

		for (int i = 0; i < layout.size(); i++) {
			for (int j = 0; j < deck.size(); j++) {

				if ((layout[i].getFace() && deck[j].getFace()) == enemyCapturePile[blockCard].getFace()) {

					cardPosition = j;
					return true;
				}
			}
		}
	}

	
	return false;
}

/* *********************************************************************
Function Name: pairFromStockPile
Purpose: Looks to create a stackPair from stockPile match
Parameters:
			None
Local Variables: None
Algorithm: vector<Card> deck, vector<Card> stockPile, int& cardPosition

Assistance Received: none
********************************************************************* */
bool Player::pairFromStockPile(vector<Card> deck, vector<Card> stockPile, int& cardPosition) {

	for (int i = 0; i < deck.size(); i++) {

		if (stockPile[0].getFace() == deck[i].getFace()) {

			cardPosition = i;
			return true;
		}
	}

	return false;
}

/* *********************************************************************
Function Name: isStackPair
Purpose: Looks if stackPair already exists in layout or tripleCap
Parameters:
			vector<Card> layout, int cardPosition
Local Variables: None
Algorithm: None

Assistance Received: none
********************************************************************* */
bool Player::isStackPair(vector<Card> layout, int cardPosition) {

	if (cardPosition == 0) {

		return false;

	}

	else if (cardPosition + 1 >= layout.size()) {

		return false;
	}

	else if (layout[cardPosition - 1].cardMatcher() == "[") {

		return true;
	}

	else if (layout[cardPosition + 1].cardMatcher() == "]") {

		return true;
	}

	/* Check to make sure not triple cap as well */
	else if (layout[cardPosition - 1].getFace() == layout[cardPosition].getFace() &&
		layout[cardPosition + 1].getFace() == layout[cardPosition].getFace()) {

		/* make sure cardPosition is not out of range */
		if (cardPosition - 2 >= 0) {

			if (layout[cardPosition - 2].cardMatcher() == "[") {

				return true;
			}
		}


	}

	return false;

}

/* *********************************************************************
Function Name: stackPairMatchesStockPilee
Purpose: Looks if stockPile card will match with layoutCard for a stack Pair
Parameters:
			None
Local Variables: None
Algorithm: None

Assistance Received: none
********************************************************************* */
bool Player::stackPairMatchesStockPile(vector<Card> layout, vector<Card> stockPile) {

	for (int i = 0; i < layout.size(); i++) {

		if (layout[i].getFace() == stockPile[0].getFace()) {

			return true;
		}
	}

	return false;
}

/* *********************************************************************
Function Name: tripleCapPositions
Purpose: Returns positions of tripleCap
Parameters:
			vector<Card> layout, vector<Card> deck, int choosenCard, 
			int& layoutMatch1, int& layoutMatch2, int& layoutMatch3
Local Variables: None
Algorithm: (1) Checks for triple cap
			(2) Checks if triple cap matches selected card
			(3) returns positions of tripleCap

Assistance Received: none
********************************************************************* */
bool Player::tripleCapPositions(vector<Card> layout, vector<Card> deck, int choosenCard, int& layoutMatch1, int& layoutMatch2, int& layoutMatch3) {

	
	
	
	for (int i = 0; i < layout.size(); i++) {
		int j = i + 1;
		int k = j + 1;

		if (k + 1 < layout.size() && (i - 1) >= 0) {

			if (layout[i - 1].cardMatcher() == "[" &&
				layout[k + 1].cardMatcher() == "]") {

				if (layout[i].getFace() == layout[j].getFace() && layout[i].getFace()
					== layout[k].getFace()) {

					/* Checks if card in deck matches triple cap card*/
					if (deck[choosenCard].getFace() == layout[i].getFace()) {

						layoutMatch1 = i;
						layoutMatch2 = j;
						layoutMatch3 = k;	
						return true;
					}
	
				}
			}
		}

	}
	return false;
}


/* *********************************************************************
Function Name: Play
Purpose: Used for human GetHelp
Parameters:
			vector<Card> deckOfCards, vector<Card> layout, vector<Car> humanDeck,
			vector<Card> humanCapture, vector<Card> computerCapture

Strategy: capture four, capture two to get a point, capture two, block
Assistance Received: none
********************************************************************* */
void Player::play(vector<Card> stockPile, vector<Card> layout, vector<Card> humanDeck, vector<Card> humanCapture, vector<Card> computerCapture) {

	int cardPosition = 0;

	if (tripleCap(layout, humanDeck, cardPosition) == true) {

		cout << "I recommend you play: " << humanDeck[cardPosition].cardMatcher() << " to capture all four cards\n";
	}

	else if (stackPair(layout, humanDeck, humanCapture, cardPosition) == true) {

		cout << "I recommend you play: " << humanDeck[cardPosition].cardMatcher() << " to create a stack pair\n";
	}

	else if (pairFromStockPile(humanDeck, stockPile, cardPosition) == true) {

		cout << "I recommend you play: " << humanDeck[cardPosition].cardMatcher() << " to create a stack pair with the stock pile\n";

	}

	else if (block(layout, humanDeck, computerCapture, cardPosition) == true) {

		cout << "I recommend you play: " << humanDeck[cardPosition].cardMatcher() << " to block the computer from capturing the cards it needs\n";
	}

	else {

		cout << "I don't have recommendations sorry" << endl;

	}

	cout << endl;
	
}