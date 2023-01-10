//
// Created by Admin on 1/3/2022.
//

#ifndef HW_5_MAPNODE_H
#define HW_5_MAPNODE_H

template<class K, class V>
class MapNode
{
private:
    K key;
    V value;
    MapNode<K, V> *next;
    MapNode<K, V> *prev;

public:
    /*Constructor
     * key - given key
     * value - given value*/
    MapNode(K key, V value) : key(key) {this->value = value; this->next = 0; this->prev = 0;}

    /*Copy constructor*/
    MapNode(const MapNode<K,V> &other){this->key = other.key; this->value = other.value; this->next = other.next; this->prev = other.prev;}

    /*Destructor*/
    ~MapNode()
    {
        this->key = 0;
        this->value = 0;
        this->next = 0;
        this->prev = 0;
    }

    /*Copy assignment operator deemed unnecessary*/

    /*Getter for key
     * return : Returns key in node*/
    K getKey(){return this->key;}

    /*Getter for value
     * return : Returns value in node*/
    V getValue(){return this->value;}

    /*Getter for next
     * return : Returns next node*/
    MapNode* getNext(){return this->next;}

    /*Getter for prev
     * return : Returns previous node*/
    MapNode* getPrev(){return this->prev;}

    /*Setter for next
     * next - node*/
    void setNext(MapNode* next){this->next = next;}

    /*Setter for prev
     * prev - node*/
    void setPrev(MapNode* prev){this->prev = prev;}

    /*Setter for key
     * key - given key*/
    void setKey(K key){this->key = key;}

    /*Setter for value
     * value - given value*/
    void setValue(V value){this->value = value;}

};


#endif //HW_5_MAPNODE_H
