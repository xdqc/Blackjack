#ifndef MAKECHOICE_H
#define MAKECHOICE_H
#include "GameStat.h"


class MakeChoice
{
    public:
        MakeChoice();
        void showFirstChoice();
        void showChoice();
        void showSplitChoice();

        //getters
        bool getHit(){return hit;}
        bool getStand(){return stand;}
        bool getDouble(){return doubleDown;}
        bool getSplit(){return split;}

        //mutators
        void clrDouble(){doubleDown = false;}
        void setSplit(){split = true;}
        void clrSplit(){split = false;}

    private:
        char choice;
        bool hit;
        bool stand;
        bool doubleDown;
        bool split;
};

#endif // MAKECHOICE_H
