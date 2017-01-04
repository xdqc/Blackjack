#include "CardDeck.h"

using namespace std;

CardDeck::CardDeck(){
    softAce = 0;
}

Card CardDeck::cardGen()
{
    Card rawCard;
    int point = rand()%13 + 1;

    //assign card value
    if(point <= 10){
        rawCard.value = point;
    }
    else{
        //make J Q K card = 10
        rawCard.value = 10;
    }

    //assign card digit
    switch(point){
        case 1:
            rawCard.digit = "A";
            break;
        case 2:
            rawCard.digit = "2";
            break;
        case 3:
            rawCard.digit = "3";
            break;
        case 4:
            rawCard.digit = "4";
            break;
        case 5:
            rawCard.digit = "5";
            break;
        case 6:
            rawCard.digit = "6";
            break;
        case 7:
            rawCard.digit = "7";
            break;
        case 8:
            rawCard.digit = "8";
            break;
        case 9:
            rawCard.digit = "9";
            break;
        case 10:
            rawCard.digit = "10";
            break;
        case 11:
            rawCard.digit = "J";
            break;
        case 12:
            rawCard.digit = "Q";
            break;
        case 13:
            rawCard.digit = "K";
            break;
    }

    //assign card suit
    int i = rand()%4;
    switch(i){
        case 0:
            rawCard.suit = 3;
            break;
        case 1:
            rawCard.suit = 4;
            break;
        case 2:
            rawCard.suit = 5;
            break;
        case 3:
            rawCard.suit = 6;
            break;
    }

    rawCard.soft = false;

    return rawCard;
}

vector<Card> CardDeck::cardDeckGen()
{
    vector<Card>oneDeck;
    Card rawCard;
    int point;
    int suit;

    for(point = 1; point <= 13; point++){
        //assign card value
        if(point <= 10){
            rawCard.value = point;
        }
        else{
            //make J Q K card = 10
            rawCard.value = 10;
        }

        //assign card digit
        switch(point){
            case 1:
                rawCard.digit = "A";
                break;
            case 2:
                rawCard.digit = "2";
                break;
            case 3:
                rawCard.digit = "3";
                break;
            case 4:
                rawCard.digit = "4";
                break;
            case 5:
                rawCard.digit = "5";
                break;
            case 6:
                rawCard.digit = "6";
                break;
            case 7:
                rawCard.digit = "7";
                break;
            case 8:
                rawCard.digit = "8";
                break;
            case 9:
                rawCard.digit = "9";
                break;
            case 10:
                rawCard.digit = "10";
                break;
            case 11:
                rawCard.digit = "J";
                break;
            case 12:
                rawCard.digit = "Q";
                break;
            case 13:
                rawCard.digit = "K";
                break;
        }

        //assign card suit
        for(suit = 0; suit < 3; suit++){
            switch(suit){
                case 0:
                    rawCard.suit = 3;
                    break;
                case 1:
                    rawCard.suit = 4;
                    break;
                case 2:
                    rawCard.suit = 5;
                    break;
                case 3:
                    rawCard.suit = 6;
                    break;
            }
            rawCard.soft = false;

            oneDeck.push_back(rawCard);
        }
    }

    return oneDeck;
}


int CardDeck::sumHand(vector<Card> &cards)
{
    int sum = 0;
    //hold index of soft Aces
    vector<int>softIndex;

    for(unsigned i = 0; i < cards.size(); i++){
        //if possible, make the Ace soft as 11
        cards[i].enSoft();
        if(cards[i].soft){
            softIndex.push_back(i);
        }

        sum += cards[i].value;

        //to prevent bust, make soft Ace(11) back to hard Ace(1)
        if(sum > 21 && softIndex.size() > 0){
            sum -= 10;
            cards[softIndex.back()].deSoft();
            softIndex.pop_back();
        }
    }
    softAce = softIndex.size();
    softIndex.clear();
    return sum;
}

int CardDeck::numHand(vector<Card> &vect) const
{
    return vect.size();
}



void CardDeck::showHand(vector<Card> &vect)
{
    for(unsigned i = 0; i < vect.size(); i++)
    {
        cout << " [" << vect[i].digit << vect[i].suit << "] ";
    }
}

void CardDeck::showHand(vector<Card> &vect, int showNum)
{
    cout << " [**] ";

    for(int i = 1; i < showNum; i++)
    {
        cout << " [" << vect[i].digit << vect[i].suit << "] ";
    }
}

//display the point of one card
int CardDeck::showOneCard(vector<Card> &vect, int index) const
{
    return vect[index].value;
}

