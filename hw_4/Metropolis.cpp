//
// Created by Admin on 1/3/2022.
//

#include "Metropolis.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdlib.h>

Metropolis::Metropolis(double **graph, unsigned int size)
{
    this->carMap = new Map<std::string, int>();
    this->graph = graph;
    this->cars = new carList();
    this->roads = 0;
    //this->pollutionConst = 0;
    this->numIntersections = size;
    this->intersectionNeighbors = new int[size];

    parseGraph(graph);
}

Metropolis::~Metropolis()
{
    for(int i = 0;i < this->numIntersections;i++)
    {
        delete[] roads[i];
    }
    delete(roads);
    delete(intersectionNeighbors);
    delete(cars);
}

/**
void Metropolis::setPollutionConst(double c)
{
    if(c > 0)
    {
        if(pollutionConst == 0)
        {
            pollutionConst = c;
            initPollution();
        }
    }
}
**/

/**
void Metropolis::initPollution()
{
    if(roads)
    {
        for (int i = 0; i < numIntersections; i++)
        {
            for (int j = 0; j < numIntersections; j++)
            {
                roads[i][j]->setPollutionConst(this->pollutionConst);
            }
        }
    }
}
**/

void Metropolis::parseGraph(double **graph)
{
    roads = new Road**[numIntersections];
    for(int i = 0;i<numIntersections;i++)
    {
        roads[i] = new Road*[numIntersections];
        int numNeighbors = 0;
        for(int j = 0;j<numIntersections;j++)
        {
            double length = graph[i][j];
            roads[i][j] = new Road(i,j,length,0);
            if(length > 0)
            {
                numNeighbors++;
            }
        }

        intersectionNeighbors[i] = numNeighbors;
    }
}

void Metropolis::printPollutionMap()
{
    for(int i = 0; i < numIntersections;i++)
    {
        for(int j = 0; j< numIntersections;j++)
        {
            std::cout<<round((roads[i][j]->getPollutionLevel())*100)/100;
            if(j < numIntersections-1) std::cout<<" ";
            else std::cout<<std::endl;
        }
    }
}

void Metropolis::printCarLocations()
{
    std::string carLocations[numIntersections];
    for(int i = 0;i<numIntersections;i++)
    {
        std::stringstream str;
        str << (i+1) <<":";
        carLocations[i] = str.str();
    }

    carNode* scan = cars->getHead();
    while(scan)
    {
        std::stringstream str;
        //int carLoc = scan->getValue()->getLocation();
        int carLoc = this->carMap->find(scan->getValue()->getId());
        str<<" "<<scan->getValue()->getId();
        carLocations[carLoc-1].append(str.str());
        scan = scan->getNext();
    }

    for(int i = 0;i<numIntersections;i++)
    {
        std::cout<<carLocations[i]<<std::endl;
    }
}

/**
void Metropolis::insertCar(Car* car)
{
    if(car)
    {
        if(car->getId() >= 0 && car->getLocation() > 0 && car->getLocation() <= numIntersections)
        {
            int *carNeighbors;
            if (intersectionNeighbors[car->getLocation() - 1] > 0)
            {
                carNeighbors = new int[intersectionNeighbors[car->getLocation() - 1]];
                int k = 0;
                for (int j = 0; j < numIntersections; j++)
                {
                    if (graph[car->getLocation()- 1][j] > 0)
                    {
                        carNeighbors[k] = j + 1;
                        k++;
                    }
                }
            }
            else carNeighbors = 0;

            //car->setNeighbors(carNeighbors, intersectionNeighbors[car->getLocation() - 1]);
            this->cars->insert(car);
        }
    }
}
**/

void Metropolis::insertCar(std::string id, int location)
{
    if(!id.empty() && location > 0 && location <= numIntersections)
    {
        //std::cout<<id<<" "<<location<<std::endl;
        if(id[0] == 'F' || id[0] == 'S'|| id[0] == 'L'|| id[0] == 'M')
        {
            int *carNeighbors;
            if (intersectionNeighbors[location - 1] > 0)
            {
                carNeighbors = new int[intersectionNeighbors[location - 1]];
                int k = 0;
                for (int j = 0; j < numIntersections; j++)
                {
                    if (graph[location - 1][j] > 0)
                    {
                        carNeighbors[k] = j + 1;
                        k++;
                    }
                }
            }
            else carNeighbors = 0;

            //car->setNeighbors(carNeighbors, intersectionNeighbors[car->getLocation() - 1]);
            if(id[0] == 'F') this->cars->insert(new FamilyCar(id));
            else if(id[0] == 'S') this->cars->insert(new SportsCar(id));
            else if(id[0] == 'L') this->cars->insert(new LuxuryCar(id));
            else if(id[0] == 'M') this->cars->insert(new MASERATI(id));
            this->carMap->insert(id, location);
        }
    }
}

void Metropolis::transitionCar(Car* car)
{
    if(car)
    {
        int carLoc = this->carMap->find(car->getId());
        //std::cout<<carLoc<<std::endl;
        if(carLoc > 0)
        {
            //int carLoc = car->getLocation();
            int numNeighbors = intersectionNeighbors[carLoc-1];
            double intNeighbors[numNeighbors];
            int k = 0;
            for(int j = 0;j<numIntersections;j++)
            {
                if(graph[carLoc-1][j] > 0)
                {
                    intNeighbors[k] = j+1;
                    k++;
                }
            }

            if(dynamic_cast<FamilyCar*>(car) != 0)
            {
                srand(time(0));
                int newLoc = rand();
                newLoc = (newLoc % (numNeighbors + 1));
                if (newLoc != numNeighbors)
                {
                    //car->setLocation(intNeighbors[newLoc]);
                    this->carMap->insert(car->getId(), intNeighbors[newLoc]);
                }
            }

            else if(dynamic_cast<LuxuryCar*>(car) != 0 && dynamic_cast<SportsCar*>(car) == 0)
            {
                srand(time(0));
                int decision = rand();
                if(decision%2 == 0)
                {
                    srand(time(0));
                    int newLoc = rand();
                    newLoc = (newLoc % (numNeighbors));
                    this->carMap->insert(car->getId(), intNeighbors[newLoc]);
                }
            }

            else if(dynamic_cast<SportsCar*>(car) != 0)
            {
                if(numNeighbors > 0)
                {
                    srand(time(0));
                    int newLoc = rand();
                    newLoc = (newLoc % (numNeighbors));
                    this->carMap->insert(car->getId(), intNeighbors[newLoc]);
                }
            }
        }
    }
}

void Metropolis::stepSimulation()
{
    if(this->cars)
    {
        //int counter = 1;
        carNode* scan = this->cars->getHead();
        while(scan)
        {
            //int prev = scan->getValue()->getLocation();
            int prev = this->carMap->find(scan->getValue()->getId());
            transitionCar(scan->getValue());
            int curr = this->carMap->find(scan->getValue()->getId());
            if(prev != curr)
            {
                double pollCo = 1/(roads[prev-1][curr-1]->getLength());
                if(dynamic_cast<FamilyCar*>(scan->getValue()) != 0) roads[prev-1][curr-1]->addPollution(2*pollCo);
                else if(dynamic_cast<LuxuryCar*>(scan->getValue()) != 0) roads[prev-1][curr-1]->addPollution(3*pollCo);
                else if(dynamic_cast<SportsCar*>(scan->getValue()) != 0 && dynamic_cast<LuxuryCar*>(scan->getValue()) == 0) roads[prev-1][curr-1]->addPollution(4*pollCo);
            }
            scan = scan->getNext();
            //counter += pollutionConst;
        }
    }
}
