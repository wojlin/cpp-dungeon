#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include "levelGenerator.h"

int launchGame(int argc, char* argv[])
{
    levelGenerator generator;
    generator.createLevel(0);
    
    std::cout << "hello world!" << std::endl;
    return 0;
}

#endif
