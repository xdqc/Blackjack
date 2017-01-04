#include "MakeChoice.h"

MakeChoice::MakeChoice()
{
    //constructor
    choice = ' ';
    hit = false;
    stand = false;
    doubleDown = false;
    split = false;
}

void MakeChoice::showFirstChoice(){
    hit = false;
    stand = false;

    //show options
    cout << "\n\n--> 1.Hit  2.Stand  3.Double ? (H/S/D) " ;
    choice = cin.get();
    cin.clear();
    cin.ignore(1000,'\n');

    if(choice == 'H' || choice == 'h' || choice == '1'){
        hit = true;
        cout << "\n               >>> Hit <<<\n";
    }
    else if(choice == 'S' || choice == 's' || choice == '2' || choice == '0'){
        stand = true;
        cout << "\n              >>> Stand <<< \n";
    }
    else if(choice == 'D' || choice == 'd' || choice == '3'){
        hit = true;
        doubleDown = true;
        stand = true;
        cout << "\n           >>> Double Down! <<< \n";
    }
    else{
        MakeChoice::showFirstChoice();
    }
}

void MakeChoice::showChoice(){

    hit = false;
    stand = false;

    //show options
    cout << "\n\n--> 1.Hit  2.Stand ? (H/S) " ;
    choice = cin.get();
    cin.clear();
    cin.ignore(1000,'\n');

    if(choice == 'H' || choice == 'h' || choice == '1'){
        hit = true;
        cout << "\n               >>> Hit <<<\n";
    }
    else if(choice == 'S' || choice == 's' || choice == '2' || choice == '0'){
        stand = true;
        cout << "\n              >>> Stand <<<\n";
    }
    else{
        MakeChoice::showChoice();
    }
}

void MakeChoice::showSplitChoice(){
    //show split options

    cout << "\n\n--> 1.Split  2.No-Split ? (P/N)" ;
    choice = cin.get();
    cin.clear();
    cin.ignore(1000,'\n');

    if(choice == 'P' || choice == 'p' || choice == '1' || choice == 'Y' || choice == 'y' || choice == '3'){
        split = true;
        cout << "\n              >>> Split <<<\n";
    }
    else if(choice == 'N' || choice == 'n' || choice == '2' || choice == '0'){
        split = 0;
        cout << "\n             >>> No-Split <<<";
    }
    else{
        MakeChoice::showSplitChoice();
    }
}
