#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H

#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <map>

#include "utils.h"

#include "layoutGenerator.h"
#include "interiorGenerator.h"

class levelGenerator
{
    public:
        levelGenerator(int level);

        void generatePreview(std::string outputPath, int scale = 10);

    protected:
        generator::BSP bsp;
        generator::interiorElements interior;

        int dungeonDepth;

        int levelWidth;
        int levelHeight;
        std::vector<std::vector<manager::levelTile>> levelTiles;

        layoutGenerator layoutGen;
        interiorGenerator interiorGen;

};



#endif