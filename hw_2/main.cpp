#include <iostream>
#include "Cell.h"
#include "Board.h"
#include "GameInterface.h"
using namespace std;


/*Runs program*/
int main()
{
    GameInterface* gi = new GameInterface();
    gi->runInterface();
    return 0;
}
