//
// Created by Admin on 1/4/2022.
//

#include "carNode.h"
carNode::~carNode()
{
    delete(this->value);
}