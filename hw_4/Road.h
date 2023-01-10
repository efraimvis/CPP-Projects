//
// Created by Admin on 1/3/2022.
//

#ifndef HW_5_ROAD_H
#define HW_5_ROAD_H


class Road
{
private:
    const int start;
    const int end;
    const double length;
    double pollutionLevel;

public:
    //all data members are primitive, so default destructor is sufficient

    /*Constructor
     *
     * u - "form" intersection
     * v - "to" intersection
     * length - road's length*/
    Road(const int u, const int v, const double length, const double c):start(u),end(v),length(length){this->pollutionLevel = 0;};

    /*Copy constructor for Road*/
    Road(const Road& r):start(r.start),end(r.end),length(r.length){pollutionLevel = r.pollutionLevel;};

    /*Getter for start ("from" intersection)*/
    const int getStart(){return this->start;};

    /*Getter for end ("to" intersection)*/
    const int getEnd(){return this->end;};

    /*Getter for road length*/
    const double getLength(){return this->length;};

    /*Returns pollution level in road*/
    double getPollutionLevel(){return this->pollutionLevel;};

    /*Adds an amount of pollution to road*/
    void addPollution(double addition){ if(addition > 0) this->pollutionLevel += addition;};
};


#endif //HW_5_ROAD_H
