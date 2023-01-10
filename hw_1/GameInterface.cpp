//
// Created by Admin on 11/19/2021.
//

#include "GameInterface.h"
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;

GameInterface::GameInterface(int numReferees, int maxAthletes):numReferees(numReferees),maxAthletes(maxAthletes)
{
    this->athletes = new Contestant*[maxAthletes]();
    this->numAtheletes = 0;
}

GameInterface::~GameInterface()
{
    delete(this->athletes);
}

int GameInterface::getAthleteIndex(const std::string name)
{
    if(this->numAtheletes > 0)
    {
        int i = 0;

        while (i < this->numAtheletes && i < this->maxAthletes)
        {
            if (this->athletes[i]->getName().compare(name) == 0) break;
            i++;
        }

        if(i < this->numAtheletes) return i;
    }
    return -1;
}

/*Checks if a given string representing a name is legal
*
* name - string representing name
*
* return : Reutrns true if name is legal, false otherwise*/
bool isLegalName(const std::string name)
{
    if(name.size()<= 18 && name.compare("cov") != 0 && name.compare("mean") != 0) return true;
    return false;
}

void GameInterface::inputCompetitor()
{
    string name;
    getline(cin,name);

    if(isLegalName(name))
    {
        int i = 0;

        while (i < this->numAtheletes &&i < this->maxAthletes)
        {
            if (this->athletes[i]->getName().compare(name) == 0) break;
            i++;
        }

        if (i == this->maxAthletes)
        {
            cout << "ERROR: MAX_ATHLETES exceeded"<<endl;
            return;
        }

        char scores[1000];
        cin.getline(scores,sizeof(scores));

        char *token = strtok(scores, ",");
        char* ptr;
        strtof(token,&ptr);

        if(*ptr != '\0')
        {
            cerr << "ERROR: invalid input"<<endl;
            return;
        }

        int j = 0;

        float *scoreArr = new float[this->numReferees];

        while (token && j < this->numReferees)
        {
            float score = strtof(token,&ptr);
            if(*ptr != '\0' || score < 0)
            {
                cerr << "ERROR: invalid input"<<endl;
                return;
            }
            scoreArr[j] = score;
            token = strtok(NULL, ",");
            j++;
        }

        if (!token && (j == this->numReferees))
        {
            if (i == this->numAtheletes)
            {
                this->athletes[i] = new Contestant(name, scoreArr, this->numReferees);
                this->numAtheletes++;
            }
            else this->athletes[i]->inputJudgeScore(scoreArr);
        }
        else
        {
            cerr << "ERROR: invalid input"<<endl;
            return;
        }
    }
    else
    {
        cerr << "ERROR: invalid input"<<endl;
        return;
    }
}

/*Prints a float truncated up to two decimal places
*
* f - given float*/
void printWithPrecision(const float f)
{
    cout<<round(f*100)/100;
}

/*Prints a given vector according to format specified in assignment
*
* vector - given float vector
* name - title
* size - size of given vector
**/
void printVector(const float* vector,const std::string name ,int size)
{
    cout<<name<<"=[";
    for(int i = 0;i<size;i++)
    {
        printWithPrecision(vector[i]);
        if(i < size-1) cout<<",";
    }
    cout<<"]"<<endl;
}

void GameInterface::displayJudgeScore()
{
    std::string name;
    getline(cin, name);
    if(this->numAtheletes > 0 && getAthleteIndex(name) != -1)
    {
        const float* vector = this->athletes[getAthleteIndex(name)]->getJudgeScore();
        printVector(vector,name,this->numReferees);
    }
    else
    {
        cerr<<"ERROR: "<<name<<" does not exist"<<endl;
        return;
    }
}

void GameInterface::displayContestantAverage()
{
    std::string name;
    getline(cin, name);

    if(isLegalName(name) && getAthleteIndex(name) != -1)
    {
        cout<<name<<", ";
        printWithPrecision(this->athletes[getAthleteIndex(name)]->getScoreAverage());
        cout<<endl;
    }
    else
    {
        cerr<<"ERROR: "<<name<<" does not exist"<<endl;
        return;
    }
}

void GameInterface::displayAverages()
{
    if(this->numAtheletes > 0)
    {
        for(int i = 0;i<this->numAtheletes;i++)
        {
            std::string name = this->athletes[i]->getName();
            cout<<name<<", ";
            printWithPrecision(this->athletes[i]->getScoreAverage());
            cout<<endl;
        }
    }
    else
    {
        cerr<<"ERROR: no records in the system"<<endl;
    }
}

float* GameInterface::getAverageVector()
{
    float* averageVector = new float[this->numReferees];
    for (int i = 0; i<this->numReferees;i++)
    {
        float sum = 0;
        for (int j = 0;j<this->numAtheletes;j++)
        {
            sum = sum + (this->athletes[j]->getJudgeScore()[i]);
        }
        averageVector[i] = sum/(this->numAtheletes);
    }
    return averageVector;
}

void GameInterface::displayAverageVector()
{
    if(this->numAtheletes > 0)
    {
        float* vector = getAverageVector();
        printVector(vector,"mean",this->numReferees);
        delete(vector);
    }
    else
    {
        cerr<<"ERROR: no records in the system"<<endl;
    }

}

void GameInterface::displayCovMatrix()
{
    if(numAtheletes > 0)
    {
        cout<<"cov=["<<endl;
        for(int i = 0;i<numReferees;i++)
        {
            for(int j = 0; j<numReferees;j++)
            {
                float element = 0;
                for(int k = 0; k< numAtheletes;k++)
                {
                    if(numAtheletes == 1)
                    {
                        element += (athletes[k]->getJudgeScore()[i] - getAverageVector()[i]) *
                                   (athletes[k]->getJudgeScore()[j] - getAverageVector()[j]);
                    }
                    else
                    {
                        element += ((athletes[k]->getJudgeScore()[i] - getAverageVector()[i]) *
                                   (athletes[k]->getJudgeScore()[j] - getAverageVector()[j]))/(numAtheletes-1);
                    }
                }
                printWithPrecision(element);
                if(j < numReferees-1) cout<<",";
                if(j == numReferees-1) cout<<endl;
            }
        }
        cout<<"]"<<endl;
    }
    else
    {
        cerr<<"ERROR: no records in the system"<<endl;
        return;
    }
}

void GameInterface::runInterface()
{
    int select;
    while(true)
    {
        cin>>select;
        switch (select) {

            case 0:
                return;

            case 1: {
                cin.ignore();
                inputCompetitor();
                break;
            }

            case 2: {
                cin.ignore();
                displayJudgeScore();
                break;
            }

            case 3: {
                cin.ignore();
                displayContestantAverage();
                break;
            }

            case 4: {
                cin.ignore();
                displayAverages();
                break;
            }

            case 5: {
                cin.ignore();
                displayAverageVector();
                break;
            }

            case 6: {
                cin.ignore();
                displayCovMatrix();
                break;
            }

            /**
            default: {
                cin.ignore();
                cerr << "ERROR: invalid command; type 0 for exit" << endl;
                break;
            }**/
        }
    }
}