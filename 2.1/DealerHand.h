#pragma once
#include "CardHand.h"
class DealerHand :
	public CardHand
{
public:
	DealerHand() {};
	DealerHand(bool hitOn17)
	{
		do {
			drawCard();
		} while (sum() < 17);
		
		if (sum() == 17 && softAce && hitOn17) {
			do {
				drawCard();
			} while (sum() < 17);
		}

		cout << "  Dealer hand: ";
		if (blackjack()) {
			showHand();
			cout << "\n    ***    Dealer got Blackjack!    ***\n";
		}
		else {
			showHandMask();
		}
	}
	~DealerHand() {};
};

