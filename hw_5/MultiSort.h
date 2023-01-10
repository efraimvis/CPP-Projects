//
// Created by Admin on 1/15/2022.
//

#ifndef HW_6_MULTISORT_H
#define HW_6_MULTISORT_H
#include <iostream>
#include "Element.h"

template<class T,class V>
class MultiSort
{
private:
    /*Helper function to sort a given vector of elements with respect to rank
     *
     * elements - given vector of elements*/
    void insertionSort(vector<Element<T,V> > &elements)
    {
        if(!elements.empty())
        {
            int n = elements.size();
            Element<T,V> key;
            int j;
            for (int i = 1; i < n; i++)
            {
                key = elements[i];
                j = i - 1;

                while (j >= 0 && elements[j].getRank() > key.getRank())
                {
                    elements[j + 1] = elements[j];
                    j = j - 1;
                }
                elements[j + 1] = key;
            }
        }
    }



public:
    /*Implementation of ParetoRanking from assignment,
     * takes a vector of target vectors, and returns a vector
     * containing their ranks
     *
     * targets - vector of target vectors
     *
     * return : Returns a vector of ranks for given vector of target vector*/
    vector<int> ParetoRanking(vector<vector<T> > targets)
    {
        vector<int> ranks;
        if(!targets.empty())
        {
            if(!targets[0].empty())
            {
                int numVectors = targets.size();
                int dim = targets[0].size();
                vector<int> ranks;
                ranks.assign(numVectors,0);

                for(int n = 0; n< numVectors;n++)
                {
                    if(targets[n].size() != dim)
                    {
                        ranks.resize(0);
                        return ranks;
                    }
                    for(int i = 0;i<numVectors;i++)
                    {
                        if(i != n)
                        {
                            bool proper = false;
                            bool le = true;
                            for(int j = 0; j< dim;j++)
                            {
                                if((targets[i])[j] < (targets[n])[j]) proper = true;

                                if((targets[n])[j] < (targets[i])[j])
                                {
                                    le = false;
                                    break;
                                }
                            }

                            if(proper == true && le == true) ranks[n]++;
                        }
                    }
                }

                return ranks;

            }
        }
        return ranks;
    }

    /*Sorts given vector of elements, according to rank - assuming rank is correct
     *
     * elements - given vector of elements*/
    void ElementsReordering(vector<Element<T,V> > &elements)
    {
        insertionSort(elements);
    }

    /*Implementation of ParetoSorting from assignment
     *
     * elements - given vector of elements*/
    void ParetoSorting(vector<Element<T,V> > &elements)
    {
        int numElements = elements.size();
        vector<vector<T> > targets;
        vector<int> ranks;
        for(int i = 0;i<numElements;i++)
        {
            targets.push_back(elements[i].getTargets());
        }

        ranks = ParetoRanking(targets);
        if(ranks.empty()) return;

        for(int i = 0;i<numElements;i++)
        {
            elements[i].setRank(ranks[i]);
        }

        ElementsReordering(elements);

    }
};


#endif //HW_6_MULTISORT_H
