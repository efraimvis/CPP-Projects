//
// Created by Admin on 12/8/2021.
//

#ifndef HW_3_GAMEINTERFACE_H
#define HW_3_GAMEINTERFACE_H
#include "Board.h"
#include <iostream>
using namespace std;

class GameInterface
{
private:
    Board* board;
    int turn;

public:
    /*Constructor*/
    GameInterface();

    /*Runs game interface*/
    void runInterface();

    /*Handles a single move by a player
     *
     * str - input string representing move
     * color - color of player performing move
     *
     * return : Returns true if move succeeded (legal move), false otherwise*/
    bool performMove(std::string str, char color);
};


#endif //HW_3_GAMEINTERFACE_H
