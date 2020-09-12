#ifndef CARD_H
#define CARD_H

using namespace std;

class Card
{
public:

	Card(int face = 1, int suit = 1);
	Card(string s);
	~Card();

	/* Gettters */
	int getFace();
	int getSuit();

	void setFace(int face);
	void setSuit(int suit);

	void print();
	string cardMatcher();


private:

	int face, suit;
	string card;


};
#endif
