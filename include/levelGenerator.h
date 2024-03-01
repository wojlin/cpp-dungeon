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
        
        level createLevel(int dungeonDepth);

    protected:

        




        // ### VISUALIZATION ###

        std::string createVisualization(nodeBSP* node);
        std::string createVisualization(roomBox* room);
        std::string visualization(int x, int y, int w, int h);
        


        // ### ROOMS ###

        roomBox createRoom(nodeBSP* node);



        // ### BSP ###

        //creates bsp of dungeon
        BSP createBSP(int dungeonDepth); 
        
        //this method recursively splits nodes
        void splitNodeBSP(nodeBSP* node, int desiredRoomSize);
        
        //this method will traverse trough bsp tree and assign rooms etc.
        void traverseBSP(BSP* bsp, nodeBSP* node);
        


        // ### CALCULATIONS ###

        //calculates minimum node size based on recursions amount and level size
        int calculateMinimumNodeSize(int recursionsAmount, int levelSize);
        
        //calculates level size size based on dungeon depth
        int calculateLevelSize(int dungeonDepth);

        //calculates desired room size based on dungeon depth
        int calculateDesiredRoomSize(int dungeonDepth);

        //calculates recursions amount based on dungeon depth
        int calculateRecursionsAmount(int dungeonDepth);
        


        // ### UTILS ###

        //util function to create random number inclusive
        int getRandomNumber(int minmumNumber, int maximumNumber);
            
};



#endif