/*
BlackJack v2.0


*/
#include "CardDeck.h"
#include "Dealer.h"
#include "Player.h"
#include "GameStat.h"
#include "MakeChoice.h"

using namespace std;

//basic function runs single game
void runOnePlayer(CardDeck* d, GameStat* g);

//basic function runs one hand game
void playOneHand(CardDeck* d, CardDeck* p, MakeChoice &c, GameStat *g);

//decide the winner
void winner(CardDeck* d, GameStat* g);




int main()
{
    unsigned seed = time(0);
    srand(seed);

    cout << " ......    Welcome to BlackJack!    ......\n\n";

    //ask for Casino rule
    cout << "Choose level: ( 0 = Easy / 1 = Hard )";
    bool hitSoft17;
    cin >> hitSoft17;
    cin.clear();
    cin.ignore(1000,'\n');
    if(hitSoft17){
        cout << "\tCasino Rule - Dealer HIT at soft 17\n\n";
    }
    else{
        cout << "\tCasino Rule - Dealer STAND at soft 17\n\n";
    }


////test zone/////////////////////////////////////////////////////////////////////////
//
//    double total = 100;
//    int test = 1000;
//
//    int standBustMore = 0;
//    int standBjMore = 0;
//    CardDeck* d;
//    for(int i=0; i< test;i++){
//        int bustH17 = 0;
//        int bustS17 = 0;
//        int bjH17 = 0;
//        int bjS17 = 0;
//        for(int i=0;i<total;i++){
//            Dealer dealerDeck(hitSoft17);
//            d = &dealerDeck;
//            if(d->sum()>21){
//                bustH17++;
//            }
//            if(d->sum()>=20 && d->size()>=2){
//                bjH17++;
//            }
//        }
//        //cout << "Hit17 Bust rate " << bustH17/total <<endl;
//
//        for(int i=0;i<total;i++){
//            Dealer dealerDeck(!hitSoft17);
//            d = &dealerDeck;
//            if(d->sum()>21){
//                bustS17++;
//            }
//            if(d->sum()>=20 && d->size()>=2){
//                bjS17++;
//            }
//        }
//        //cout << "Stand bust rate " << bustS17/total <<endl<<endl;
//        if(bustH17<bustS17){
//            standBustMore++;
//        }
//        if(bjH17<bjS17){
//            standBjMore++;
//        }
//    }
//    cout << "Stand bust more " << standBustMore << " / " << test << " test of " << total << endl <<endl;
//    cout << "Stand Blackjack more " << standBjMore << " / " << test << " test of " << total << endl <<endl;
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////


    //ask for multi player
    cout << "How many players? ";
    int pNumber;
    cin >> pNumber;
    if(pNumber < 1){
        pNumber = 1;}
    cin.clear();
    cin.ignore(1000,'\n');

    //setup player's game stats
    vector<GameStat>gamers;
    for(int i = 0; i < pNumber; i++){
        gamers.push_back(GameStat(i));
    }
    GameStat* g;


    //run the game
    do{
        cout << "\n\n  New Game....\n\n";
        //let player set bet
        for(int i = 0; i < pNumber; i++){
            g = &gamers[i];
            g->printChips();
            g->setBet();
        }

        //Dealer draw cards
        Dealer dealerDeck(hitSoft17);
        CardDeck* d = &dealerDeck;
        if(d->getBJ()){
            cout << "\n    ***    Dealer got Blackjack!    ***\n";
        }

        //player draw cards
        for(int i = 0; i < pNumber; i++){
            g = &gamers[i];
            if(pNumber>1){
                cout << "\n-------------------------------------------------\n";
                cout << "\n  < " << g->getID() << " > 's turn...\n";
                d->show();
            }
            runOnePlayer(d, g);
            cout << endl;
            system("PAUSE");
        }

        cout << "\n> > > > > > > Dealer draw " << d->size() -2 << " cards > > > > > > >  \n";
        cout << "\n====================Results======================\n";

        //display results of this round
        for(int i = 0; i < pNumber; i++){
            g = &gamers[i];

            //display player and dealer's total points
            g->showPts();
            d->showPts();

            //display winner
            if(!g->getSplit()){
                winner(d, g);
            }
            else{
                g->swapSplit();
                winner(d, g);
                g->swapSplit();
                winner(d, g);
            }
            g->printStats();

            //remove player who lost all chips out of the loop
            if(g->getChips() <= 0){
                cout << "\n          ... " << g->getID() << " GAME OVER ...\n";
                gamers.erase(gamers.begin()+i);
                pNumber--;
                i--;
            }
            cout << "_________________________________________________\n";
        }
        system("PAUSE");

    }while(pNumber>0);

    return 0;
}




//basic function runs single game
void runOnePlayer(CardDeck* d, GameStat* g){

    cout << "\n" << setw(8) << g->getID() << " hand: ";
    Player playerDeck(2);
    Player* p = &playerDeck;

    MakeChoice c;

    if(p->cardAt(0) == p->cardAt(1) && g->getBet()*2 <= g->getChips()){
        c.showSplitChoice();
        if(c.getSplit()){
            //split, create a new hand
            Player playerDeck1(playerDeck , true);
            p = &playerDeck1;
            playOneHand(d, p, c, g);

            //clear split and double flag
            c.clrSplit();
            c.clrDouble();
            //swap bet between two hands
            g->swapSplit();

            //split, another hand
            Player playerDeck2(playerDeck, false);
            p = &playerDeck2;
            playOneHand(d, p, c, g);
        }
        else{
            playOneHand(d, p, c, g);
        }
    }
    else{
        playOneHand(d, p, c, g);
    }
}



//basic function runs the one hand game
void playOneHand(CardDeck* d, CardDeck* p, MakeChoice &c, GameStat *g){
    //test Blackjack
    if(p->getBJ()){
        cout << "\n      ***    You got Blackjack!    ***\n";
    }
    else if(d->getBJ()){    }

    //ask for player choice
    else{
        if(g->getBet()*2 <= g->getChips()){
            c.showFirstChoice();
        }
        else{
            c.showChoice();
        }

        while(!c.getStand()){
            p->drawCard();
            if(p->sum() >= 21)
                break;
            cout << "\n" << setw(8) << g->getID() << " hand: ";
            p->show();
            c.showChoice();
        };

        if(c.getDouble()){
            g->doubleBet();
            p->drawCard();
        }

        cout << "\n" << setw(8) << g->getID() << " hand: ";
        p->show();
        cout << endl;
    }

    //save this hand to game stat, for later winner determination
    g->savePlayerHand(p);
}



//decide the winner
void winner(CardDeck* d, GameStat* g){
    //Blackjack situation
    if(g->getBJ() && !d->getBJ()){
        cout << "      ***    Player win Blackjack!    ***\n";
        g->winBJ();
    }
    else if(d->getBJ() && !g->getBJ()){
        cout << "      ***    Dealer win Blackjack!    ***\n";
        g->loseBJ();
    }

    else{
        //busted situation
        if(g->sum() > 21 || d->sum() >21){
            if(d->sum() <= 21){
                cout << "          ***    Player busted!    ***\n";
                g->lose();
            }
            else if(g->sum() <= 21){
                cout << "          ***    Dealer busted!    ***\n";
                g->win();
            }
            else{
                cout << "           ***    Both busted!    ***\n";
                g->push();
            }
        }

        else{
            //other
            if(g->sum() > d->sum()){
                cout << "      ***    Player got higher pts!    ***\n";
                g->win();
            }
            else if(g->sum() < d->sum()){
                cout << "      ***    Dealer got higher pts!    ***\n";
                g->lose();
            }
            else{
                cout << "             ***    Push    ***\n";
                g->push();
            }
        }
    }
}
