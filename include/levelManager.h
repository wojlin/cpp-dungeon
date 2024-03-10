#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <map>

#include "utils.h"


class levelManager
{
    public:
        levelManager(int dungeonDepth, generator::BSP bsp);

        void generatePreview(std::string outputPath, int scale = 10);

    private:
        generator::BSP bsp;
        int levelWidth;
        int levelHeight;
        std::vector<std::vector<manager::levelTile>> levelTiles;

};



#endif