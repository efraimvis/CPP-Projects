//
// Created by Admin on 12/8/2021.
//

#ifndef HW_3_CELL_H
#define HW_3_CELL_H


class Cell
{
private:
    bool visited;
    const int x;
    const int y;
    bool redWin;
    bool blueWin;
    char color;
    Cell* neighbors[6];
    friend class Board;

public:
    //Cell(int x, int y) : x(x),y(y) {};

    /*Constructor
     *
     * x - x coordinate of cell
     * y - y coordinate of cell*/
    Cell(int x, int y);

    /*Copy Constructor
     *
     * c - cell to copy from*/
    Cell(const Cell &c);

    /*Destructor*/
    ~Cell();
    //Cell& operator=(const Cell &c); not necessary, since each cell is unique, and should not be copied

    /**
    const int getX();
    const int getY();
    **/

    /*Returns color of this cell*/
    const char getColor();

    /*Setter for color
     *
     * color - color to set in this cell
     *
     * return : Returns true if successful, false otherwise (cell already non grey)*/
    bool setColor(char color);

    /*Sets this cell to have the property of being a winning cell (terminal) for blue player*/
    void setBlueWin();

    /*Sets this cell to have the property of being a winning cell (terminal) for red player*/
    void setRedWin();
};


#endif //HW_3_CELL_H
