//
// Created by Admin on 12/20/2021.
//

#ifndef HW_4_ROAD_H
#define HW_4_ROAD_H


class Road
{
private:
    const int start;
    const int end;
    const double length;
    double pollutionConst;
    double pollutionLevel;

public:
    //all data members are primitive, so default destructor is sufficient

    /*Constructor
     *
     * u - "form" intersection
     * v - "to" intersection
     * length - road's length
     * c - pollution constant in road*/
    Road(const int u, const int v, const double length, const double c):start(u),end(v),length(length),pollutionConst(c){this->pollutionLevel = 0;};

    /*Copy constructor for Road*/
    Road(const Road& r):start(r.start),end(r.end),length(r.length),pollutionConst(r.pollutionConst){pollutionLevel = r.pollutionLevel;};

    /*Getter for start ("from" intersection)*/
    const int getStart(){return this->start;};

    /*Getter for end ("to" intersection)*/
    const int getEnd(){return this->end;};

    /*Getter for road length*/
    const double getLength(){return this->length;};

    /*Getter for pollution constant*/
    const double getPollutionConst(){return this->pollutionConst;};

    /*Setter for pollution constant*/
    void setPollutionConst(double c){this->pollutionConst = c;};

    /*Returns pollution level in road*/
    double getPollutionLevel(){return this->pollutionLevel;};

    /*Prefix ++ operator, increments pollution level by pollutionConst/length*/
    Road& operator++()
    {
        pollutionLevel += (pollutionConst/length);
        return *this;
    }

    /*Postfix ++ operator, increments pollution level by pollutionConst/length*/
    Road operator++(int)
    {
        Road r = *this;
        operator++();
        return r;
    };

};


#endif //HW_4_ROAD_H
