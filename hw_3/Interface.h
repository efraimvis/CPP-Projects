//
// Created by Admin on 12/21/2021.
//

#ifndef HW_4_INTERFACE_H
#define HW_4_INTERFACE_H
#include "Metropolis.h"
#include <fstream>

class Interface
{
private:
    int numIntersections;
    Metropolis* met;

    /*Generates a representation of a graph from input file in given directory
     *
     * intersections - given file directory
     *
     * return : Returns representation of a graph if successful, 0 otherwise*/
    double** readIntersections(char* intersections);

    /*Reads file in given directory and inserts cars into metropolis accordingly
     *
     * cars - given file directory*/
    void readCars(char* cars);

public:

    /*Constructor
     * intersection - directory to input file for intersections
     * cars - directory to input file for cars in intersections*/
    Interface(char* intersections, char* cars);

    /*Destructor*/
    ~Interface();

    /*Runs the simulation*/
    void runSim();
};


#endif //HW_4_INTERFACE_H
