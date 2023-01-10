//
// Created by Admin on 1/3/2022.
//

#ifndef HW_5_METROPOLIS_H
#define HW_5_METROPOLIS_H
#include "carList.h"
#include "Road.h"
#include "Map.h"
#include <iostream>


class Metropolis
{
private:
    Map<std::string, int> *carMap;
    double** graph;
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

    /*Prints a two-dimensional array representing pollution in roads*/
    void printPollutionMap();

    /*Prints the locations of all cars in the metropolis*/
    void printCarLocations();

    /*Inserts a given car into the metropolis
     *
     * id - given car id
     * location - given car location*/
    void insertCar(std::string id, int location);

    /*Steps the simulation once - some cars will transition to different intersections,
     * and the pollution levels in the metropolis will change accordingly*/
    void stepSimulation();
};


#endif //HW_5_METROPOLIS_H
