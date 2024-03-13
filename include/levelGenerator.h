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
#include <ncursesw/ncurses.h>
#include "utils.h"

#include "layoutGenerator.h"
#include "interiorGenerator.h"

class levelGenerator
{
    public:
        levelGenerator(int level);

        coords getPlayerPos();
        
        void generatePreview(std::string outputPath, int scale = 10);

        void print(int x, int y, int windowWidth, int windowHeight);
        
        std::vector<std::vector<level::levelTile*>> getLevelSector(int startX, int startY, int width, int height);

    protected:
        generator::BSP bsp;
        generator::interiorElements interior;

        int dungeonDepth;

        int levelWidth;
        int levelHeight;
        std::vector<std::vector<level::levelTile>> levelTiles;

        layoutGenerator layoutGen;
        interiorGenerator interiorGen;

};



#endif