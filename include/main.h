#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include "levelGenerator.h"

int launchGame(int argc, char* argv[])
{
    levelGenerator level(1);
    level.generatePreview("preview.png", 10);

    return 0;
}

#endif
