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

class interiorGenerator
{
    public:
        interiorGenerator();

        
        void createInterior(int dunegonDepth, generator::BSP* bspTree);

    protected:

};



#endif