/*
BlackJack v1.03

*/


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <limits>
#include <string>



using namespace std;

//deal a random card
int cardGen();

//sum up the total points,
int sumHand(vector<int> &);

//display cards at hand
void showHand(vector<int> &, bool);

//basic function runs the game
void run(int &, int &, int &, int &, double &);

//initial the game, deal two cards to dealer and one card to player
//return number of Aces in dealer's hand
int initialGame(vector<int> &, vector<int> &);

//dealer draw cards
void dealerHand(vector<int> &, int);

//play draw cards
void playerHand(vector<int> &, vector<int> &, double &bet, int &dealNumAce);

//user input validation
bool choiceValid(char ch);

//get player's choice for first time
char askPlayer();

//get player's choice for later time
char askPlayer2();

//get player's choice whether split or not
bool askPlayerSplit();

//run the game in case of player choose to split, return split bet
double runSplit(vector<int> &, vector<int> &, int &, int &, int &, double &bet, int &dealNumAce);

//Blackjack winning, return true if blackjack
bool winBlackjack(vector<int> &, vector<int> &, int &, int &, int &, double &);

//winning results
void winOrLose(vector<int> &, vector<int> &, int &, int &, int &, double &);

//print the current winning count status
void printResults(int &, int &, int &, int &);

//print total chips that player has
void printChips(double &);

//user input validation
double inputValid(double);




int main()
{
    cout << "Welcome to BlackJack v1.03\n"

    unsigned seed = time(0);
    srand(seed);

    //vector<int> dealer;
    //vector<int> player;
    int gameCount = 0,
        winCount = 0,
        loseCount = 0,
        pushCount = 0;

    double chips = 10000.0;

    do
    {
        run(gameCount, winCount, loseCount, pushCount, chips);
        gameCount++;
        printResults(gameCount, winCount, loseCount, pushCount);

    }while(chips > 0);

    cout << "Game Over...";

    system ("PAUSE");


    return 0;
}

int cardGen()
{
    int card = rand()%13 + 1;
    if(card > 10)
        card = 10;

    return card;
}


int sumHand(vector<int> &vect)
{
    int sum = 0;
    int numAce = 0;
    for(int i : vect)
    {
        if(i == 1)
        {
            if(sum <= 10)
                {
                    i = 11;
                    numAce++;
                }
        }
        sum += i;

        while(sum>21 && numAce>0)
        {
            sum -= 10;
            numAce--;
        }
    }
    //cout << "The sum of hand is: " << sum << endl;
    return sum;
}

void showHand(vector<int> &vect, bool hideFirst)
{

    if(hideFirst)
    {
        cout << " [X] ";
    }
    else
    {
        if(vect.at(0) == 1)
            cout << " [A] ";
        else
            cout << " [" << vect.at(0) << "] ";
    }

    for(unsigned i = 1; i < vect.size(); i++)
    {
        if(vect.at(i) == 1)
            cout << " [A] ";
        else
            cout <<  " [" << vect.at(i) << "] ";
    }
    cout << endl;
}

void run(int &gameCount, int &winCount, int &loseCount, int &pushCount, double &chips)
{

    cout << "\n --- New Game (" << gameCount+1 << ") --- \n";

    printChips(chips);

    cin.clear();

    double bet = inputValid(chips), betSplit = 0.0;
    cout << "Your bet is: " << showpoint << setprecision(5) << bet << "\n\n";

    vector<int> dealer, player;

    int dealNumAce = initialGame(dealer, player);

    if((sumHand(dealer) == 21 && dealer.size() == 2) || (sumHand(player) == 21 && player.size() == 2))
    {
            winBlackjack(dealer, player, winCount, loseCount, pushCount, bet);
    }

    else
    {
        bool splitFlag = false;

        if(player.at(0) == player.at(1))
        {
            showProbabilitySplit(dealer, player, dealNumAce);

            if(askPlayerSplit())
            {
                splitFlag = true;
                betSplit = runSplit(dealer, player, winCount, loseCount, pushCount, bet, dealNumAce);
            }
        }
        if(!splitFlag)
        {

            playerHand(dealer, player, bet, dealNumAce);
            dealerHand(dealer, dealNumAce);

            winOrLose(dealer, player, winCount, loseCount, pushCount, bet);
        }

    }

    chips += (bet + betSplit);




}

int initialGame(vector<int> &dealer, vector<int> &player)
{
    int numAce = 0;
    int card1 = cardGen();
    if(card1 == 1)
        numAce++;
    dealer.push_back(card1);
    int card2 = cardGen();
    if(card2 == 1)
        numAce++;
    dealer.push_back(card2);
    cout << "Dealer's hand: ";
    showHand(dealer, true);

    player.push_back(cardGen());
    player.push_back(cardGen());
    cout << "Player's hand: ";
    showHand(player, false);

    return numAce;
}


void dealerHand(vector<int> &vect, int numAce)
{
    if(numAce == 0)
    {
        int sum = sumHand(vect);
        while(sum < 17)
        {
            int card = cardGen();
            vect.push_back(card);
            //showHand(vect,0);
            sum = sumHand(vect);
        }
    }
    else
    {
        int sum = vect.at(0) + vect.at(1) + 10;
        while(sum < 17)
        {
            int card = cardGen();
            vect.push_back(card);
            //showHand(vect,0);
            sum = sumHand(vect);
        }
    }

    cout << "\nDealer's hand: ";
    showHand(vect, false);
    cout << "                                   Dealer points = " << sumHand(vect) << endl;
}


void playerHand(vector<int> &dealer, vector<int> &player, double &bet, int &dealNumAce)
{
    showProbability(dealer, player, dealNumAce);

    char choice = askPlayer();

    while(choice == 'H')
    {
        player.push_back(cardGen());
        cout << "\nPlayer's hand: ";
        showHand(player, false);
        if(sumHand(player) > 21)
            break;
        showProbability(dealer, player, dealNumAce);
        choice = askPlayer2();
    }

    if (choice == 'D')
    {
        //if(bet*2 < chips)
        bet *= 2;
        player.push_back(cardGen());
        cout << "\n                Double down!\nPlayer's hand: ";
        showHand(player, false);
    }
    cout << "                                   Player points = " << sumHand(player) << endl;
}



char askPlayer()
{
    char choice = ' ';

    do
    {
        cout << "--> Hit, Stand or Double ? (H/S/D)" ;
        cin >> choice;
        cin.clear();

    }while(!choiceValid(choice));

    if(choice == 'H' || choice == '1')
        return 'H';
    if(choice == 'S' || choice == '0')
        return 'S';
    if(choice == 'D' || choice == '2')
        return 'D';
}

char askPlayer2()
{
    char choice;
    do
    {
        cout << "--> Hit or Stand? (H/S)" ;
        cin >> choice;
        cin.clear();
    }while(!choiceValid(choice));

    if(choice == 'H' || choice == '1')
        return 'H';
    if(choice == 'S' || choice == '0')
        return 'S';

}


bool askPlayerSplit()
{
    char choice;
    do
    {
        cout << "--> Do you want to split? (P or 0)" ;
        cin >> choice;
        cin.clear();
    }while(!choiceValid(choice));

    if(choice == 'P' || choice == '3')
        return true;
    else
        return false;
}


bool choiceValid(char ch)
{
    if(ch == 'H' || ch == 'S' || ch == '0' || ch == '1' || ch == 'D' || ch == '2' || ch == 'P' || ch == '3' || ch == '9')
        return true;
    else
    {
        cin.clear();
        return false;
    }
}

double inputValid(double amount)
{
  double userInput = 0.00; // To hold the number of userInput
  bool loopFlag = true; // Control flag for the loop

  do
  {
    cout << "Enter your bet: ";
    cin >> userInput;
    // Short circuit testing
    if ((cin.fail()) || userInput <= 0 || userInput > amount)
    {
      cout << "The bet must be a valid number between 0 and " << amount << " .\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
      loopFlag = false;
    }
  } while (loopFlag);
  return userInput;
}

double runSplit(vector<int> &dealer, vector<int> &player, int &winCount, int &loseCount, int &pushCount, double &bet, int &dealNumAce)
{
                player.pop_back();
                vector<int> playerSplit(player);
                playerSplit.push_back(cardGen());
                player.push_back(cardGen());

                bool blackJack = 0, blackJackSplit = 0;
                double betSplit = bet;

                cout << "\nPlayer's first hand: ";
                showHand(playerSplit, false);
                if(sumHand(playerSplit) == 21)
                    {
                        blackJackSplit = winBlackjack(dealer, playerSplit, winCount, loseCount, pushCount, betSplit);
                    }
                else
                    {
                        playerHand(dealer, playerSplit, betSplit, dealNumAce);
                    }

                cout << "\nPlayer's second hand: ";
                showHand(player, false);
                if(sumHand(player) == 21)
                    {
                        blackJack = winBlackjack(dealer, player, winCount, loseCount, pushCount, bet);
                    }
                else
                    {
                        playerHand(dealer, player, bet, dealNumAce);
                    }

                dealerHand(dealer, dealNumAce);

                if(!blackJackSplit)
                {
                    cout << "\nFor your first hand: \n";
                    winOrLose(dealer, playerSplit, winCount, loseCount, pushCount, betSplit);
                }

                if(!blackJack)
                {
                    cout << "For your second hand: \n";
                    winOrLose(dealer, player, winCount, loseCount, pushCount, bet);
                }

                return betSplit;
}


bool winBlackjack(vector<int> &dealer, vector<int> &player, int &win, int &lose, int &push, double &bet)
{
    if((sumHand(dealer) == 21 && dealer.size() == 2) || (sumHand(player) == 21 && player.size() == 2))
    {
        if(sumHand(player) != 21)
        {
            lose++;
            bet = -bet;
            cout << "\nDealer's hand: ";
            showHand(dealer, false);
            cout << " *** Dealer got BlackJack! *** \n"
                 << "      Dealer win!\n\n";

        }
        else if(sumHand(dealer) != 21)
        {
            win++;
            cout << "\n *** You got BlackJack!!! ***\n"
                 <<  "       You win!\n\n";
        }
        else
        {
            push++;
            bet = 0;
            cout << "\nDealer's hand: ";
            showHand(dealer, false);
            cout << "\n *** You and dealer both got BlackJack!!! ***\n"
                 <<  "           Push!\n\n";
        }

        system ("PAUSE");

    }
    return true;
}


void winOrLose(vector<int> &dealer, vector<int> &player, int &win, int &lose, int &push, double &bet)
{


    if(sumHand(player) > 21 && sumHand(dealer) <= 21)
    {
        lose++;
        bet = -bet;
        cout << "\n *** You busted! ***\n"
             << "     Dealer win!\n\n";
    }
    else if(sumHand(dealer) > 21 && sumHand(player) <= 21)
    {
        win++;
        cout << "\n *** Dealer busted! ***\n"
             << "     You win!\n\n";
    }

    else if(sumHand(dealer) > 21 && sumHand(player) > 21)
    {
        push++;
        bet = 0;
        cout << "\n *** You and Dealer both busted! ***\n"
             << "           Push!\n\n";
    }
    else
    {
        if(sumHand(player) > sumHand(dealer))
        {
            win++;
            cout << "\n *** You got higher point. ***\n"
                 << "        You win!\n\n";
        }
        else if(sumHand(player) < sumHand(dealer))
        {
            lose++;
            bet = -bet;
            cout << "\n *** Dealer got higher point. ***\n"
                 << "        Dealer win!\n\n";
        }
        else
        {
            push++;
            bet = 0;
            cout << "\n *** You and dealer got same point. ***\n"
                 << "            Push!\n\n";
        }
    }

}

void printResults(int &game, int &win, int &lose, int &push)
{
    cout << " [  Game]  [   Win]  [  Lose]  [  Push]\n"
         << " [" << setw(6) << game << "] "
         << " [" << setw(6) << win << "] "
         << " [" << setw(6) << lose << "] "
         << " [" << setw(6) << push << "] \n\n";

}

void printChips(double &chips)
{
    cout << "Player credits: " << setw(8) << showpoint << setprecision(6) << chips << endl;
}



/*
 *   The following code is For Cheating Mode
 */
 

void showProbability(vector<int> dealerProb, vector<int> playerProb, int dealNumAce)
{
    int win = 0, lose = 0, push = 0;
    int total = 10000;

    //In the case of HIT
    for(int i = 0; i < total; i++)
    {
        vector<int> playerProbi(playerProb);
        playerProbi.push_back(cardGen());

        vector<int> dealerProbi(dealerProb);
        dealerHandProbab(dealerProbi, dealNumAce);

        ///THere could be hit after hit
        if(sumHand(playerProbi) <= 11 || (dealerProbi.at(1) > 7) && sumHand(playerProbi) < 17)
        {
            playerProbi.push_back(cardGen());
        }

        winOrLoseProbab(dealerProbi, playerProbi, win, lose, push);

    }
    cout << "   //If HIT:\n"
         << "       Win rate  = " << win << endl
         << "       Lose rate = " << lose << endl
         << "       Win:Lose  = " << static_cast<double>(win)/lose << endl;

    win = 0, lose = 0, push = 0;

    //In the case of STAND
    for(int i = 0; i < total; i++)
    {
        vector<int> playerProbi(playerProb);
        vector<int> dealerProbi(dealerProb);
        dealerHandProbab(dealerProbi, dealNumAce);

        winOrLoseProbab(dealerProbi, playerProbi, win, lose, push);
    }
    cout << "   //If STAND:\n"
         << "       Win rate  = " << win << endl
         << "       Lose rate = " << lose << endl
         << "       Win:Lose  = " << static_cast<double>(win)/lose << endl;

}

void showProbabilitySplit(vector<int> dealerProb, vector<int> playerProb, int dealNumAce)
{
    int win = 0, lose = 0, push = 0;
    int total = 1000;

    cout << "//If NOT split:\n";
    showProbability(dealerProb, playerProb, dealNumAce);

    win = 0, lose = 0, push = 0;

    cout << "//If split:\n";
    playerProb.pop_back();
    showHand(playerProb,0);

    for(int i = 0; i < total; i++)
    {
        vector<int> playerProbi(playerProb);
        playerProbi.push_back(cardGen());
        //showHand(playerProbi,0);

        for(int j = 0; j < 100; j++)
        {
            vector<int> playerProbii(playerProbi);
            playerProbii.push_back(cardGen());

            vector<int> dealerProbi(dealerProb);
            dealerHandProbab(dealerProbi, dealNumAce);

            winOrLoseProbab(dealerProbi, playerProbii, win, lose, push);
        }
    }
    cout << "   //If HIT:\n"
         << "       Win rate  = " << win << endl
         << "       Lose rate = " << lose << endl
         << "       Win:Lose  = " << static_cast<double>(win)/lose << endl;

    win = 0, lose = 0, push = 0;

    for(int i = 0; i < total; i++)
    {
        vector<int> playerProbi(playerProb);
        playerProbi.push_back(cardGen());

        for(int j = 0; j < 100; j++)
        {
            //vector<int> playerProbi(playerProb);
            vector<int> dealerProbi(dealerProb);
            dealerHandProbab(dealerProbi, dealNumAce);

            winOrLoseProbab(dealerProbi, playerProbi, win, lose, push);
        }
    }
    cout << "   //If STAND:\n"
         << "       Win rate  = " << win << endl
         << "       Lose rate = " << lose << endl
         << "       Win:Lose  = " << static_cast<double>(win)/lose << endl;

}


void dealerHandProbab(vector<int> &vect, int numAce)
{
    if(numAce == 0)
    {
        int sum = sumHand(vect);
        while(sum < 17)
        {
            int card = cardGen();
            vect.push_back(card);
            //showHand(vect,0);
            sum = sumHand(vect);
        }
    }
    else
    {
        int sum = vect.at(0) + vect.at(1) + 10;
        while(sum < 17)
        {
            int card = cardGen();
            vect.push_back(card);
            //showHand(vect,0);
            sum = sumHand(vect);
        }
    }
}


void winOrLoseProbab(vector<int> dealer, vector<int> player, int &win, int &lose, int &push)
{
    if(sumHand(player) > 21 && sumHand(dealer) <= 21)
    {
        lose++;
    }
    else if(sumHand(dealer) > 21 && sumHand(player) <= 21)
    {
        win++;
    }

    else if(sumHand(dealer) > 21 && sumHand(player) > 21)
    {
        push++;
    }
    else
    {
        if(sumHand(player) > sumHand(dealer))
        {
            win++;
        }
        else if(sumHand(player) < sumHand(dealer))
        {
            lose++;
        }
        else
        {
            push++;
        }
    }
}

