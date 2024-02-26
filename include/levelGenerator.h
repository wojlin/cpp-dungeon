#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H

#define MINIMUM_ROOM_SIZE 5

#include <random>
#include <cmath>
#include <vector>

#include "level.h"



class levelGenerator
{
    public:
        level createLevel(int dungeonDepth);

    private:

        struct roomBox
        {
            int posX;
            int posY;
            int width;
            int height;
        };

        struct nodeBSP
        {
            int depth;
            int posX;
            int posY;
            int width;
            int height;
            nodeBSP* firstNode;
            nodeBSP* secondNode;
            roomBox* room;
        };

        
        
        int calculateRecursionsAmount(int dungeonDepth);
        int calculateLevelSize(int dungeonDepth);
        void traverseBSP(nodeBSP* node);
        nodeBSP createBSP(int dungeonDepth);
        roomBox createRoom(nodeBSP* node);
        void splitNodeBSP(nodeBSP* node, int depth);
        int getRandomNumber(int minmumNumber, int maximumNumber);
            
    
    

};



#endif