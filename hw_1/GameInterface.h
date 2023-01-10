//
// Created by Admin on 11/19/2021.
//

#ifndef HW_2_GAMEINTERFACE_H
#define HW_2_GAMEINTERFACE_H

#include "contestant.h"

class GameInterface
{
private:
    const int numReferees;
    const int maxAthletes;
    int numAtheletes;
    Contestant** athletes;

    /*Finds the index of an athlete with a given name
    *
    * name - contestant's name
    *
    * return : Returns the index of a contestant with a given name*/
    int getAthleteIndex(const std::string name);

    /*Inserts a new athlete into the system*/
    void inputCompetitor();

    /*Displays the vector of judge scores for athlete given by user*/
    void displayJudgeScore();

    /*Displays the average score a an athlete*/
    void displayContestantAverage();

    /*Displays averages of all athletes in the system*/
    void displayAverages();

    /*Calculates the vector of judge score averages
    *
    * finds for each judge the average of his scores, and forms a vector such
    * that each element is an average of one judge's given scores
    *
    * return : Returns a float array representing the average vector*/
    float* getAverageVector();

    /*Displays the vector of judge score averages (mean)*/
    void displayAverageVector();

    /*Displays the covariange matrix of judge scores*/
    void displayCovMatrix();

public:
    GameInterface(int numReferees, int maxAthletes);
    ~GameInterface();

    /**
    int getAthleteIndex(const std::string name);

    void inputCompetitor();
    void displayJudgeScore();
    void displayContestantAverage();
    void displayAverages();

    float* getAverageVector();
    void displayAverageVector();

    void displayCovMatrix();
    **/ 

    /*Runs system interface*/
    void runInterface();


};


#endif //HW_2_GAMEINTERFACE_H
