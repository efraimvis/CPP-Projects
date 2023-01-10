//
// Created by Admin on 12/8/2021.
//

#include "Cell.h"

Cell::Cell(int x, int y):x(x),y(y)
{
    this->color = 'g';
    this->redWin = false;
    this->blueWin = false;
    this->visited = false;
}

Cell::Cell(const Cell &c):x(c.x),y(c.y)
{
    this->color = c.color;
    this->visited = c.visited;
}

Cell::~Cell()
{
    delete(this);
}

const char Cell::getColor()
{
    return this->color;
}

bool Cell::setColor(char color)
{
    if(this->color == 'g' && (color == 'r' || color == 'b'))
    {
        this->color = color;
        return true;
    }
    else return false;
}

void Cell::setBlueWin()
{
    this->blueWin = true;
}

void Cell::setRedWin()
{
    this->redWin = true;
}

