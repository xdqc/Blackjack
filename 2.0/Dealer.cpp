#include "Dealer.h"

using namespace std;

Dealer::Dealer()
{

}

Dealer::Dealer(bool hit)
{
    //Casino Rule - "Dealer STAND at soft 17"
    while(sum() < 17){
        drawCard();
    }

    //Casino Rule - "Dealer HIT at soft 17"
    while(sum() == 17 && softAce > 0 && hit){
        do{
            drawCard();
        }while(sum() < 17);
    }

    show();

    if(vect.size() == 2 && sum() == 21){
        blackjack = true;
    }
    else{
        blackjack = false;
    }
}

void Dealer::drawCard(){
    vect.push_back(cardGen());
}

void Dealer::disCard(){
    vect.pop_back();
}

void Dealer::show(){
    cout << "  Dealer hand: ";

    if(!blackjack){
        //show two cards in dealer's hand. Hide the first one
        showHand(vect,2);
    }
    else{
        showHand(vect);
    }
}

void Dealer::showPts(){
    cout << "    Vs.\n  Dealer   ";
    showHand(vect);
    cout << setw(8) << "(" << sum() << "pts)" << endl << endl;
}

//return one card point
int Dealer::cardAt(int i){
    return showOneCard(vect, i);
}

