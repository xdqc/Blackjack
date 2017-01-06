
#include "GameStat.h"

const int INITIAL_CHIPS = 10000;
const int BET_UNIT = 100;

GameStat::GameStat(int i)
{
    cout << "Please enter Player " << i+1 << " 's name (0~8 characters) ";
    getline(cin, playerID);
    playerID = playerID.substr(0,8);
    cin.clear();
    gameCount = 0;
    winCount = 0;
    loseCount = 0;
    pushCount = 0;
    chips = INITIAL_CHIPS;
    bet = 0;
    splitBet = 0;
    split = false;
}


void GameStat::setBet(){
	cout << "Enter your bet : $" << BET_UNIT << " x ";
    cin >> bet;
    cin.clear();
    cin.ignore(1000,'\n');

    if(bet <= 0){
        bet = 1;
    }
    bet *= BET_UNIT;
    if(bet>chips){
        bet = chips;
    }
    splitBet = bet;
    split = false;

    cout << setw(8) << right << playerID << "'s bet : $" << bet << endl << endl;
}

void GameStat::swapSplit(){
    int temp = bet;
    bet = splitBet;
    splitBet = temp;
    split = !split;
}

void GameStat::printChips(){
    cout << "\t  -------------------------------\n";
    cout << "\t | " << setw(8) << left << playerID <<" BALANCE  =  $" << setw(8) << chips << '|' << endl;
    cout << "\t  -------------------------------\n";
}

void GameStat::printStats()
{
    cout << "\n" << setw(8) << playerID << " [ Balance ]  [  Win ]  [ Lose ]  [ Push ]\n\t"
         << " [" << setw(8) << chips << " ] "
         ///< " [" << setw(4) << ++gameCount << "  ] "
         << " [" << setw(4) << winCount << "  ] "
         << " [" << setw(4) << loseCount << "  ] "
         << " [" << setw(4) << pushCount << "  ] \n";
}


//display result of one round
void GameStat::showPts(){
    if(!split){
        cout << "\n" << setw(8) << getID() << "   ";
        thisRun->showHand();
        cout << setw(8) << "(" << thisRun->sum() << "pts)" << endl;
    }
    else{
        cout << "\n" << setw(8) << getID() << " 1 ";
        thisRun->showHand();
        cout << setw(8) << "(" << thisRun->sum() << "pts)" << endl;
        cout << setw(8) << getID() << " 2 ";
        thisRunSplit->showHand();
        cout << setw(8) << "(" << thisRunSplit->sum() << "pts)" << endl;
    }

	cout << "    Vs.\n  Dealer   ";
	thisDealer->showHand();
	cout << setw(8) << "(" << dSum() << "pts)" << endl << endl;
}

//display winner of one round
void GameStat::winner()
{
	//Blackjack situation
	if (pBlackjack() && !dBlackjack()) {
		cout << "        ***    Player win Blackjack!    ***\n";
		winCount++;
		bet += bet / 2;
		chips += bet;
		cout << "          ^_^    " << playerID << " won $" << bet << "     ^_^\n";
	}
	else if (dBlackjack() && !pBlackjack()) {
		cout << "        ***    Dealer win Blackjack!    ***\n";
		loseCount++;
		//bet += bet / 2;
		chips -= bet;
		cout << "          v_v    " << playerID << " lost $" << bet << "     v_v\n";
	}

	//busted situation
	else if (pSum() > 21 || dSum() > 21) {
		if (dSum() <= 21) {
			cout << "           ***    Player busted!    ***\n";
			loseCount++;
			chips -= bet;
			cout << "          v_v    " << playerID << " lost $" << bet << "     v_v\n";
		}
		else if (pSum() <= 21) {
			cout << "           ***    Dealer busted!    ***\n";
			winCount++;
			chips += bet;
			cout << "          ^_^    " << playerID << " won &" << bet << "     ^_^\n";
		}
		else {
			cout << "            ***    Both busted!    ***\n";
			pushCount++;
		}
	}

	//other
	else {
		if (pSum() > dSum()) {
			cout << "       ***    Player got higher pts!    ***\n";
			winCount++;
			chips += bet;
			cout << "          ^_^    " << playerID << " won $" << bet << "     ^_^\n";
		}
		else if (pSum() < dSum()) {
			cout << "       ***    Dealer got higher pts!    ***\n";
			loseCount++;
			chips -= bet;
			cout << "          v_v    " << playerID << " lost $" << bet << "     v_v\n";
		}
		else {
			cout << "                ***    Push    ***\n";
			pushCount++;
		}
	}
	
}


