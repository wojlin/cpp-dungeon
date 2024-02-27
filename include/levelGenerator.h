#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H

#include <random>
#include <cmath>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
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

        struct BSP
        {
            nodeBSP root;
            std::string visulatizationBSP;
            std::string visulatizationRooms;
            int recursionAmount;
            int roomsAmount;
            int nodesAmount;
            std::vector<roomBox*> rooms;
        };

        std::string createVisualization(nodeBSP* node);
        std::string createVisualization(roomBox* room);
        std::string visualization(int x, int y, int w, int h);
        int calculateDesiredRoomSize(int dungeonDepth);
        int calculateRecursionsAmount(int dungeonDepth);
        int calculateLevelSize(int dungeonDepth);
        void traverseBSP(BSP* bsp, nodeBSP* node);
        BSP createBSP(int dungeonDepth);
        roomBox createRoom(nodeBSP* node);
        void splitNodeBSP(nodeBSP* node, int depth, int desiredRoomSize);
        int getRandomNumber(int minmumNumber, int maximumNumber);
            
    
    

};



#endif