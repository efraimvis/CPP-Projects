//
// Created by Admin on 1/4/2022.
//

#include <iostream>
#include <cstdlib>
#include <sstream>
#include "Interface.h"
using namespace std;

Interface::Interface(char* intersections, char* cars)
{
    this->met = new Metropolis(readIntersections(intersections), numIntersections);
    readCars(cars);
}

Interface::~Interface()
{
    delete(this->met);
}

void Interface::readCars(char* cars)
{
    std::ifstream file(cars);
    if(!(file.is_open()))
    {
        file.close();
        std::cerr<<"ERROR: Invalid input.\n";
        throw std::exception();
    }
    int lineCounter = 1;
    string line;
    while(getline(file,line))
    {
        int carCounter = 0;
        stringstream head;
        head<<lineCounter<<":";
        istringstream ss(line);
        string token;
        while(getline(ss,token,' '))
        {
            if(carCounter == 0)
            {
                if(token.compare(ss.str()) == 0)
                {
                    break;
                }
                if(token.compare(head.str()) != 0)
                {
                    file.close();
                    std::cerr<<"ERROR: Invalid input.\n";
                    throw std::exception();
                }
                carCounter++;
            }
            else
            {
                if(token[0] != 'F' && token[0] != 'S' && token[0] != 'L' && token[0] != 'M')
                {
                    file.close();
                    std::cerr<<"ERROR: Invalid input.\n";
                    throw std::exception();
                }

                string carId;
                if(!isdigit(token[token.size()-1])) carId = token.substr(0,token.size()-1);
                else carId = token;
                this->met->insertCar(carId, lineCounter);
            }
        }
        lineCounter++;
    }

    file.close();
}

double** Interface::readIntersections(char* intersections)
{
    std::ifstream file(intersections);
    if(!(file.is_open()))
    {
        file.close();
        std::cerr<<"ERROR: Invalid input.";
        throw std::exception();
    }
    std::string line;
    int numIntersections=0;
    getline(file,line);
    numIntersections = atoi(line.c_str());

    if(numIntersections == 0)
    {
        file.close();
        std::cerr<<"ERROR: Invalid input.";
        throw std::exception();
    }
    double** graph = new double*[numIntersections];
    for(int i = 0;i<numIntersections;i++)
    {
        graph[i] = new double[numIntersections];
        for(int j = 0;j<numIntersections;j++)
        {
            graph[i][j] = 0;
        }
    }


    int lineCounter = 0;

    while(getline(file,line))
    {
        int roadCounter = 0;
        istringstream ss(line);
        string token;

        while(getline(ss,token,' '))
        {
            char* ptr;
            double roadLength = strtof(token.c_str(),&ptr);
            if(roadCounter < numIntersections-1)
            {
                if (*ptr != '\0' || roadLength < 0)
                {
                    file.close();
                    std::cerr<<"ERROR: Invalid input.";
                    throw std::exception();
                }
            }
            if(roadLength < 0)
            {
                file.close();
                std::cerr<<"ERROR: Invalid input.";
                throw std::exception();
            }

            if(lineCounter == roadCounter && roadLength != 0)
            {
                file.close();
                std::cerr<<"ERROR: Invalid input.";
                throw std::exception();
            }

            if(roadCounter < numIntersections)
            {
                graph[lineCounter][roadCounter] = roadLength;
            }
            roadCounter++;
        }

        if(roadCounter != numIntersections)
        {
            file.close();
            std::cerr<<"ERROR: Invalid input.";
            throw std::exception();
        }
        lineCounter++;
    }
    file.close();
    this->numIntersections = numIntersections;
    return graph;
}

void Interface::runSim()
{
    int cycles;
    cin>>cycles;
    if(cycles < 0)
    {
        std::cerr<<"ERROR: Invalid input.";
        throw std::exception();
    }

    for(int i = 0;i<cycles;i++)
    {
        this->met->stepSimulation();
    }

    this->met->printPollutionMap();
    this->met->printCarLocations();
}
