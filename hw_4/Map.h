//
// Created by Admin on 1/3/2022.
//

#ifndef HW_5_MAP_H
#define HW_5_MAP_H

#include "Map.h"
#include "MapNode.h"

/*This class implements a generic map, using a linked list of generic nodes*/
template<class K, class V>
class Map
{
private:
    MapNode<K, V> *head;
    MapNode<K, V> *tail;
    int size;

public:
    /*Constructor*/
    Map<K,V>(){this->head = 0; this->tail = 0; this->size = 0;}

    /*Destructor*/
    ~Map<K,V>()
    {
         this->destroyMap();
    }

    /*Getter for size
     * return : Returns map size*/
    int getSize(){return this->size;}

    /*Finds the value for a specified key, if present
     * key - given key
     *
     * return : Returns value for specified key if present, null otherwise*/
    V find(K key)
    {
        if(this->head != 0)
        {
            MapNode<K,V> *scan = this->head;
            while(scan)
            {
                V retval = scan->getValue();
                if(scan->getKey() == key)
                {
                    retval = scan->getValue();
                    return retval;
                }
                scan = scan->getNext();
            }
        }
        return 0;
    }

    /*Removes a key-value pair from the map, if present
     * key - specified key*/
    void clear(K key)
    {
        if(this->head)
        {
            MapNode<K,V> *scan = this->head;
            while(scan)
            {
                if(scan->getKey() == key)
                {
                    if(scan == this->head && scan == this->tail)
                    {
                        delete(scan);
                        this->head = 0;
                        this->tail = 0;
                        this->size = 0;
                    }

                    else if(scan == this->head && scan != this->tail)
                    {
                        this->head->getNext()->setPrev(0);
                        this->head = scan->getNext();
                        scan->setNext(0);
                        delete(scan);
                        this->size--;
                    }

                    else if(scan != this->head && scan == this->tail)
                    {
                        this->tail = scan->getPrev();
                        this->tail->setNext(0);
                        scan->setPrev(0);
                        delete(scan);
                        this->size--;
                    }

                    else if(scan != this->head && scan != this->tail)
                    {
                        scan->getNext()->setPrev(scan->getPrev());
                        scan->getPrev()->setNext(scan->getNext());
                        scan->setNext(0);
                        scan->setPrev(0);
                        delete(scan);
                        this->size--;
                    }
                }
                else scan = scan->getNext();
            }
        }
    }

    /*Removes all key-value pairs from the map*/
    void destroyMap()
    {
        if(this->head)
        {
            MapNode<K,V> *scan = this->head;
            while(scan)
            {
              MapNode<K,V> *temp = scan;
              scan = scan->getNext();
              temp->setNext(0);
              if(scan) scan->setPrev(0);
              delete(temp);
              this->size--;
            }
            this->head = 0;
            this->tail = 0;
        }
    }

    /*Prints map, in format specified in assignment*/
    void print()
    {
        if(this->head)
        {
            MapNode<K,V> *scan = this->head;
            while(scan)
            {
                std::cout<<scan->getKey()<<" "<<scan->getValue()<<std::endl;
                scan = scan->getNext();
            }
        }
    }

    /*Inserts a single key-value pair into the map
     * if key is already present, its value will be overwritten by the new value
     *
     * key - given key
     * value - given value*/
    void insert(K key, V value)
    {
        if (&key != 0 && &value != 0)
        {
            if (this->head == 0)
            {
                this->head = new MapNode<K, V>(key, value);
                this->tail = this->head;
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
                    scan->setValue(value);
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
};


#endif //HW_5_MAP_H
