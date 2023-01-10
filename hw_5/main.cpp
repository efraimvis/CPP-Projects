#include "Numeric.h"

/*Runs simulation*/
int main(int argc, char** argv)
{
    try
    {
        Numeric *n = new Numeric();
        n->readFiles(argv[1], argv[2]);
    }
    catch(exception){}

    return 0;
}
