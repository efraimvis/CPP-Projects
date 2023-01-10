//
// Created by Admin on 11/19/2021.
//

#include "contestant.h"

/*Constructor
*
* name - contestant name
* judgeScore - array representing competitor scores by different judges
* numJudges - number of judges*/
Contestant::Contestant(const std::string name, float* judgeScore, int numJudges):name(name)
{
    this->numJudges = numJudges;
    this->judgeScore = judgeScore;
}

/*Sets judge scores
*
* judgeScore - array of judge scores*/
void Contestant::inputJudgeScore(float *judgeScore)
{
    this->judgeScore = judgeScore;
}

/*Getter
*
* return : Returns string representing contestant name*/
const std::string Contestant::getName()
{
    return this->name;
}

/*Getter
*
* return : Returns array representing contestant scores by different judges*/
const float* Contestant::getJudgeScore()
{
    return this->judgeScore;
}

/*Returns the contestant's average score
*
* return : Returns contestant's average score*/
float Contestant::getScoreAverage()
{
    float counter = 0;
    for(int i = 0;i<this->numJudges;i++)
    {
        counter += this->judgeScore[i];
    }
    return counter/this->numJudges;
}

/*Destrctor*/
Contestant::~Contestant()
{
    delete(this->judgeScore);
}



