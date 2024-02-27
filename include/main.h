#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include "levelGenerator.h"

int launchGame(int argc, char* argv[])
{
    levelGenerator generator;
    //for(int i = 1; i < 35; i++)
    //{
    //    generator.createLevel(i);
    //}
    generator.createLevel(1);
    
    
    std::cout << "hello world!" << std::endl;
    return 0;
}

#endif
