/*************************************************************
* Name:  Bryan Francis
* Project : GoStop C++
* Class : OPL Spring 2020
* Date : 3/11/2020
*************************************************************/
#include "stdafx.h"
#include "Round.h"


/* *********************************************************************
Function Name: Round
Purpose: The constructor of the class
Parameters:
			None
Assistance Received: none
********************************************************************* */
Round::Round() {

	deck = Deck();

	
}

/* *********************************************************************
Function Name: ~Round
Purpose: The deconstructor of the class
Parameters:
			None
Assistance Received: none
********************************************************************* */
Round::~Round() {

}

/* *********************************************************************
Function Name: setRound
Purpose: Sets the round
Parameters:
			int round
Assistance Received: none
********************************************************************* */
void Round::setRound(int round) {

	this->round = round;
}

/* *********************************************************************
Function Name: getRound
Purpose: Gets the round
Parameters:
			None
Assistance Received: none
********************************************************************* */
int Round::getRound() {

	return this->round;
}

/* *********************************************************************
Function Name: setHumanDeck
Purpose: sets the human hand
Parameters:
			Vector<Card>
Assistance Received: none
********************************************************************* */
void Round::setHumanDeck(vector<Card> humanDeck) {
	
	this->humanDeck = humanDeck;
}

/* *********************************************************************
Function Name: setcomputerDeck
Purpose: sets the computer hand
Parameters:
			Vector<Card>
Assistance Received: none
********************************************************************* */
void Round::setComputerDeck(vector<Card> computerDeck) {

	this->computerDeck = computerDeck;
}

/* *********************************************************************
Function Name: setHumanCapture
Purpose: sets the human capture hand
Parameters:
			Vector<Card>
Assistance Received: none
********************************************************************* */
void Round::setHumanCapture(vector<Card> humanCapture) {

	this->humanCapture = humanCapture;
}

/* *********************************************************************
Function Name: setComputerCapture
Purpose: sets the computer capture hand
Parameters:
			Vector<Card>
Assistance Received: none
********************************************************************* */
void Round::setComputerCapture(vector<Card> computerCapture) {

	this->computerCapture = computerCapture;
}

/* *********************************************************************
Function Name: setLayout
Purpose: sets the layout
Parameters:
			Vector<Card>
Assistance Received: none
********************************************************************* */
void Round::setLayout(vector<Card> layout) {

	this->layout = layout;
}

/* *********************************************************************
Function Name: setStockPile
Purpose: sets the stock pile
Parameters:
			Vector<Card>
Assistance Received: none
********************************************************************* */
void Round::setStockPile(vector<Card> deckOfCards) {

	this->deckOfCards = deckOfCards;
}

/* *********************************************************************
Function Name: setScores
Purpose: sets the human and computer score
Parameters:
			int comScore, int humanScore
Assistance Received: none
********************************************************************* */
void Round::setScores(int comScore, int humanScore) {

	computer.setScore(comScore);
	human.setScore(humanScore);
}

/* *********************************************************************
Function Name: isComputerTurn
Purpose: sets the players turns
Parameters:
			bool isTurn
Assistance Received: none
********************************************************************* */
void Round::isComputerTurn(bool isTurn) {

	if (isTurn == true) {

		computer.setTurn(true);
		human.setTurn(false);
	}

	else {

		computer.setTurn(false);
		human.setTurn(true);
	}

	
}

/* *********************************************************************
Function Name: setUpRound
Purpose: sets the deck for the initial round, takeing cards from the deck
and putting them in the human hand, computer hand, and layout.
Parameters:
			None
Local Variables: vector<Card> deckOfCards, humanDeck, computerDeck, layout
Algorithm: None
Assistance Received: none
********************************************************************* */
void Round::setUpRound() {

	deck.shuffleCards(); // Shuffle Deck
	/*
	Five Cards to human
	Five Cards to computer
	4 cards are placed face up in the layout
	5 Cards to human
	5 Cards to Computer
	4 cards placed face up in layout
	Remaining Cards are left in stock pile face down
	*/

	/* getting deck from deck class after each delete
	then setting the deck class after last delete*/

	// Make a second deck
	deckOfCards = deck.getDeck();
	vector<Card> newDeck;
	newDeck = deck.getDeck();
	deckOfCards.insert(deckOfCards.end(), newDeck.begin(), newDeck.end());

	
	
	//Shuffle combined decks
	srand(time(NULL));
	random_shuffle(deckOfCards.begin(), deckOfCards.end());
	deck.setDeck(deckOfCards);


	std::move(deckOfCards.begin(), deckOfCards.begin() + 5, back_inserter(humanDeck));
	deck.deleteFive();
	deckOfCards = deck.getDeck();

	// 5 Cards to computer
	std::move(deckOfCards.begin(), deckOfCards.begin() + 5, back_inserter(computerDeck));
	deck.deleteFive();
	deckOfCards = deck.getDeck();

	// Place 4 cards face up in layout
	std::move(deckOfCards.begin(), deckOfCards.begin() + 4, back_inserter(layout));
	deck.deleteFour();
	deckOfCards = deck.getDeck();

	// 5 Cards to human
	std::move(deckOfCards.begin(), deckOfCards.begin() + 5, back_inserter(humanDeck));
	deck.deleteFive();
	deckOfCards = deck.getDeck();

	// 5 Cards to computer
	std::move(deckOfCards.begin(), deckOfCards.begin() + 5, back_inserter(computerDeck));
	deck.deleteFive();
	deckOfCards = deck.getDeck();

	// Place 4 cards face up in layout
	std::move(deckOfCards.begin(), deckOfCards.begin() + 4, back_inserter(layout));
	deck.deleteFour();
	deckOfCards = deck.getDeck();

	deck.setDeck(deckOfCards);
}

/* *********************************************************************
Function Name: determinePlayer
Purpose: determines the player for the game.
Parameters:
			vector<Card> computerDeck, humanDeck
Local Variables: None
Algorithm: Sorts through the cards of the human and computer class one at a
time to see who as more kings. If the amount of kings is equal, then it moves
on to queens.
Assistance Received: none
********************************************************************* */
void Round::determinePlayer() {

	int computerHand = 0;
	int humanHand = 0;
	int highestCard = 12;

	// If the game started round based on who has better hand
	// Or if the score is tied
	if ((round == 1) || (computer.getScore() == human.getScore())) {

		do {
			for (unsigned i = 0; i < computerDeck.size(); i++) {

				/* 12 == King , 11 == Queen...*/
				/*Computer card matches highest card */
				if (computerDeck[i].getFace() == highestCard) {

					/*Human and computer card match highest card */
					if (humanDeck[i].getFace() == highestCard) {

						computerHand++;
						humanHand++;
					}
					else {

						computerHand++;
					}
				}
				/* Human card matches highest card*/
				else if (humanDeck[i].getFace() == highestCard) {

					humanHand++;
				}
			}

			/* All cards match game must start over*/
			if (highestCard == 0) {
				break;
			}
			highestCard--;

			/* While highest cards equal in both deck or cards completely match */
		} while (computerHand == humanHand);

		//setPlayers(human, computer);

		if (highestCard == 0) {

			cout << "All cards matched the game is starting Over. " << endl;
			dealAgain();

		}

		else if (computerHand > humanHand) {

			cout << "Computer Has the better hand and will start" << endl;
			cout << endl;
			computer.setTurn(true);
			human.setTurn(false);
		}

		else if (humanHand > computerHand) {

			cout << "Human has the better hand and will start" << endl;
			cout << endl;
			computer.setTurn(false);
			human.setTurn(true);
		}
	}

	/* Higher Score goes first */
	else if ((round > 1) && (computer.getScore() != human.getScore())) {

		if (computer.getScore() > human.getScore()) {
			computer.setTurn(true);
			human.setTurn(false);

		}
		else {

			computer.setTurn(false);
			human.setTurn(true);
		}
	}
}
/* *********************************************************************
Function Name: dealAgain
Purpose: returns all the cards back the deck, so they can be reshuffled
and delt again.
Parameters:
			None
Local Variables: vector<Card> humandDeck, deckOfCards, computerDeck
Algorithm: None
Assistance Received: none
********************************************************************* */
void Round::dealAgain() {
	/*Remove cards from all decks and start over */

	std::move(computerDeck.begin(), computerDeck.end(), back_inserter(deckOfCards));
	deckOfCards.erase(computerDeck.begin(), computerDeck.end());

	std::move(humanDeck.begin(), humanDeck.end(), back_inserter(deckOfCards));
	deckOfCards.erase(humanDeck.begin(), humanDeck.end());

	std::move(layout.begin(), layout.end(), back_inserter(deckOfCards));
	deckOfCards.erase(layout.begin(), layout.end());

	deck.setDeck(deckOfCards);
	

}
/* *********************************************************************
Function Name: display
Purpose: Displays the game.
Parameters:
			None
Local Variables: vector<Card> humanDeck, computerDeck, layout, deckOfCards
Algorithm: None
Assistance Received: none
********************************************************************* */
void Round::display() {

	cout << "----------------------" << endl;
	cout << "Round: " << round << endl;
	cout << endl;

	cout << "Computer:" << endl;
	cout << "   Score: " << computer.getScore() << endl;
	cout << "   Hand: ";
	deck.printVector(computerDeck);
	cout << endl;


	cout << "   Capture Pile: ";
	deck.printVector(computerCapture);
	cout << endl;
	cout << endl;

	cout << "Human: " << endl;
	cout << "   Score: " << human.getScore() << endl;
	cout << "   Hand: ";
	deck.printVector(humanDeck);
	cout << endl;

	cout << "   Capture Pile: ";
	deck.printVector(humanCapture);
	cout << endl;
	cout << endl;

	cout << "Layout: ";
	deck.printVector(layout);
	cout << endl;
	cout << endl;

	cout << "Stock Pile: ";
	deck.printVector(deckOfCards);
	cout << endl;
	cout << endl;


	cout << "Next Player: ";

	if (computer.getIsTurn() == true) {

		cout << "Computer" << endl;
		cout << endl;
		cout << "----------------------" << endl;
		
	}

	else {
		cout << "Human" << endl;
		cout << endl;
		cout << "----------------------" << endl;
	
	}

	menu();

}

/* *********************************************************************
Function Name: menu
Purpose: Displays the menu for the human player
Parameters:
			None
Local Variables: None
Algorithm: None
Assistance Received: none
********************************************************************* */
void Round::menu() {

	// If no more cards start new round
	if (computerDeck.size() == 0 && humanDeck.size() == 0) {

		nextRound();
	}

	else {

		checkHand();
	}

	if (computer.getIsTurn() == true) {

		computerMenu();
		return;
	}

	


	size_t choice;

	cout << "1. Save the game" << endl;
	cout << "2. Make a move" << endl;
	cout << "3. Ask for help" << endl;
	cout << "4. Quit the game" << endl;

	cout << "Selection: ";

	do {
		cin >> choice;
		if (choice < 1 || choice > 4) {
			cout << "Please enter a number 1 - 4: ";
		}
	} while (choice < 1 || choice > 4);

	if (choice == 1) {

		int computerScore = computer.getScore();
		int humanScore = human.getScore();
		bool isComputerTurn = computer.getIsTurn();

		s.saveGame(round, computerScore, computerDeck, computerCapture, humanScore, humanDeck,
			humanCapture, layout, deckOfCards, isComputerTurn);
		menu();
	}
	else if (choice == 2) {

		move();
	}
	else if (choice == 3) {

		player.play(deckOfCards, layout, humanDeck, humanCapture, computerCapture);
		menu();
	}
	else if (choice == 4) {

		endRound();

	}
}

/* *********************************************************************
Function Name: computerMenu
Purpose: Displays the menu for the computer 
Parameters:
			None
Local Variables: None
Algorithm: None
Assistance Received: none
********************************************************************* */
void Round::computerMenu() {

	size_t choice;
	cout << "1. Save Game" << endl; 
	cout << "2. Computer Move" << endl;
	cout << "3. Quit Game" << endl;
	cout << "Please choose: ";

	do {

		cin >> choice;
		if (choice < 1 || choice > 3) {
			cout << "Please enter a number 1 - 3: ";
		}
	} while (choice < 1 || choice > 3);

	if (choice == 1) {

		int computerScore = computer.getScore();
		int humanScore = human.getScore();
		bool isComputerTurn = computer.getIsTurn();

		s.saveGame(round, computerScore, computerDeck, computerCapture, humanScore, humanDeck,
			humanCapture, layout, deckOfCards, isComputerTurn);
		menu();
	}
	else if (choice == 2) {

		move();
	}
	else if (choice == 3) {

		endRound();
	}

}

/* *********************************************************************
Function Name: checkHand
Purpose: Switches the players if the player has no cards in hand.
Parameters:
			None
Assistance Received: none
********************************************************************* */
void Round::checkHand() {

	if (computer.getIsTurn() && computerDeck.size() == 0) {
		cout << "No cards in hand, switching players" << endl;
		cout << endl;
		switchPlayers();
		menu();
	}

	else if (human.getIsTurn() && humanDeck.size() == 0) {
		cout << "No cards in hand, switching players" << endl;
		cout << endl;
		switchPlayers();
		menu();
	}


}



/* *********************************************************************
Function Name: switchPlayers
Purpose: Switches the players for each round.
Parameters:
			None
Assistance Received: none
********************************************************************* */
void Round::switchPlayers() {

	computer.setTurn(!computer.getIsTurn());
	human.setTurn(!human.getIsTurn());
}

/* *********************************************************************
Function Name: move
Purpose: Makes the move for the players
Parameters:
			None
Local Variables: None
Algorithm: None
Assistance Received: none
********************************************************************* */
void Round::move() {


	if (computer.getIsTurn() == true) {

		computer.play(deckOfCards, layout, computerDeck, computerCapture, humanCapture);
	
	}

	else {

		human.play(deckOfCards, layout, humanDeck, humanCapture);

	}

	switchPlayers();
	display();
}

/* *********************************************************************
Function Name: nextRound
Purpose: Start the next round
Parameters:
			None
Local Variables: None
Algorithm: None
Assistance Received: none
********************************************************************* */
void Round::nextRound() {

	string str;

	do {

		cout << "The round is over would you like to play another round? (Yes or No): ";
		cin >> str;
		transform(str.begin(), str.end(), str.begin(), ::toupper);


	} while (str != "YES" && str != "NO");


	if (str == "YES") {

		computerDeck.clear();
		humanDeck.clear();
		layout.clear();
		deckOfCards.clear();
		humanCapture.clear();
		computerCapture.clear();

		round++;

		setUpRound();
		determinePlayer();
		display();


	}

	else {

		endRound();
	}

}


/* *********************************************************************
Function Name: endRound
Purpose: Ends the game
Parameters:
			None
Local Variables: None
Algorithm: None
Assistance Received: none
********************************************************************* */
void Round::endRound() {

	if (computer.getScore() > human.getScore()) {

		cout << "Sorry computer won :( better luck next time!" << endl;

	}

	else if (computer.getScore() == human.getScore()) {

		cout << "Tie Game!" << endl;
	}

	else {

		cout << "Congrats you won!" << endl;
	}

	exit(0);
}




