//
// Created by Admin on 1/3/2022.
//

#include <iostream>
#include "Map.h"

/**
template<class K, class V>
void Map<K, V>::insert(K key, V value)
{
    if (&key != 0 && &value != 0)
    {
        if (this->head == 0)
        {
            this->head = new MapNode<K, V>(key, value);
            this->size++;
        }
        else if (key < this->head->getKey())
        {
            MapNode<K, V> *newNode = new MapNode<K, V>(key, value);
            newNode->setNext(this->head);
            this->head->setPrev(newNode);
            this->head = newNode;
            this->size++;
        }
        else if (this->tail->getKey() < key)
        {
            MapNode<K, V> *newNode = new MapNode<K, V>(key, value);
            newNode->setPrev(this->tail);
            this->tail->setNext(newNode);
            this->tail = newNode;
            this->size++;
        }
        else
        {
            MapNode<K, V> *scan = this->head;
            while (scan->getKey() < key) scan = scan->getNext();
            if (scan->getKey() == key)
            {
                scan->setKey(key);
            }
            else
            {
                MapNode<K, V> *newNode = new MapNode<K, V>(key, value);
                newNode->setNext(scan);
                newNode->setPrev(scan->getPrev());
                scan->getPrev()->setNext(newNode);
                scan->setPrev(newNode);
                this->size++;
            }
        }
    }
}
 **/

/**
template<class K, class V>
void Map<K, V>::print()
{
    if(this->head)
    {
        MapNode<K,V> *scan = this->head;
        int counter = 0;
        while(scan)
        {
            std::cout<<scan->getKey()<<" "<<scan->getValue();
            counter++;
            if(counter < this->size-1) std::cout<<std::endl;
        }
    }
}
 **/

