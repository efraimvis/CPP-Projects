//
// Created by Admin on 12/20/2021.
//
#include <iostream>
#include "carNode.h"

/**
carNode::~carNode()
{
    carNode* current = this->next;
    carNode* next;
    while(current != 0)
    {
        next = current->next;
        delete(current->value);
        delete(current);
        current = next;
    }
    delete(this->value);
    delete(this);
}
**/

carNode::~carNode()
{
    delete(this->value);
    //delete(this);
}
