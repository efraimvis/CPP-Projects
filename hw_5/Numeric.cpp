//
// Created by Admin on 1/18/2022.
//

#include <fstream>
#include "Numeric.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

Numeric::Numeric()
{
    this->population = vector<Element<double,double> >();
    this->populationSize = 0;
    this->varSpaceDim = 0;
    this->tarSpaceDim = 0;
    this->numCycles = 0;
}

void Numeric::readFiles(char *inputFile, char *outputFile)
{
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);
    if(!(input.is_open() && output.is_open()))
    {
        if(!input.is_open() && output.is_open())
        {
            input.close();
            output.close();
            std::cerr << "ERROR: " << inputFile << " does not exist or cannot be opened\n";
            throw std::exception();
        }

        else if(input.is_open() && !output.is_open())
        {
            input.close();
            output.close();
            std::cerr << "ERROR: " << outputFile << " does not exist or cannot be opened\n";
            throw std::exception();
        }

        else
        {
            input.close();
            output.close();
            std::cerr << "ERROR: does not exist or cannot be opened\n";
            throw std::exception();
        }
    }

    int lineCounter = 0;
    string line;

    int populationSize=0;
    int varSpaceDim=0;
    int tarSpaceDim=0;
    int numCycles=0;

    input >> populationSize >> varSpaceDim >> tarSpaceDim >> numCycles;
    if(!(populationSize > 0 && varSpaceDim > 0 && tarSpaceDim > 0 && numCycles > 0 && varSpaceDim > tarSpaceDim))
    {
        input.close();
        output.close();
        std::cerr << "ERROR: simulation definition in "<<inputFile<<" is invalid\n";
        throw std::exception();
    }
    else
    {
        this->populationSize = populationSize;
        this->varSpaceDim = varSpaceDim;
        this->tarSpaceDim = tarSpaceDim;
        this->numCycles = numCycles;
    }

    getline(input,line);

    this->population.resize(populationSize);
    vector<Element<double, double> > population;

    while(getline(input,line))
    {
        int vectDimCounter = 0;
        vector<double> vars = vector<double>(varSpaceDim);
        istringstream ss(line);
        double coord;
        while(ss>>coord)
        {
            if(vectDimCounter >= varSpaceDim)
            {
                input.close();
                output.close();
                std::cerr << "ERROR: population definition in "<<inputFile<<" at line "<<lineCounter+2<<" is invalid\n";
                throw std::exception();
            }

            vars[vectDimCounter] = coord;
            vectDimCounter++;
        }

        if(vectDimCounter != varSpaceDim)
        {
            input.close();
            output.close();
            std::cerr << "ERROR: population definition in "<<inputFile<<" at line "<<lineCounter+2<<" is invalid\n";
            throw std::exception();
        }


        vector<double> tars = vector<double>(tarSpaceDim);
        tars = generateTargetVector(vars, tarSpaceDim);
        Element<double,double> e = Element<double,double>(vars,tars);
        population.push_back(e);
        lineCounter++;
    }
    if(lineCounter != populationSize)
    {
        input.close();
        output.close();
        std::cerr << "ERROR: population definition in "<<inputFile<<" at line "<<lineCounter+2<<" is invalid\n";
        throw std::exception();
    }

    input.close();

    this->population = population;
    Run();
    cout<<printTargets();
    output<<printTargets();
    output.close();
}

vector<double> Numeric::generateTargetVector(vector<double> vars, int tarDim)
{
    vector<double> target;
    target.resize(tarDim);

    for(int i =0; i <tarDim;i++)
    {
        double coord = 0;
        for(unsigned int j = 0;j<vars.size();j++)
        {
            coord += (pow((vars[j]-(i+1)),2));
        }
        target[i] = coord;
    }

    return target;
}

double Numeric::generateRandom()
{
    srand(time(0));
    double y1= ( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. );
    double y2= ( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. );
    double temp = cos(2*3.14*y2)*sqrt(-2.*log(y1));
    double retval = fmod(abs(temp),1);
    if(retval == 0) return retval+0.5;
    return retval;
}

vector<double> Numeric::offsetVector(vector<double> variables)
{
    double offset = generateRandom();
    vector<double> newVect;
    newVect.resize(variables.size());
    for(unsigned int i = 0;i<variables.size();i++)
    {
        newVect[i] = variables[i]+offset;
    }

    return newVect;
}

void Numeric::stepSimulation()
{
    this->population.resize(2*this->populationSize);
    for(int i = 0;i<this->populationSize;i++)
    {
        vector<double> offsetVect = offsetVector(this->population[i].getVariables());
        vector<double> newTarget = generateTargetVector(offsetVect, this->tarSpaceDim);
        this->population[i+populationSize] = Element<double,double>(offsetVect,newTarget);
    }
    MultiSort<double, double> ms;
    ms.ParetoSorting(this->population);

    this->population.resize(this->populationSize);
}

string Numeric::printTargets()
{
    stringstream text;
    for(int i = 0;i<this->populationSize;i++)
    {
        for(int j = 0;j<this->tarSpaceDim;j++)
        {
            double temp = round(this->population[i].getTargets()[j]*1000000)/1000000;
            text << temp;
            if(j < this->tarSpaceDim-1) text << " ";
            else text << "\n";
        }
    }

    return text.str();
}

void Numeric::Run()
{
    for(int i = 0;i<this->numCycles;i++)
    {
        stepSimulation();
    }
}