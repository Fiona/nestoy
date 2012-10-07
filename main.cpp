/**
 * Just messing
 */

#include <string>
#include <iostream>
#include "Core.h"


int main(int argc, char* argv[])
{

    try
    {
        if(argv[1] == NULL)
            throw "Please supply NES iROM file as parameter.";

        Core::Instance()->Load_And_Execute_ROM(argv[1]);
    }
    catch(char const* e)
    {
        std::cout << "Exception caught: " << e << std::endl;
        return 0;
    }
    
    return 1;

}
