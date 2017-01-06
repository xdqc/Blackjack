/*
 BlackJack v2.1
 
 */

#include "CardHand.h"
#include "DealerHand.h"
#include "PlayerHand.h"
#include "GameStat.h"
#include "MakeChoice.h"
#include <list>
#include <algorithm>
using namespace std;

int main();

//runs one roundl of the game
void runOneRound(list<GameStat>&, bool);

//runs one player's turn
void runOnePlayer(shared_ptr<DealerHand>, GameStat&);

//runs one hand game of a player
void playOneHand(shared_ptr<DealerHand>, shared_ptr<PlayerHand> , MakeChoice &, GameStat&);

//define maximum players
const int MAX_PLAYER = 9;


int main()
{
	srand(time(0));

	cout << "\t ......    Welcome to BlackJack!    ......\n\n";

	//ask for Casino rule
	cout << "Choose level: ( 0.Easy : 1.Hard ) ";
	bool hitSoft17;
	cin >> hitSoft17;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\n\tCasino Rule - Dealer *" << (hitSoft17 ? "HIT" : "STAND") << "* at soft 17\n\n";

	//ask for multi player
	cout << "How many players? (1~"<<MAX_PLAYER<<") ";
	int pNumber;
	cin >> pNumber;
	if (pNumber < 1 || pNumber > MAX_PLAYER) {
		pNumber = 1;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	//setup player's game stats
	list<GameStat>gamers;
	for (int i = 0; i < pNumber; i++) {
		gamers.push_back(GameStat(i));
	}


	//run the game
	do {
		runOneRound(gamers, hitSoft17);
		//remove player who lost all chips
		gamers.remove_if([](GameStat& g) {return g.getChips() <= 0; });
		system("PAUSE");
	} while (gamers.size() > 0);

	return 0;
}

//runs one roundl of the game
void runOneRound(list<GameStat>& gamers, bool hitSoft17)
{
	cout << "\n\n\tNew Round....\n\n";
	//let each player set bet
	for (GameStat& g : gamers) {
		g.printChips();
		g.setBet();
	}
	//Dealer draw cards
	auto d = make_shared<DealerHand>(hitSoft17);

	//player move, take turns
	for (GameStat& g : gamers) {            /*Beware to use ref& in the rage based declaration*/
		if (gamers.size() > 1) {
			cout << "\n--------------------------------------------------\n";
			cout << "\n  < " << g.getID() << " > 's turn...\n";
			cout << "  Dealer hand: ";
			d->showHandMask();
		}
		runOnePlayer(d, g);
	}
	cout << "\n> > > > > > > Dealer draws " << d->size() - 2 << " card > > > > > > >  \n";
	cout << "\nPress ENTER to show results . . .";
	cin.get();
	cout << "\n=================== Results ======================\n";

	//display results of this round
	for (GameStat& g : gamers) {
		g.saveDealerHand(d);
		//display player and dealer's total points
		g.showPts();

		//display winner
		if (!g.getSplit()) {
			g.winner();
		}
		else {
			g.swapSplit();
			g.winner();
			g.swapSplit();
			g.winner();
		}
		g.printStats();
		if (g.getChips() <= 0) {
			cout << "\n\t" << g.getID() << " Lost All Money \t... GAME OVER ...\n";
		}
		cout << "__________________________________________________\n";
	}
}

//runs one player's turn
void runOnePlayer(shared_ptr<DealerHand> d, GameStat& g) 
{
	cout << "\n" << setw(8) << g.getID() << " hand: ";
	auto p = make_shared<PlayerHand>();
	MakeChoice c;

	// at[A][A] scenario, the value of these two cards differers 10, with one automatically soften
	if (p->duplicate() && g.getBet() * 2 <= g.getChips()) {
		c.showSplitChoice();
		if (c.getSplit()) {
			//split, create a new hand
			cout << "\n" << setw(8) << g.getID() << "-hand: ";
			auto p1 = make_shared<PlayerHand>(*p);
			playOneHand(d, p1, c, g);

			//clear split and double flag
			c.clrSplit();
			c.clrDouble();
			//swap bet between two hands
			g.swapSplit();

			//another hand
			cout << "\n" << setw(8) << g.getID() << "-hand: ";
			p->showHand();
			playOneHand(d, p, c, g);
		}
		else {
			playOneHand(d, p, c, g);
		}
	}
	else {
		playOneHand(d, p, c, g);
	}
}

//runs one hand game of a player
void playOneHand(shared_ptr<DealerHand> d, shared_ptr<PlayerHand> p, MakeChoice &c, GameStat& g) {
	//test Blackjack
	if (p->blackjack()) {
		cout << "\n      ***    You got Blackjack!    ***\n";
	}
	else if (d->blackjack()) {}

	//ask for player choice
	else {
		g.getBet() * 2 <= g.getChips() ? c.showFirstChoice() : c.showChoice();

		while (!c.getStand()) {
			p->drawCard();
			cout << "\n" << setw(8) << g.getID() << " hand: ";
			p->showHand();
			if (p->sum() >= 21)
				break;
			c.showChoice();
		}

		if (c.getDouble()) {
			g.doubleBet();
			p->drawCard();
			cout << "\n" << setw(8) << g.getID() << " hand: ";
			p->showHand();
			
		}
		cout << endl;
	}
	//save this hand to game stat, for later winner determination
	g.savePlayerHand(p);       /*beware of dangling pointer! use shared_ptr to avoid this issue*/
}

