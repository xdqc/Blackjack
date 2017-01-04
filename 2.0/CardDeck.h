#ifndef CARDECK_H
#define CARDECK_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

struct Card
{
    string digit;
    char suit;
    int value;
    bool soft;
    void enSoft(){
        if(digit == "A" && !soft){
            value = 11;
            soft = true;
        }
    }
    void deSoft(){
        if(digit == "A" && soft){
            value = 1;
            soft = false;
        }
    }
};

//Abstract Base Class
class CardDeck
{
    public:
        CardDeck();

        //generate a random card from infinite card pool
        Card cardGen();

        //generate a 52-card decks
        vector<Card> cardDeckGen();

        //return one card
        Card getCard(vector<Card>*vect, int i){return vect->at(i);}

        //return all cars in hand
        vector<Card> getHand(vector<Card>*vect){return *vect;}

        //sum up the total points
        int sumHand(vector<Card> &);

        //return number of cards in hand
        int numHand(vector<Card> &) const;

        //display cards in hand
        void showHand(vector<Card> &) ;
        //display two cards in dealer's hand. Hide the first one
        void showHand(vector<Card> &, int) ;

        //display the value of one card
        int showOneCard(vector<Card> &, int) const;

        //polymorphism - pure virtual functions
        //return total points
        virtual int sum()=0;
        //return how many cards at hand
        virtual int size()=0;
        //return card point at position
        virtual int cardAt(int)=0;
        //display all cards at hand
        virtual void show()=0;
        //display all cards at hand and total points
        virtual void showPts()=0;
        //draw a card
        virtual void drawCard()=0;
        //through the latest card
        virtual void disCard()=0;
        //return the card deck
        virtual vector<Card> get()=0;
        //return blackjack flag
        virtual bool getBJ()=0;

    protected:
        int softAce;
};

#endif // CARDECK_H
