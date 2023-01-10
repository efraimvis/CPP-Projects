//
// Created by Admin on 1/18/2022.
//

#ifndef HW_6_NUMERIC_H
#define HW_6_NUMERIC_H
#include "MultiSort.h"

class Numeric
{
private:
    vector<Element<double,double> > population;
    int populationSize;
    int varSpaceDim;
    int tarSpaceDim;
    int numCycles;

    /*Generates an output vector of given dimension for a given variables vector
     * according to function described in assignment
     *
     * vars - given variables vector
     * tarDim - dimension of requested target vector
     *
     * return : Returns a target vector of given dimension*/
    vector<double> generateTargetVector(vector<double> vars, int tarDim);

    /*Generates a new variables vector, offset by some random scalar
     *
     * variables - given variables vector
     *
     * return : Returns a new variables vector, with some random offset from given vector*/
    vector<double> offsetVector(vector<double> variables);

    /*Generates a random real value in range (0,1) following normal distribution, using Box-Muller transform
     *
     * return : Returns a random value in range (0,1)*/
    double generateRandom();

    /*Performs a single step of the simulation, as described in assignment*/
    void stepSimulation();

    /*Generates a string representing the output of the simulation*/
    string printTargets();

    /*Runs simulation for number of cycles specified in input file*/
    void Run();

public:
    //Since only a single instance of this class should be made, copy constructor and copy assignment operator were avoided
    //Additionally, there are no data members in this class that are destructible, therefore the default destructor is sufficient

    /*Constructor*/
    Numeric();

    /*Reads representation of vectors from input file, and
     * outputs results of simulation to output file
     *
     * inputFile - directory to input file
     * outputFile - directory to output file*/
    void readFiles(char* inputFile, char* outputFile);

};


#endif //HW_6_NUMERIC_H
