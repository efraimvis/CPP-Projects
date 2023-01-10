//
// Created by Admin on 12/20/2021.
//

#ifndef HW_4_METROPOLIS_H
#define HW_4_METROPOLIS_H
#include "carList.h"
#include "Road.h"

class Metropolis
{
private:
    double** graph;
    double pollutionConst;
    Road*** roads;
    carList* cars;
    int numIntersections;
    int* intersectionNeighbors;

    /*Initializes internal Road array from given graph
     *
     * graph - graph of intersections
     **/
    void parseGraph(double** graph);

    /*Initializes all roads to have internal pollution coefficient*/
    void initPollution();

    /*Randomly selects if a car should move to one of its intersection's available neighbors
     *
     * car - given car*/
    void transitionCar(Car* car);

public:
    //Metropolis is singular, therefore copy constructor and copy assignment operator are unnecessary

    /*Constructor
     *
     * graph - given representation of a graph
     * size - dimension-n of nxn graph*/
    Metropolis(double** graph, unsigned int size);

    /*Destructor*/
    ~Metropolis();

    /*Sets pollution coefficient for metropolis, only if it has not been previously set (is currently 0)
     *
     * c - pollution coefficient*/
    void setPollutionConst(double c);

    /*Prints a two-dimensional array representing pollution in roads*/
    void printPollutionMap();

    /*Prints the locations of all cars in the metropolis*/
    void printCarLocations();

    /*Inserts a given car into the metropolis
     *
     * car - given car*/
    void insertCar(Car* car);

    /*Steps the simulation once - some cars will transition to different intersections,
     * and the pollution levels in the metropolis will change accordingly*/
    void stepSimulation();
};


#endif //HW_4_METROPOLIS_H
