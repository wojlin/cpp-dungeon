#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include "levelGenerator.h"

int launchGame(int argc, char* argv[])
{
    levelGenerator level(1);
    level.generatePreview("preview.png", 10);
    level.print(level.getPlayerPos().x, level.getPlayerPos().y, 40, 40);

    return 0;
}

#endif
