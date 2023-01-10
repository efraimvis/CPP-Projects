#include <iostream>
#include <stdlib.h>
#include "GameInterface.h"
using namespace std;

/*Runs assignment with given parameters*/
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cerr<<"ERROR: USAGE "<<argv[0]<<" NUM_REFEREES MAX_ATHLETES"<<endl;
        return 0;
    }
    else if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0)
    {
        cerr<<"ERROR: USAGE "<<argv[0]<<" NUM_REFEREES MAX_ATHLETES"<<endl;
        return 0;
    }

    GameInterface* g = new GameInterface(atoi(argv[1]),atoi(argv[2]));
    g->runInterface();
    return 0;
}
