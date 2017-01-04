#include "Player.h"

using namespace std;


Player::Player(int n)
{
    //initialize the game
    for(int i = 0; i < n; i++){
        drawCard();
    }

    if(vect.size() == 2 && sum() == 21){
        blackjack = true;
    }
    else{
        blackjack = false;
    }

    show();
}

//copy constructor, used for splitting hand
Player::Player(Player &obj, bool first){

    if(first){
        vect.push_back(obj.vect.at(0));
    }
    else{
        vect.push_back(obj.vect.at(1));
    }

    this->drawCard();

    if(first)
        cout << "\nPlayer 1st hand: ";
    else
        cout << "\nPlayer 2nd hand: ";

    showHand(vect);

    if(vect.size() == 2 && sum() == 21){
        blackjack = true;
    }
    else{
        blackjack = false;
    }
}

void Player::drawCard(){
    vect.push_back(cardGen());
}

void Player::disCard(){
    vect.pop_back();
}

//sum up the total points
int Player::sum(){
    return sumHand(vect);
}

//display cards at hand
void Player::show(){
    showHand(vect);
}

//display cards and total points
void Player::showPts(){
    cout << "\nPlayer hand: ";
    showHand(vect);
    cout << "                             Player points = " << sum() << endl;
}

//return one card point
int Player::cardAt(int i){
    return showOneCard(vect, i);
}

//overload =
void Player::operator=(CardDeck* p){
    vect = p->get();
}
