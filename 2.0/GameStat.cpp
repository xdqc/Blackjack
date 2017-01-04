#include "GameStat.h"

GameStat::GameStat(int i)
{
    cout << "Please enter Player " << i+1 << "'s name: ";
    getline(cin, playerID);
    playerID = playerID.substr(0,8);
    cin.clear();
    gameCount = 0;
    winCount = 0;
    loseCount = 0;
    pushCount = 0;
    chips = 10000;
    bet = 0;
    splitBet = 0;
    split = false;
}


void GameStat::win(){
    gameCount++;
    winCount++;
    chips += bet;
    cout << "         ^_^    " << playerID << " won " << bet << " !    ^_^\n";
}

void GameStat::winBJ(){
    gameCount++;
    winCount++;
    bet += bet/2;
    chips += bet;
    cout << "         ^_^    " << playerID << " won " << bet << " !    ^_^\n";
}

void GameStat::lose(){
    gameCount++;
    loseCount++;
    chips -= bet;
    cout << "         =_=    " << playerID << " lost " << bet << " !    =_=\n";
}

void GameStat::loseBJ(){
    gameCount++;
    loseCount++;
    bet += bet/2;
    chips -= bet;
    cout << "         =_=    " << playerID << " lost " << bet << " !    =_=\n";
}

void GameStat::push(){
    gameCount++;
    pushCount++;
}

void GameStat::setBet(){
    cout << "Enter your bet : 500 x ";
    cin >> bet;
    cin.clear();
    cin.ignore(1000,'\n');

    if(bet <= 0){
        bet = 1;
    }
    bet *= 500;
    if(bet>chips){
        bet = chips;
    }
    splitBet = bet;
    split = false;

    cout << setw(8) << right << playerID << "'s bet : " << bet << endl << endl;
}

void GameStat::swapSplit(){
    int temp = bet;
    bet = splitBet;
    splitBet = temp;
    split = !split;
}

void GameStat::printChips(){
    cout << "\t  ----------------\n";
    cout << "\t | " << setw(8) << left << playerID <<" CHIPS |  =  " << chips << endl;
    cout << "\t  ----------------\n";
}

void GameStat::printStats()
{
    cout << "\n" << setw(8) << playerID << " [  Chips ]  [  Win ]  [ Lose ]  [ Push ]\n\t"
         << " [" << setw(7) << chips << " ] "
       //<< " [" << setw(6) << gameCount << "] "
         << " [" << setw(4) << winCount << "  ] "
         << " [" << setw(4) << loseCount << "  ] "
         << " [" << setw(4) << pushCount << "  ] \n";
}




//save current player deck
void GameStat::savePlayerHand(CardDeck* p){
    if(!split){
        thisRun = p;
    }
    else{
        thisRunSplit = p;
    }

}

//
void GameStat::showPts(){
    if(!split){
        cout << "\n" << setw(8) << getID() << "   ";
        thisRun.show();
        cout << setw(8) << "(" << thisRun.sum() << "pts)" << endl;
    }
    else{
        cout << "\n" << setw(8) << getID() << " 1 ";
        thisRun.show();
        cout << setw(8) << "(" << thisRun.sum() << "pts)" << endl;
        cout << setw(8) << getID() << " 2 ";
        thisRunSplit.show();
        cout << setw(8) << "(" << thisRunSplit.sum() << "pts)" << endl;
    }
}

int GameStat::sum(){
    if(!split)
        return thisRun.sum();
    else
        return thisRunSplit.sum();
}

int GameStat::size(){
    if(!split)
        return thisRun.size();
    else
        return thisRunSplit.size();
}

bool GameStat::getBJ(){
    if(!split)
        return (thisRun.size() == 2 && thisRun.sum() == 21);
    else
        return (thisRunSplit.size() == 2 && thisRunSplit.sum() == 21);
}
