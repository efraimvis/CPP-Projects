//
// Created by Admin on 1/4/2022.
//

#ifndef HW_5_CARLIST_H
#define HW_5_CARLIST_H
#include "carNode.h"

class carList
{
private:
    carNode* head;
    carNode* tail;
    int numNodes;

public:

    /*Constructor*/
    carList(){this->head = 0; this->tail = 0; this->numNodes = 0;};

    /*Destructor*/
    ~carList();

    /*Inserts a new car into the list
     * value - new car to insert*/
    void insert(Car* value);

    /*Getter for head
     * return : Returns list's head*/
    carNode* getHead(){return this->head;};

    /*Getter for tail
     * return : Returns list's tail*/
    carNode* getTail(){return this->tail;};

    /*Returns the number of cars in the list*/
    int getNumNodes(){return this->numNodes;};
};


#endif //HW_5_CARLIST_H
