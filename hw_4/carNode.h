//
// Created by Admin on 1/4/2022.
//

#ifndef HW_5_CARNODE_H
#define HW_5_CARNODE_H
#include "Car.h"

class carNode
{
private:
    Car* value;
    carNode* next;

public:

    /*Constructor
     * value - given car*/
    carNode(Car* value){this->value = value; this->next = 0;};

    /*Destructor*/
    ~carNode();

    /*Getter for value
     *
     * return : Returns car in node*/
    Car* getValue(){return this->value;};

    /*Getter for next
     *
     * return : Returns pointer to next node*/
    carNode* getNext(){return this->next;};

    /*Setter for next.
     * next - pointer to next node*/
    void setNext(carNode* next){this->next = next;};
};


#endif //HW_5_CARNODE_H
