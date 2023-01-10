//
// Created by Admin on 12/8/2021.
//

#include "GameInterface.h"

GameInterface::GameInterface()
{
    this->board = new Board();
    this->turn = 0;
}

/*Checks if given string is a valid control string (valid, but necessarily legal move)
 *
 * string - given string
 *
 * return : Returns true if string is a valid control string, false otherwise*/
bool isValidControlString(std::string str)
{
    if(str.size() == 2 || str.size() == 3)
    {
        if(!(str[0] >= 'A' && str[0] <= 'K')) return false;

        if(str.size() == 2)
        {
            if(!(str[1] >= '1' && str[1] <= '9')) return false;
        }

        if(str.size() == 3)
        {
            if(!(str[1] == '1' && str[2] >= '0' && str[2] <= '1')) return false;
        }

        return true;
    }
    return false;
}

bool GameInterface::performMove(std::string str, char color)
{
    if(str.size() == 2 || str.size() == 3)
    {
        if((str[0] >= 'A' && str[0] <= 'K'))
        {
            if (str.size() == 2)
            {
                if ((str[1] >= '1' && str[1] <= '9'))
                {
                    //if(this->board->setCell((str[0]-65),(str[1]-49),color))return true ;
                    if(this->board->setCell((str[1]-49),(str[0]-65),color))return true ;
                }
            }

            else if (str.size() == 3)
            {
                if ((str[1] == '1' && str[2] >= '0' && str[2] <= '1'))
                {
                    //if(this->board->setCell((str[0]-65),(10+(str[2]-49)),color)) return true;
                    if(this->board->setCell((10+(str[2]-49)),(str[0]-65),color)) return true;
                }
            }
        }
    }
    cerr << "Invalid move; the game awaits a valid move." << endl;
    return false;
}

void GameInterface::runInterface()
{
    std::string control = "";
    while(true)
    {
        board->printBoard();
        if(turn % 2 == 0) cout<<"B:"<<endl;
        else cout<<"R:"<<endl;
        getline(cin,control);
        if(isValidControlString(control))
        {
            if (turn % 2 == 0)
            {
                if (performMove(control, 'b')) turn++;
            }
            else
            {
                if(performMove(control, 'r')) turn++;
            }
        }
        else if (control == "QUIT")
        {
            if(turn % 2 == 0)
            {
                cout<<"B: QUIT"<<endl;
                board->printBoard();
                cout<<"R wins the game."<<endl;
                break;
            }

            else
            {
                cout<<"R: QUIT"<<endl;
                board->printBoard();
                cout<<"B wins the game."<<endl;
                break;
            }
        }
        else cerr<<"Invalid move; the game awaits a valid move."<<endl;

        if(board->checkWinner('b'))
        {
            cout<<"B wins the game."<<endl;
            break;
        }
        if(board->checkWinner('r'))
        {
            cout<<"R wins the game."<<endl;
            break;
        }
    }
}
