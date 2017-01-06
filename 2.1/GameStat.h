#pragma once
#include "PlayerHand.h"
#include "DealerHand.h"

class GameStat
{
    public:
        GameStat(int);
        ~GameStat(){}

        //getters
        string getID(){return playerID;}
        int getBet(){return bet;}
        int getChips(){return chips;}
        bool getSplit(){return split;}

        //mutators
        void setBet();
        void doubleBet(){bet *= 2;}
        void swapSplit();

        void printChips();
        void printStats();
        void showPts();
		//decide winner
		void winner();

        //save current player deck
		void savePlayerHand(shared_ptr<PlayerHand> p) { split ? thisRunSplit = p : thisRun = p; }
		void saveDealerHand(shared_ptr<DealerHand> d) { thisDealer = d; }

		int dSum() { return thisDealer->sum(); }
		int pSum() { return split ? thisRunSplit->sum() : thisRun->sum(); }
		bool dBlackjack() { return (thisDealer->size() == 2 && thisDealer->sum() == 21); }
		bool pBlackjack() {
			return split ? (thisRunSplit->size() == 2 && thisRunSplit->sum() == 21)
						 : (thisRun->size() == 2 && thisRun->sum() == 21);
		}


    private:
        string playerID;
        int gameCount;
        int winCount;
        int loseCount;
        int pushCount;
        int chips;
        int bet;
        int splitBet;
        bool split;

        //store the info of players hand of current run
        shared_ptr<PlayerHand> thisRun;
        shared_ptr<PlayerHand> thisRunSplit;
		shared_ptr<DealerHand> thisDealer;
};

