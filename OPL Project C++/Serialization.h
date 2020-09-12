#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include "Card.h"

class Serialization
{

private:

	ifstream inFile;
	ofstream outFile;

	string filename;
	string word;

public:

	Serialization();
	~Serialization();

	void setFileName(string file);

	void getRound(int &round);
	void getComputer(int& score, vector<Card>& computerDeck, vector<Card>& computerCapture);
	void getHuman(int& score, vector<Card>& humanDeck, vector<Card>& humanCapture);
	void getLayout(vector<Card>& layout);
	void getStockPile(vector<Card>& deckOfCards);
	void isComputerTurn(bool& isTurn);

	void saveGame(int round, int computerScore, vector<Card> computerDeck, vector<Card> computerCapture, int humanScore,
		vector<Card> humanDeck, vector<Card> humanCapture, vector<Card> layout, vector<Card> stockpile, bool isComputerTurn);

};
#endif
