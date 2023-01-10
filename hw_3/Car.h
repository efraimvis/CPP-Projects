//
// Created by Admin on 12/18/2021.
//

#ifndef HW_4_CAR_H
#define HW_4_CAR_H


class Car
{
private:
    const int id;
    int location;
    int numNeighbors;
    int* neighbors;

public:
    //There is no dynamic memory allocation, so the default destructor is sufficient
    //Each car is singular, therefore a copy constructor is undesirable
    //Each car is singular, therefore a copy assignment operator is undesirable

    /*Constructor
     * id - car id number (positive integer)
     * location -car location, integer value between 1 and metropolis size*/
    Car(int id, int location):id(id),location(location){};


    /*Getter for id
     *return : Returns car id*/
    const int getId() const {return this->id;};

    /*Getter for location
     * return : Returns car's location*/
    const int getLocation() const {return this->location;};

    /*Setter for location.
     * location - car's location*/
    void setLocation(int location){if(location > 0) this->location = location;};

    //void setNeighbors(int* neighbors, int numNeighbors){this->neighbors = neighbors; this->numNeighbors = numNeighbors;};
};


#endif //HW_4_CAR_H
