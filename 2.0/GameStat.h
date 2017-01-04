#ifndef GAMESTAT_H
#define GAMESTAT_H
#include "Player.h"


class GameStat: public Player
{
    public:
        GameStat(){}
        GameStat(int);

        //getters
        string getID(){return playerID;}
        int getBet(){return bet;}
        int getChips(){return chips;}
        bool getSplit(){return split;}

        //mutators
        void game(){++gameCount;}
        void win();
        void winBJ();
        void lose();
        void loseBJ();
        void push();
        void setBet();
        void doubleBet(){bet *= 2;}
        void swapSplit();

        void printChips();
        void printStats();


        //save current player deck
        void savePlayerHand(CardDeck* p);
        //
        void showPts();
        int sum();
        int size();
        bool getBJ();


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
        Player thisRun;
        Player thisRunSplit;
};

#endif // GAMESTAT_H
