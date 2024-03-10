#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include "levelGenerator.h"
#include "levelManager.h"

int launchGame(int argc, char* argv[])
{
    levelGenerator generator;
    levelManager level = generator.createLevel(5);
    level.generatePreview("preview.png", 10);
    
    std::cout << "hello world!" << std::endl;
    return 0;
}

#endif
