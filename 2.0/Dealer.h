#ifndef DEALER_H
#define DEALER_H
#include "CardDeck.h"

using namespace std;

class Dealer: public CardDeck
{
    public:
        //default constructor
        Dealer();

        //dealer stand hit/stand at soft 17
        Dealer(bool);

        //add a card to hand
        void drawCard();

        //remove a card from hand
        void disCard();

        //return one card point
        int cardAt(int );

        //sum up the total points
        int sum(){return sumHand(vect);}

        //return number of cards in deck
        int size(){return numHand(vect);}

        //display cards at hand
        void show();

        //display cards and total points
        void showPts();

        //return the card deck
        vector<Card> get(){return vect;}

        //return blackjack flag
        bool getBJ(){return blackjack;}

    private:
        vector<Card> vect;
        bool blackjack;
};


#endif // DEALER_H
