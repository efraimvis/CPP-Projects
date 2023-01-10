#include <iostream>
#include "Interface.h"

/*Runs program with command line arguments for input files*/
int main(int argc, char** argv)
{
    try
    {
        if(argc != 3)
        {
            throw std::exception();
        }
        Interface *i = new Interface(argv[1], argv[2]);
        i->runSim();
    }
    catch(const std::exception&)
    {
        return 0;
    };

    return 0;
}
