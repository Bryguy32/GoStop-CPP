/*************************************************************
* Name:  Bryan Francis
* Project : GoStop C++
* Class : OPL Spring 2020
* Date : 3/11/2020
*************************************************************/
#include "stdafx.h"
#include "Human.h"
#include "Player.h"


/* *********************************************************************
Function Name: Human
Purpose: The constructor of the class
Parameters:
			None
Assistance Received: none
********************************************************************* */
Human::Human() {

}

/* *********************************************************************
Function Name: ~Human
Purpose: The deconstructor of the class
Parameters:
			None
Assistance Received: none
********************************************************************* */
Human::~Human() {


}

/* *********************************************************************
Function Name: Play
Purpose: Makes a move for the human
Parameters:
			vector<Card> &deckOfCards, vector<Card> &layout, vectorMCard> &humanDeck
            vector<Card> &humanCapture
Local Variables: 

Algorithm: None
Assistance Received: none
********************************************************************* */
void Human::play(vector<Card> &deckOfCards, vector<Card> &layout, vector<Card> &humanDeck, vector<Card> &humanCapture) {

    int cardMatches = 0; // How many times the face of the card the user picked is in the stock pile
    int choosenCard = 0; // The location in the vector of the  card the user picked
    int layoutMatch1 = 0; // The first matching face card of the user pick in the layout
    int layoutMatch2 = 0; // The second match
    int layoutMatch3 = 0; // The third match
    int score = getScore();
    string playCard = "";
    bool isCard = false; // count as a card not a card from stackPair


    /** Card
     * Played
     * From
     * Hand
     */

    bool hasCard = false;

    // Check to make sure card is in deck
    do {

        cout << "Please choose a card: ";
        cin >> playCard;
        transform(playCard.begin(), playCard.end(), playCard.begin(), ::toupper);

       

        for (int i = 0; i < humanDeck.size(); i++) {

            if (humanDeck[i].cardMatcher() == playCard) {

                hasCard = true;
            }

        }
       

    } while (!hasCard);
    

    cout << "The card entered is: " << playCard << endl;



    /* Plays a card from hand */
    for (int i = 0; i < humanDeck.size(); i++) {

        if (humanDeck[i].cardMatcher() == playCard) {

            choosenCard = i;

            for (int j = 0; j < layout.size(); j++) {

                if (humanDeck[i].getFace() == layout[j].getFace()) {

                    // Check to make sure the card that matched is not a stack pair
                    if (isStackPair(layout, j) == false) {

                        cardMatches++;
                        isCard = true;

                    }

                    else if (isStackPair(layout, j) == true) {

                        isCard = false;
                    }

                    if (cardMatches == 1 && isCard == true) {

                        layoutMatch1 = j;

                    }

                    else if (cardMatches == 2 && isCard == true) {

                        layoutMatch2 = j;
                    }

                    else if (cardMatches == 3 && isCard == true) {

                        layoutMatch3 = j;
                    }


                }
            }

            break;
        }
    }



    /** The card is added to layout */
    if (cardMatches == 0 && 
        tripleCapPositions(layout, humanDeck, choosenCard, layoutMatch1, layoutMatch2, layoutMatch3) == false) {

        layout.push_back(humanDeck[choosenCard]);
        humanDeck.erase(humanDeck.begin() + choosenCard);

    }

    /** Creates stack pair which is left in layout */
    else if (cardMatches == 1) {

        // add cards to layout
        layout.push_back(Card(13, 4));
        layout.push_back(humanDeck[choosenCard]);
        layout.push_back(layout[layoutMatch1]);
        layout.push_back(Card(14, 4));

        humanDeck.erase(humanDeck.begin() + choosenCard);
        layout.erase(layout.begin() + layoutMatch1);

    }
    /** User picks one of the two to create stack pair */
    else if (cardMatches == 2) {

        cout << "Card to make a stack pair with: ";
        layout[layoutMatch1].print();
        layout[layoutMatch2].print();

        string stackCard = "";

        do {


            cout << "\nPlease choose a card: ";
            cin >> stackCard;
            transform(stackCard.begin(), stackCard.end(), stackCard.begin(), ::toupper);


            /** To know which card the user choose */
            if (layout[layoutMatch1].cardMatcher() == stackCard) {

                break;

            }

            else if (layout[layoutMatch2].cardMatcher() == stackCard) {

                layoutMatch1 = layoutMatch2;
                break;
            }

        } while (true);

        cout << "The card entered is: " << stackCard << endl;

        layout.push_back(Card(13, 4));
        layout.push_back(humanDeck[choosenCard]);
        layout.push_back(layout[layoutMatch1]);
        layout.push_back(Card(14, 4));


        humanDeck.erase(humanDeck.begin() + choosenCard);
        layout.erase(layout.begin() + layoutMatch1);


    }

    /** Three cards in layout or triple cap */

    else if (cardMatches == 3 || 
        tripleCapPositions(layout, humanDeck, choosenCard, layoutMatch1, layoutMatch2, layoutMatch3) == true) {
       
        /** three cards in layout */
        if (cardMatches == 3) {

            humanCapture.push_back(humanDeck[choosenCard]);
            humanCapture.push_back(layout[layoutMatch1]);
            humanCapture.push_back(layout[layoutMatch2]);
            humanCapture.push_back(layout[layoutMatch3]);

            humanDeck.erase(humanDeck.begin() + choosenCard);
            layout.erase(layout.begin() + layoutMatch3);
            layout.erase(layout.begin() + layoutMatch2);
            layout.erase(layout.begin() + layoutMatch1);
        }

        /** Three cards are in triple cap */
        else {

            humanCapture.push_back(humanDeck[choosenCard]);
            humanCapture.push_back(layout[layoutMatch1]);
            humanCapture.push_back(layout[layoutMatch2]);
            humanCapture.push_back(layout[layoutMatch3]);


            humanDeck.erase(humanDeck.begin() + choosenCard);
            /** Remove triple stack and "[" "]" from layout */
            layout.erase(layout.begin() + layoutMatch1 - 1, layout.begin() + layoutMatch1 + 4);

          
        }

        score++;
    }

    /** Card
     * Played
     * From
     * Stock
     * Pile
     */


    int layoutCardMatches = 0; // How many times the face of the card in the stock pile is in the layout
    layoutMatch1 = 0; // The first matching face card in the layout
    layoutMatch2 = 0; // The second match
    layoutMatch3 = 0; // The third match
    isCard = false; // count as a card


    for (int i = 0; i < layout.size(); i++) {

        if (deckOfCards[0].getFace() == layout[i].getFace()) {

            if (isStackPair(layout, i) == false) {

                layoutCardMatches++;
                isCard = true;
            }

            else if (isStackPair(layout, i) == true) {

                isCard = false;

            }
           
            if (layoutCardMatches == 1 && isCard == true) {

                layoutMatch1 = i;

            }

            else if (layoutCardMatches == 2 && isCard == true) {

                layoutMatch2 = i;
            }

            else if (layoutCardMatches == 3 && isCard == true) {

                layoutMatch3 = i;
            }


        } // End if

    } // end for


    if (cardMatches == 0 || cardMatches == 3) {

        if (layoutCardMatches == 0 &&
            tripleCapPositions(layout, deckOfCards, 0, layoutMatch1, layoutMatch2, layoutMatch3) == false) {

            layout.push_back(deckOfCards[0]);
            deckOfCards.erase(deckOfCards.begin() + 0);

        }

        
        else if (layoutCardMatches == 1) {

            /* Add cards */
            humanCapture.push_back(deckOfCards[0]);
            humanCapture.push_back(layout[layoutMatch1]);

            //Score
            int count = 0;
            for (int i = 0; i < humanCapture.size(); i++) {

                if (deckOfCards[0].getFace() == humanCapture[i].getFace()) {

                    count++;

                    // Possible to have all 8 cards
                    if (count == 4 || count == 8) {

                        score++;
                    }

                }

            }

             /* Erase cards */
            deckOfCards.erase(deckOfCards.begin() + 0);
            layout.erase(layout.begin() + layoutMatch1);

        }

        //Works
        else if (layoutCardMatches == 2) {

            cout << "Card to make a stack pair with: ";
            layout[layoutMatch1].print();
            layout[layoutMatch2].print();

            string stackCard = "";

            do {


                cout << "\nPlease choose a card: ";
                cin >> stackCard;
                transform(stackCard.begin(), stackCard.end(), stackCard.begin(), ::toupper);


                /** To know which card the user choose */
                if (layout[layoutMatch1].cardMatcher() == stackCard) {

                    break;

                }

                else if (layout[layoutMatch2].cardMatcher() == stackCard) {

                    layoutMatch1 = layoutMatch2;
                    break;
                }

            } while (true);

            cout << "The card entered is: " << stackCard << endl;

            /* Add cards */
            humanCapture.push_back(deckOfCards[0]);
            humanCapture.push_back(layout[layoutMatch1]);

            // Score
            int count = 0;
            for (int i = 0; i < humanCapture.size(); i++) {

                if (deckOfCards[0].getFace() == humanCapture[i].getFace()) {

                    count++;

                    // Possible to have all 8 cards
                    if (count == 4 || count == 8) {

                        score++;
                    }

                }

            }

            /* Erase cards */
            deckOfCards.erase(deckOfCards.begin() + 0);
            layout.erase(layout.begin() + layoutMatch1);

        }

        else if (layoutCardMatches == 3 ||
        tripleCapPositions(layout, deckOfCards, 0, layoutMatch1, layoutMatch2, layoutMatch3) == true) {

            /** three cards in layout */
            if (layoutCardMatches == 3) {

                humanCapture.push_back(deckOfCards[0]);
                humanCapture.push_back(layout[layoutMatch1]);
                humanCapture.push_back(layout[layoutMatch2]);
                humanCapture.push_back(layout[layoutMatch3]);

                /* Erase cards*/
                deckOfCards.erase(deckOfCards.begin() + 0);
                layout.erase(layout.begin() + layoutMatch3);
                layout.erase(layout.begin() + layoutMatch2);
                layout.erase(layout.begin() + layoutMatch1);
            }

            /** Three cards are in triple cap */
            else {

                humanCapture.push_back(deckOfCards[0]);
                humanCapture.push_back(layout[layoutMatch1]);
                humanCapture.push_back(layout[layoutMatch2]);
                humanCapture.push_back(layout[layoutMatch3]);

                /* Erase cards */
                deckOfCards.erase(deckOfCards.begin() + 0);
                /** Remove triple stack and "[" "]" from layout */
                layout.erase(layout.begin() + layoutMatch1 - 1, layout.begin() + layoutMatch1 + 4);
              
            }
            score++;
        }

    } // end if Card Matches == 0 || 3


    else if (cardMatches == 1 || cardMatches == 2) {

        /** Doesn't match layout cards or stacked pair  or triplestack*/
        if (layoutCardMatches == 0 &&
            stackPairMatchesStockPile(layout, deckOfCards) == false &&
            tripleCapPositions(layout, deckOfCards, 0, layoutMatch1, layoutMatch2, layoutMatch3) == false) {

            int count;
            count = layout.size();

            /** start end of vectors because the stack pair was just added
             * to the end
             */
            humanCapture.push_back(layout[count - 2]);
            humanCapture.push_back(layout[count - 3]);

            //score
            
            int scoreCount = 0;
            for (int i = 0; i < humanCapture.size(); i++) {

                if (layout[count - 2].getFace() == humanCapture[i].getFace()) {

                    scoreCount++;
                    // Possible to have all 8 cards
                    if (scoreCount == 4 || scoreCount == 8) {

                        score++;
                    }

                }

            }
         
            //Remove cards in layout that were moved to stack pair
            layout.erase(layout.end() - 4, layout.end());
        
            // Add card to layout
            layout.push_back(deckOfCards[0]);
            deckOfCards.erase(deckOfCards.begin() + 0);


        }

        else if (layoutCardMatches == 3 ||
            tripleCapPositions(layout, deckOfCards, 0, layoutMatch1, layoutMatch2, layoutMatch3) == true) {

            /** three cards in layout */
            if (layoutCardMatches == 3) {

                humanCapture.push_back(deckOfCards[0]);
                humanCapture.push_back(layout[layoutMatch1]);
                humanCapture.push_back(layout[layoutMatch2]);
                humanCapture.push_back(layout[layoutMatch3]);

                deckOfCards.erase(deckOfCards.begin() + 0);
                layout.erase(layout.begin() + layoutMatch3);
                layout.erase(layout.begin() + layoutMatch2);
                layout.erase(layout.begin() + layoutMatch1);
            }

            /** Three cards are in triple cap */
            else {

                humanCapture.push_back(deckOfCards[0]);
                humanCapture.push_back(layout[layoutMatch1]);
                humanCapture.push_back(layout[layoutMatch2]);
                humanCapture.push_back(layout[layoutMatch3]);

                deckOfCards.erase(deckOfCards.begin() + 0);
                /** Remove triple stack and "[" "]" from layout */
                layout.erase(layout.begin() + layoutMatch1 - 1, layout.begin() + layoutMatch1 + 4);

            }
            score++;


            /* Add stacked cards from H1/H2 */
            int count;
            count = layout.size();

            /** start end of vectors because the stack pair was just added
             * to the end
             */
            humanCapture.push_back(layout[count - 2]);
            humanCapture.push_back(layout[count - 3]);

            //score

            int scoreCount = 0;
            for (int i = 0; i < humanCapture.size(); i++) {

                if (layout[count - 2].getFace() == humanCapture[i].getFace()) {

                    scoreCount++;
                    // Possible to have all 8 cards
                    if (scoreCount == 4 || scoreCount == 8) {

                        score++;
                    }

                }

            }

            //Remove cards in layout that were moved to stack pair
            layout.erase(layout.end() - 4, layout.end());
        

        }

        else if (layoutCardMatches == 1 || layoutCardMatches == 2) {

        /* Add cards */
        humanCapture.push_back(deckOfCards[0]);
        humanCapture.push_back(layout[layoutMatch1]);

        /* Add stacked Pair */
        int count = layout.size();
        humanCapture.push_back(layout[count - 2]);
        humanCapture.push_back(layout[count - 3]);

        // Check for four matching cards from stock pile card
        int scoreCount = 0;
        for (int i = 0; i < humanCapture.size(); i++) {

            if (deckOfCards[0].getFace() == humanCapture[i].getFace()) {

                scoreCount++;
                // Possible to have all 8 cards
                if (scoreCount == 4 || scoreCount == 8) {

                    score++;
                }
            }
        }

        /* Check for four matching cards from stack pair
              only if stack pair and stock pile card are different */
        if (deckOfCards[0].getFace() != layout[count - 2].getFace()) {
            scoreCount = 0;
            for (int i = 0; i < humanCapture.size(); i++) {

                if (layout[count - 2].getFace() == humanCapture[i].getFace()) {

                    scoreCount++;
                    // Possible to have all 8 cards
                    if (scoreCount == 4 || scoreCount == 8) {

                        score++;
                    }

                }
            }

        }
       

            // Erase cards
            deckOfCards.erase(deckOfCards.begin() + 0);
            layout.erase(layout.begin() + layoutMatch1);
            layout.erase(layout.end() - 4, layout.end());
            
        }

        /** No match in layout just in stack pair */
        else if (layoutCardMatches == 0 &&
        stackPairMatchesStockPile(layout, deckOfCards) == true) {

        // Create triple stack
        vector<Card>::iterator it;
        it = layout.end() - 2;

        // Add element to stack before bracket
        layout.insert(it, deckOfCards[0]);

        // Delete from stock pile
        deckOfCards.erase(deckOfCards.begin() + 0);

        }

    } // end else if Card Matches == 1 || 2

    setScore(score);

}
