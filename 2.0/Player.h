#ifndef PLAYER_H
#define PLAYER_H
#include "CardDeck.h"

using namespace std;

class Player: public CardDeck
{
    public:
        Player(){}

        Player(int);

        //copy constructor, used for splitting deck
        Player(Player &, bool);

        //add a card to hand
        void drawCard();

        //remove a card from hand
        void disCard();

        //sum up the total points
        int sum();

        //return number of cards in deck
        int size(){return numHand(vect);}

        //display cards at hand
        void show();

        //display cards and total points
        void showPts();

        //return one card point
        int cardAt(int);

        //return the card deck
        vector<Card> get(){return vect;}

        //return blackjack flag
        bool getBJ(){return blackjack;}

        //overload =, use for void GameStat::savePlayerHand(CardDeck* p)
        void operator=(CardDeck*);

    private:
        vector<Card> vect;
        bool blackjack;

};

#endif // PLAYER_H
