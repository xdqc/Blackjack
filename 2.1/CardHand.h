#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <memory>

using namespace std;

struct Card
{
	string digit;
	char suit;
	int value;
};

class CardHand
{
public:
	CardHand() : softAce(false){};
	~CardHand() {};

	int size() { return cards.size(); }
	//sum up the total point of hand
	int sum();

	//display cards in hand
	void showHand();
	void showHandMask();

	//Draw a card
	void drawCard() { cards.push_back(cardGen()); }
	void drawCardSplit(const CardHand& rhs) { cards.push_back(rhs.cards[1]); }
	void disCard() { cards.pop_back(); }

	bool blackjack() { return size() == 2 && sum() == 21; }
	bool duplicate() { return cards[0].value == cards[1].value; }


protected:
	bool softAce;


private:

	vector<Card> cards;
	//Generate a random card
	Card cardGen();
};

