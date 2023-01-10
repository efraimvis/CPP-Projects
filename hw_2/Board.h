//
// Created by Admin on 12/8/2021.
//

#ifndef HW_3_BOARD_H
#define HW_3_BOARD_H

#include "Cell.h"

class Board
{
private:
    Cell* gameBoard[11][11];

    /*Scans board to determine if player of given color has won
     *
     * cell - cell to start from
     * color - color of player for which operation is performed
     *
     * return : Returns true if a player has won, false otherwise*/
    bool scanBoard(Cell* cell, char color);

    /*Resets visit values for all cells on board to false*/
    void resetVisits();

    /*Sets neighbor arrays for all cells*/
    void setNeighbors();

public:
    /*Constructor*/
    Board();

    /*Destructor*/
    ~Board();

    /*Initializes board values*/
    void init();

    /*Sets a cell to given values
     *
     * x - cell's x value
     * y - cell's y value
     * color - cell's color
     *
     * return : Returns true if cell set successfully (legal parameters), false otherwise*/
    bool setCell(int x, int y, char color);

    /*Checks if player of given color has won, wraps recursive function scanBoard
     *
     * color - given player's color
     *
     * return : Returns true if given player has won, false otherwise*/
    bool checkWinner(char color);

    /*Prints game board state to console*/
    void printBoard();
};


#endif //HW_3_BOARD_H
