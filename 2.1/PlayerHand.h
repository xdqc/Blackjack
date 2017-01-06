#pragma once
#include "CardHand.h"
class PlayerHand :
	public CardHand
{
public:
	PlayerHand() 
	{
		drawCard();
		drawCard();
		showHand();
	}
	//copy ctor for split situation
	PlayerHand(PlayerHand& obj) 
	{
		drawCardSplit(obj);
		drawCard();
		showHand();

		obj.disCard();
		obj.drawCard();
	}

	~PlayerHand() {};
};

