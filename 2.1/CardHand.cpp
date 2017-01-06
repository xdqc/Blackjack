#include "CardHand.h"

Card CardHand::cardGen()
{
	Card rawCard;
	int point = rand() % 13 + 1;
	if (point > 1 && point <= 10){
		stringstream sstream;
		sstream << point;
		sstream >> rawCard.digit;
		rawCard.value = point;
	}
	else if (point == 1){
		rawCard.digit = "A";
		rawCard.value = 1;
	}
	else{
		rawCard.value = 10;
		if (point == 11)
			rawCard.digit = "J";
		else if (point == 12)
			rawCard.digit = "Q";
		else
			rawCard.digit = "K";
	}

	switch (rand()%4)
	{
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
	default:
		break;
	}

	return rawCard;
}

int CardHand::sum()
{
	int sum = 0;
	softAce = false;
	for (const Card &c : cards)
	{
		if (c.digit == "A" && softAce == false){
			sum += 10;
			softAce = true;
		}
		sum += c.value;
		if (sum > 21 && softAce == true) {
			sum -= 10;
			softAce = false;
		}
	}
	return sum;
}

void CardHand::showHand()
{
	for (const Card& c : cards) {
		cout << " [" << c.digit << c.suit << "] ";
	}
}

void CardHand::showHandMask()
{
	cout << " [**]  [" << cards.at(1).digit << cards.at(1).suit << "] ";
}
