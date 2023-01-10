//
// Created by Admin on 1/3/2022.
//

#ifndef HW_5_CAR_H
#define HW_5_CAR_H
#include <iostream>

class Car
{
private:
    const std::string id;

public:
    //There is no dynamic memory allocation, so the default destructor is sufficient
    //Each car is singular, therefore a copy constructor is undesirable
    //Each car is singular, therefore a copy assignment operator is undesirable

    /*Constructor
     * id - car id number (positive integer)*/
    Car(std::string id):id(id){};

    virtual ~Car(){};


    /*Getter for id
     *return : Returns car id*/
    virtual const std::string getId() const {return this->id;};

    /*Overridden '<' operator
     * applies order relation to cars by lexicographic order of their id's*/
    friend bool operator<(const Car& lhs, const Car& rhs)
    {
        return (lhs.id < rhs.id);
    }

    /*Overridden '>' operator
     * applies order relation to cars by lexicographic order of their id's*/
    friend bool operator>(const Car& lhs, const Car& rhs)
    {
        return (lhs.id > rhs.id);
    }

    /*Overridden '==' operator
     * applies order relation to cars by lexicographic order of their id's*/
    friend bool operator==(const Car& lhs, const Car& rhs)
    {
        return (lhs.id == rhs.id);
    }

    /*Overridden '<<' operator
     * prints car's id*/
    friend std::ostream& operator<<(std::ostream &out, const Car& c)
    {
        out << c.id;
        return out;
    }

};

/*Derived class SportsCar*/
class SportsCar : virtual public Car
{
public:
    /*Constructor*/
    SportsCar(std::string id):Car(id){}
};

/*Derived class FamilyCar*/
class FamilyCar :virtual public Car
{
public:
    /*Constructor*/
    FamilyCar(std::string id):Car(id){}
};

/*Derived class LuxuryCar*/
class LuxuryCar : virtual public Car
{
public:
    /*Constructor*/
    LuxuryCar(std::string id):Car(id){}
};

/*Derived class MASERATI*/
class MASERATI : public SportsCar, public LuxuryCar
{
public:
    /*Constructor*/
    MASERATI(std::string id): Car(id) ,SportsCar(id), LuxuryCar(id){}
};


#endif //HW_5_CAR_H
