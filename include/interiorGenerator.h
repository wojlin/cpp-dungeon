#ifndef INTERIOR_GENERATOR_H
#define INTERIOR_GENERATOR_H

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

using namespace generator;

class interiorGenerator
{
    public:
        interiorGenerator();
        
        interiorElements createInterior(int dunegonDepth, generator::BSP* bsp);

    protected:
        entranceCoords createEntrance(generator::BSP* bsp);

        float distanceBetweenRooms(roomBox* room1, roomBox* room2);

        int getRandomNumber(int minmumNumber, int maximumNumber);


};



#endif