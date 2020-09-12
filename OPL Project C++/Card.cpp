/*************************************************************
* Name:  Bryan Francis
* Project : GoStop C++
* Class : OPL Spring 2020
* Date : 3/11/2020
*************************************************************/

#include "stdafx.h"
#include "Card.h"

const string faceNames[15] = { "1","2","3","4","5","6","7","8","9","X","J","Q","K", "[", "]" };
const string suitNames[5] = { "H", "C", "D", "S", "" };


/* *********************************************************************
Function Name: Card
Purpose: The constructor of the class
Parameters:
			int face, int suit
Assistance Received: none
********************************************************************* */
Card::Card(int face, int suit) {

	this->face = face;
	this->suit = suit;

}

/* *********************************************************************
Function Name: Card
Purpose: The constructor of the class
Parameters:
			string s
Assistance Received: none
********************************************************************* */
Card::Card(string s) {

	for (int i = 0; i < 13; i++) {

		for (int j = 0; j < 4; j++) {

			if ((faceNames[i] + suitNames[j]) == s) {

				setFace(i);
				setSuit(j);
			}
		}
	}

}

/* *********************************************************************
Function Name: ~Card
Purpose: The deconstructor of the class
Parameters:
			int face, int suit
Assistance Received: none
********************************************************************* */
Card::~Card() {

	// Nothing for now
}

/* *********************************************************************
Function Name: getFace
Purpose: returns the face of the card
Parameters:
			None
Assistance Received: none
********************************************************************* */
int Card::getFace() {

	return this->face;
}

/* *********************************************************************
Function Name: getSuit
Purpose: The returns the suit of the card
Parameters:
			None
Assistance Received: none
********************************************************************* */
int Card::getSuit() {

	return this->suit;
}

/* *********************************************************************
Function Name: setFace
Purpose: Sets the face
Parameters:
			int face
Assistance Received: none
********************************************************************* */
void Card::setFace(int face) {

	this->face = face;

}

/* *********************************************************************
Function Name: setSuit
Purpose: Sets the suit
Parameters:
			int suit
Assistance Received: none
********************************************************************* */
void Card::setSuit(int suit) {

	this->suit = suit;
}

/* *********************************************************************
Function Name: Print
Purpose: prints the card as a face followed by a suit
Parameters:
			None
Assistance Received: http://www.cplusplus.com/forum/general/94712/
********************************************************************* */
void Card::print() {

	cout << faceNames[face] + suitNames[suit] << " ";

}

/* *********************************************************************
Function Name: cardMatcher
Purpose: returns the card as a face followed by a suit
Parameters:
			None
Assistance Received: none
********************************************************************* */
string Card::cardMatcher() {

	return faceNames[face] + suitNames[suit];

}
