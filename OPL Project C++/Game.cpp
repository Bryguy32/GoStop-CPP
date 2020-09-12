/*************************************************************
* Name:  Bryan Francis
* Project : GoStop C++
* Class : OPL Spring 2020
* Date : 3/11/2020
*************************************************************/
#include "stdafx.h"
#include "Game.h"


/* *********************************************************************
Function Name: Game
Purpose: The constructor of the class
Parameters:
			None
Assistance Received: none
********************************************************************* */
Game::Game() {

}

/* *********************************************************************
Function Name: Start Game
Purpose: Starts the game, with a choice to start new game or load
a game
Parameters:
			None
Local Variables: Round round, Deck deck
Algorithm: None
Assistance Received: none
********************************************************************* */
void Game::startGame() {

	size_t choice;

	cout << "StopGo Starting" << endl;
	cout << "(1) Start new game" << endl;
	cout << "(2) Load game" << endl;
	cout << "Selection: ";

	do {
		cin >> choice;
		if (choice < 1 || choice > 2) {

			cout << "Sorry please enter a valid choice: ";
		}

	} while (choice < 1 || choice > 2);

	if (choice == 1) {

		round.setUpRound();
		round.determinePlayer();
		round.display();
	}
	else {

		resumeGame();
	}
}

/* *********************************************************************
Function Name: resumeGame
Purpose: resumes a game from a file
Parameters:
			None
Local Variables: None
Algorithm: None

Assistance Received: none
********************************************************************* */
void Game::resumeGame() {

	string filename;
	int roundnum, comScore, humanScore;
	bool isTurn;
	string cards;
	vector<Card> computerDeck, computerCapture;
	vector<Card> humanDeck, humanCapture;
	vector<Card> layout, deckOfCards;

	cout << " What is the name of the file you would like to resume: ";
	cin >> filename;
	cout << endl;
	cout << endl;
	
	file.setFileName(filename);

	file.getRound(roundnum);
	round.setRound(roundnum);

	file.getComputer(comScore, computerDeck, computerCapture);
	round.setComputerDeck(computerDeck);
	round.setComputerCapture(computerCapture);

	file.getHuman(humanScore, humanDeck, humanCapture);
	round.setHumanDeck(humanDeck);
	round.setHumanCapture(humanCapture);
	round.setScores(comScore, humanScore);

	file.getLayout(layout);
	round.setLayout(layout);

	file.getStockPile(deckOfCards);
	round.setStockPile(deckOfCards);

	file.isComputerTurn(isTurn);
	round.isComputerTurn(isTurn);
	
	round.display();


}
