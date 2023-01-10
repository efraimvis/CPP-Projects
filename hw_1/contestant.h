//
// Created by Admin on 11/19/2021.
//

#ifndef HW_2_CONTESTANT_H
#define HW_2_CONTESTANT_H

#include <string>

class Contestant
{
private:
    int numJudges;
    const std::string name;
    float* judgeScore;

public:
    /*Constructor
    *
    * name - contestant name
    * judgeScore - array representing competitor scores by different judges
    * numJudges - number of judges*/
    Contestant(const std::string name, float* judgeScore, int numJudges);

    /*Destrctor*/
    ~Contestant();
    //Contestant(Contestant const &c);

    /*Sets judge scores
    *
    * judgeScore - array of judge scores*/
    void inputJudgeScore(float* judgeScore);

    /*Getter
    *
    * return : Returns string representing contestant name*/
    const std::string getName();

    /*Getter
    *
    * return : Returns array representing contestant scores by different judges*/
    const float* getJudgeScore();

    /*Returns the contestant's average score
    *
    * return : Returns contestant's average score*/
    float getScoreAverage();
};


#endif //HW_2_CONTESTANT_H
