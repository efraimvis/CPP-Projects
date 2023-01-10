//
// Created by Admin on 1/15/2022.
//

#ifndef HW_6_ELEMENT_H
#define HW_6_ELEMENT_H
#include <vector>

using namespace std;

template<class T, class V>
class Element
{
private:
    vector<T> targets;
    vector<V> variables;
    int rank;
public:
    //Since the type of T is not known in advance, it is not guaranteed that the vectors 'targets' and 'variables' can be deleted,
    //therefore the default destructor will be relied upon.
    //Additionally, since the variables and target vectors for an element are not changeable, the copy assignment operator was not overridden

    /*Constructor*/
    Element<T,V>()
    {
        this->targets = vector<T>();
        this->variables = vector<V>();
        this->rank = 0;
    };

    /*Constructor*/
    Element<T,V>(vector<V> vars, vector<T> tars, int rank = 0)
    {
        this->variables = vars;
        this->targets = tars;
        this->rank = rank;
    }

    /*Copy constructor*/
    Element<T,V>(const Element<T,V> &other)
    {
        this->variables = other.variables;
        this->targets = other.targets;
        this->rank = other.rank;
    }

    /*Getter for targets vector's rank*/
    int getRank(){return this->rank;}

    /*Getter for targets vector*/
    vector<T> getTargets(){return this->targets;}

    /*Getter for variables vector*/
    vector<V> getVariables(){return this->variables;}

    /*Setter for rank*/
    void setRank(int rank)
    {
        if(rank >= 0) this->rank = rank;
    }

};


#endif //HW_6_ELEMENT_H