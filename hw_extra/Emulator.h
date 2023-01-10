//
// Created by Admin on 2/13/2022.
//

#ifndef HW_7_EMULATOR_H
#define HW_7_EMULATOR_H
#include <iostream>
#include "HFile.h"

class Emulator
{
private:

    /*Converts string representation of integer to integer
     *
     * str - given string
     *
     * return : Returns integer from given string if string is a valid (non negative) integer, -1 otherwise*/
    int getNumericString(std::string str);

    /*Hidden copy constructor
     * Emulator will have singular instance in program, therefore copy constructor functionality is undesirable*/
    Emulator(const Emulator& rhs){}

    /*Hidden copy assignment operator
     * Emulator will have singular instance in program, therefore copy assignment functionality is undesirable*/
    Emulator& operator=(const Emulator& rhs){return *this;}

/*Exception for incorrect command format
 * conatins error message specifying correct command format*/
struct UsageException: public std::exception
{
    const char* command;
    const char* proper;
    UsageException(const char* command,const char* proper):command(command),proper(proper){};
    void printMessage(){std::cout<<"error: USAGE "<<command<<" "<<proper<<std::endl;}
};
public:

    /*Constructor*/
    Emulator(){}

    /*Class does not contain any object-type data members, therefore default destructor is sufficient*/

    /*Reads a single character from specified file in specified position
     *
     * filename - file directory
     * position - position in file
     *
     * throws FileNotOpenException if file does not exist or cannot be opened
     * throws OutOfBoundsException if position is out of bounds for file*/
    void read(const char* filename, unsigned int position);

    /*Writes a specified character to given file in specified position
     *
     * filename - file directory
     * position - position in file
     *
     * throws FileNotOpenException if file does not exist or cannot be opened
     * throws OutOfBoundsException if position is out of bounds for file*/
    void write(const char* filename, unsigned int position, char c);

    /*Runs file emulator*/
    void Run();

};


#endif //HW_7_EMULATOR_H
