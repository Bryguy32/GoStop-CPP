/*************************************************************
* Name:  Bryan Francis
* Project : GoStop C++
* Class : OPL Spring 2020
* Date : 3/11/2020
*************************************************************/
#include "stdafx.h"
#include "Serialization.h"


/* *********************************************************************
Function Name: Serialization
Purpose: The constructor of the class
Parameters:
			None
Assistance Received: none
********************************************************************* */
Serialization::Serialization() {

}

/* *********************************************************************
Function Name: ~Serialization
Purpose: The deconstructor of the class
Parameters:
			None
Assistance Received: none
********************************************************************* */
Serialization::~Serialization() {

}

/* *********************************************************************
Function Name: setFileName
Purpose: Sets the file name
Parameters:
			string file
Assistance Received: none
********************************************************************* */
void Serialization::setFileName(string file) {

	filename = file;
}

/* *********************************************************************
Function Name: getRound
Purpose: gets the round from the file
Parameters:
			int &round
Assistance Received: none
********************************************************************* */

void Serialization::getRound(int &round) {

	inFile.open(filename);
	if (!inFile) {

		cerr << "File did not open" << endl;
		exit(1);
	}

	word = "";

	// Search for Round:	
	while (word.compare("Round:") != 0) {

		inFile >> word;

	}

	inFile >> word;
	round = atoi(word.c_str());


	inFile.close();
	
}

/* *********************************************************************
Function Name: getComputer
Purpose: gets the computer hands and score from the file
Parameters:
			int &score, vector<Card>& computerDeck, vector<Card>& computerCapture
Assistance Received: none
********************************************************************* */
void Serialization::getComputer(int& score, vector<Card>& computerDeck, vector<Card>& computerCapture) {

	inFile.open(filename);
	if (!inFile) {

		cerr << "File did not open" << endl;
		exit(1);
	}

	word = "";
	string str = "";


	while (word.compare("Computer:") != 0) {

		inFile >> word;
	}

	while (word.compare("Score:") != 0) {

		inFile >> word;

	}

	inFile >> word;
	score = atoi(word.c_str());

	word = "";
	str = "";

	// Copy ComputerHand into vector
	if (word.compare("Hand:") != 0) {

		inFile >> word;

		while (inFile >> str && str != "Capture") {

			computerDeck.push_back(Card(str));

		}
	}


	word = "";
	str = "";

	// Copy ComputerCapture into vector
	if (word.compare("Capture Pile:") != 0) {

		inFile >> word;

		while (inFile >> str && str != "Human:") {

			computerCapture.push_back(Card(str));

		}
	
	}

	inFile.close();
}


/* *********************************************************************
Function Name: getHuman
Purpose: gets the human hands and score from the file
Parameters:
			int &score, vector<Card> &humanDeck, vector<Card> &humanCapture
Assistance Received: none
********************************************************************* */
void Serialization::getHuman(int& score, vector<Card>& humanDeck, vector<Card>& humanCapture) {

	inFile.open(filename);
	if (!inFile) {

		cerr << "File did not open" << endl;
		exit(1);
	}

	word = "";
	string str = "";


	while (word.compare("Human:") != 0) {

		inFile >> word;
	}
	
	word = "";

	while (word.compare("Score:") != 0) {

		inFile >> word;

	}

	inFile >> word;
	score = atoi(word.c_str());

	word = "";
	str = "";

	// Copy ComputerHand into vector
	if (word.compare("Hand:") != 0) {

		inFile >> word;

		while (inFile >> str && str != "Capture") {

			humanDeck.push_back(Card(str));

		}
	}


	word = "";
	str = "";

	// Copy ComputerCapture into vector
	if (word.compare("Capture Pile:") != 0) {

		inFile >> word;

		while (inFile >> str && str != "Layout:") {

			humanCapture.push_back(Card(str));

		}
	}
	

	inFile.close();

}

/* *********************************************************************
Function Name: getLayout
Purpose: gets the layout from the file
Parameters:
			vector<Card>& layout
Assistance Received: none
********************************************************************* */
void Serialization::getLayout(vector<Card>& layout) {

	inFile.open(filename);
	if (!inFile) {

		cerr << "File did not open" << endl;
		exit(1);
	}

	word = "";
	string str = "";


	while (word.compare("Layout:") != 0) {

		inFile >> word;
	}

	while (inFile >> str && str != "Stock") {

		layout.push_back(Card(str));

	}

	

	inFile.close();

}

/* *********************************************************************
Function Name: getStockPile
Purpose: gets the stockPile from the file
Parameters:
			vector<Card>& deckOfCards
Assistance Received: none
********************************************************************* */
void Serialization::getStockPile(vector<Card>& deckOfCards) {

	inFile.open(filename);
	if (!inFile) {

		cerr << "File did not open" << endl;
		exit(1);
	}

	word = "";
	string str = "";

	while (word.compare("Stock") != 0) {

		inFile >> word;
	}


	while (word.compare("Pile:") != 0) {

		inFile >> word;
	}

	while (inFile >> str && str != "Next") {

		deckOfCards.push_back(Card(str));

	}



	inFile.close();

}

/* *********************************************************************
Function Name: isComputerTurn
Purpose: gets the next player to determine current player
Parameters:
			bool& isTurn
Assistance Received: none
********************************************************************* */
void Serialization::isComputerTurn(bool& isTurn) {

	inFile.open(filename);
	if (!inFile) {

		cerr << "File did not open" << endl;
		exit(1);
	}

	word = "";
	string str = "";

	while (word.compare("Next") != 0) {

		inFile >> word;
	}


	while (word.compare("Player:") != 0) {

		inFile >> word;
	}

	inFile >> word;

	if (word == "Computer") {

		isTurn = true;
	}

	else {

		isTurn = false;
	}


	inFile.close();

}

/* *********************************************************************
Function Name: saveGame
Purpose: Saves the game to a .txt file
Parameters: int round, int computerScore, vector<Card> computerDeck, 
			vector<Card> computerCapture, int humanScore,
			vector<Card> humanDeck, vector<Card> humanCapture, 
			vector<Card> layout, vector<Card> stockpile, bool isComputerTurn
			
Assistance Received: none
********************************************************************* */
void Serialization::saveGame(int round, int computerScore, vector<Card> computerDeck, vector<Card> computerCapture, int humanScore,
	vector<Card> humanDeck, vector<Card> humanCapture, vector<Card> layout, vector<Card> stockpile, bool isComputerTurn) {

	string fileName;

	cout << "Please enter a filename: ";
	cin >> fileName;

	outFile.open(fileName, ios::out | ios::trunc);

	if (!outFile) {

		cerr << "File did not open" << endl;
		exit(1);
	}

	outFile << "Round: " << round << "\n\n";

	outFile << "Computer:\n";
	outFile << "   Score: " << computerScore << "\n";

	outFile << "   Hand: ";
	for (int i = 0; i < computerDeck.size(); i++) {

		outFile << computerDeck[i].cardMatcher() << " ";
	}
	outFile << "\n";

	outFile << "   Capture Pile: ";
	for (int i = 0; i < computerCapture.size(); i++) {

		outFile << computerCapture[i].cardMatcher() << " ";
	}
	outFile << "\n\n";

	outFile << "Human:\n";
	outFile << "   Score: " << humanScore << "\n";

	outFile << "   Hand: ";
	for (int i = 0; i < humanDeck.size(); i++) {

		outFile << humanDeck[i].cardMatcher() << " ";
	}
	outFile << "\n";

	outFile << "   Capture Pile: ";
	for (int i = 0; i < humanCapture.size(); i++) {

		outFile << humanCapture[i].cardMatcher() << " ";
	}
	outFile << "\n\n";

	outFile << "Layout: ";
	for (int i = 0; i < layout.size(); i++) {

		outFile << layout[i].cardMatcher() << " ";
	}
	outFile << "\n\n";

	outFile << "Stock Pile: ";
	for (int i = 0; i < stockpile.size(); i++) {

		outFile << stockpile[i].cardMatcher() << " ";
	}
	outFile << "\n\n";

	if (isComputerTurn == false) {

		outFile << "Next Player: Human\n";
	}

	else if (isComputerTurn == true) {

		outFile << "Next Player: Computer\n";
	}


	outFile.close();

}