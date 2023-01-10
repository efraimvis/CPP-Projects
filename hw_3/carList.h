//
// Created by Admin on 12/20/2021.
//

#ifndef HW_4_CARLIST_H
#define HW_4_CARLIST_H
#include "carNode.h"

class carList
{
private:
    carNode* head;
    carNode* tail;
    int numNodes;

public:
    carList(){this->head = 0; this->tail = 0; this->numNodes = 0;};
    ~carList();

    void insert(Car* value);
    carNode* getHead(){return this->head;};
    carNode* getTail(){return this->tail;};
    int getNumNodes(){return this->numNodes;};
};


#endif //HW_4_CARLIST_H
