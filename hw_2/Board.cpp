//
// Created by Admin on 12/8/2021.
//

#include "Board.h"
#include <iostream>

Board::Board()
{
    this->init();
}

Board::~Board()
{
    for(int i = 0;i<11;i++)
    {
        for(int j = 0;j<11;j++)
        {
            delete(gameBoard[i][j]);
        }
    }
    delete(this);
}

void Board::setNeighbors()
{
    for(int i = 0;i< 11; i++)
    {
        for(int j = 0;j<11;j++)
        {
            //top left corner
            if(i == 0 && j == 0)
            {
                this->gameBoard[i][j]->neighbors[0] = 0;
                this->gameBoard[i][j]->neighbors[1] = 0;
                this->gameBoard[i][j]->neighbors[2] = this->gameBoard[i][j + 1];
                this->gameBoard[i][j]->neighbors[3] = this->gameBoard[i + 1][j];
                this->gameBoard[i][j]->neighbors[4] = 0;
                this->gameBoard[i][j]->neighbors[5] = 0;
            }

            //top right corner
            else if(i == 0 && j == 10)
            {
                this->gameBoard[i][j]->neighbors[0] = 0;
                this->gameBoard[i][j]->neighbors[1] = 0;
                this->gameBoard[i][j]->neighbors[2] = 0;
                this->gameBoard[i][j]->neighbors[3] = this->gameBoard[i + 1][j];
                this->gameBoard[i][j]->neighbors[4] = this->gameBoard[i + 1][j - 1];
                this->gameBoard[i][j]->neighbors[5] = this->gameBoard[i][j - 1];
            }

            //bottom right corner
            else if(i == 10 && j == 10)
            {
                this->gameBoard[i][j]->neighbors[0] = this->gameBoard[i - 1][j];
                this->gameBoard[i][j]->neighbors[1] = 0;
                this->gameBoard[i][j]->neighbors[2] = 0;
                this->gameBoard[i][j]->neighbors[3] = 0;
                this->gameBoard[i][j]->neighbors[4] = 0;
                this->gameBoard[i][j]->neighbors[5] = this->gameBoard[i][j - 1];
            }

            //bottom left corner
            else if(i == 10 && j == 0)
            {
                this->gameBoard[i][j]->neighbors[0] = this->gameBoard[i - 1][j];
                this->gameBoard[i][j]->neighbors[1] = this->gameBoard[i - 1][j + 1];
                this->gameBoard[i][j]->neighbors[2] = this->gameBoard[i][j + 1];
                this->gameBoard[i][j]->neighbors[3] = 0;
                this->gameBoard[i][j]->neighbors[4] = 0;
                this->gameBoard[i][j]->neighbors[5] = 0;
            }

            //top edge
            else if(i == 0 && j > 0 && j < 10)
            {
                this->gameBoard[i][j]->neighbors[0] = 0;
                this->gameBoard[i][j]->neighbors[1] = 0;
                this->gameBoard[i][j]->neighbors[2] = this->gameBoard[i][j + 1];
                this->gameBoard[i][j]->neighbors[3] = this->gameBoard[i + 1][j];
                this->gameBoard[i][j]->neighbors[4] = this->gameBoard[i + 1][j - 1];
                this->gameBoard[i][j]->neighbors[5] = this->gameBoard[i][j - 1];
            }

            //right edge
            else if(i > 0 && i < 10 && j == 10 )
            {
                this->gameBoard[i][j]->neighbors[0] = this->gameBoard[i - 1][j];
                this->gameBoard[i][j]->neighbors[1] = 0;
                this->gameBoard[i][j]->neighbors[2] = 0;
                this->gameBoard[i][j]->neighbors[3] = this->gameBoard[i + 1][j];
                this->gameBoard[i][j]->neighbors[4] = this->gameBoard[i + 1][j - 1];
                this->gameBoard[i][j]->neighbors[5] = this->gameBoard[i][j - 1];
            }

            //bottom edge
            else if(i == 10 && j > 0 && j < 10)
            {
                this->gameBoard[i][j]->neighbors[0] = this->gameBoard[i - 1][j];
                this->gameBoard[i][j]->neighbors[1] = this->gameBoard[i - 1][j + 1];
                this->gameBoard[i][j]->neighbors[2] = this->gameBoard[i][j + 1];
                this->gameBoard[i][j]->neighbors[3] = 0;
                this->gameBoard[i][j]->neighbors[4] = 0;
                this->gameBoard[i][j]->neighbors[5] = this->gameBoard[i][j - 1];
            }

            //left edge
            else if(i > 0 && i < 10 && j == 0)
            {
                this->gameBoard[i][j]->neighbors[0] = this->gameBoard[i - 1][j];
                this->gameBoard[i][j]->neighbors[1] = this->gameBoard[i - 1][j + 1];
                this->gameBoard[i][j]->neighbors[2] = this->gameBoard[i][j + 1];
                this->gameBoard[i][j]->neighbors[3] = this->gameBoard[i + 1][j];
                this->gameBoard[i][j]->neighbors[4] = 0;
                this->gameBoard[i][j]->neighbors[5] = 0;
            }

            //everywhere else
            else if(i > 0 && i < 10 && j > 0 && j < 10)
            {
                this->gameBoard[i][j]->neighbors[0] = this->gameBoard[i - 1][j];
                this->gameBoard[i][j]->neighbors[1] = this->gameBoard[i - 1][j + 1];
                this->gameBoard[i][j]->neighbors[2] = this->gameBoard[i][j + 1];
                this->gameBoard[i][j]->neighbors[3] = this->gameBoard[i + 1][j];
                this->gameBoard[i][j]->neighbors[4] = this->gameBoard[i + 1][j - 1];
                this->gameBoard[i][j]->neighbors[5] = this->gameBoard[i][j - 1];
            }
        }
    }
}

void Board::init()
{
    for(int i = 0;i<11;i++)
    {
        for(int j = 0; j< 11 ;j++)
        {
            this->gameBoard[i][j] = new Cell(i,j);
        }
    }
    for(int i=0;i<11;i++)
    {
        gameBoard[10][i]->setRedWin();
        gameBoard[i][10]->setBlueWin();
        this->setNeighbors();
    }
}

bool Board::setCell(int x, int y, char color)
{
    if(this->gameBoard[x][y]->getColor() == 'g' && color != 'g' && (color == 'r' || color == 'b') && x >= 0 && x <= 10 && y >= 0 && y <= 10)
    {
        this->gameBoard[x][y]->setColor(color);
        return true;
    }
    return false;
}

bool Board::scanBoard(Cell *cell, char color)
{
    bool flag = false;
    if(cell->getColor() != 'g') cell->visited = true;
    if(color == 'b' && cell->blueWin == true) return true;
    if(color == 'r' && cell->redWin == true) return true;
    for(int i = 0; i< 6;i++)
    {
        if(cell->neighbors[i])
        {
            if(cell->neighbors[i]->visited == false && cell->neighbors[i]->getColor() == color)
            {
                flag = scanBoard(cell->neighbors[i], color);
                if(flag) break;
            }
        }
    }
    return flag;
}

bool Board::checkWinner(char color)
{
    if(color == 'b')
    {
        for(int i = 0; i < 11;i++)
        {
            if(scanBoard(this->gameBoard[i][0], color)) return true;
        }
    }

    if(color == 'r')
    {
        for(int j = 0; j < 11;j++)
        {
            if(scanBoard(this->gameBoard[0][j], color)) return true;
        }
    }

    this->resetVisits();
    return false;
}

void Board::resetVisits()
{
    for(int i = 0; i <11;i++)
    {
        for(int j = 0;j<11;j++)
        {
            this->gameBoard[i][j]->visited = false;
        }
    }
}

void Board::printBoard()
{
    for(int i=0;i<11;i++)
    {
        for(int z=0;z<i;z++) std::cout<<' ';
        for (int j=0;j<11;j++)
        {
            if (this->gameBoard[i][j]->getColor() == 'r') std::cout << 'R';
            else if (this->gameBoard[i][j]->getColor() == 'b') std::cout << 'B';
            else std::cout << 'O';
            if (j < 10) std::cout<< " ";
        }
        std::cout<<std::endl;
    }
}
