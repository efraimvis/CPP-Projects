//
// Created by Admin on 12/20/2021.
//

#include "carList.h"


void carList::insert(Car *value)
{
    if(!this->head)
    {
        this->head = new carNode(value);
        this->tail = this->head;
        this->numNodes++;
    }

    else
    {
        this->tail->setNext(new carNode(value));
        this->tail = this->tail->getNext();
        this->numNodes++;
    }
}


carList::~carList()
{
    carNode* current = this->head;
    if(this->head)
    {
        carNode *next;
        while (current != 0)
        {
            next = current->getNext();
            delete (current);
            current = next;
        }
    }
    this->head = this->tail = 0;
    //delete(this);
}