#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H

#include <random>
#include <cmath>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <map>

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

        struct corridorLine
        {
            int startX;
            int startY;
            int endX;
            int endY;
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
            corridorLine* corridor;
        };

        struct BSP
        {
            nodeBSP root;
            std::string visulatizationBSP;
            std::string visulatizationRooms;
            std::string visulatizationCorridors;
            int recursionAmount;
            int nodesAmount;
            int roomsAmount;
            int corridorsAmount;    
            std::vector<roomBox*> rooms;
            std::vector<corridorLine*> corridors;
        };
        
        level createLevel(int dungeonDepth);

    protected:

        
        std::vector<roomBox*> findRooms(nodeBSP* node);



        // ### VISUALIZATION ###

        std::string createVisualization(nodeBSP* node);
        std::string createVisualization(roomBox* room);
        std::string createVisualization(corridorLine* line);
        std::string visualization(int x, int y, int w, int h);
        


        // ### ROOMS ###

        //creates room for given bsp node
        roomBox createRoom(nodeBSP* node);

        //creates corridors for given node in dunegon
        corridorLine createCorridor(nodeBSP* node);


        // ### BSP ###

        //creates bsp of dungeon
        BSP createBSP(int dungeonDepth); 
        
        //this method recursively splits nodes
        void splitNodeBSP(nodeBSP* node, int desiredRoomSize);
        
        //this method will traverse trough bsp tree and assign rooms etc.
        void traverseBSP(BSP* bsp, nodeBSP* node);
        


        // ### CALCULATIONS ###

        //calculates minimum node size based on recursions amount and node size
        int calculateMinimumNodeSize(int recursionsAmount, int desiredNodeSize);
        
        //calculates level size size based on recusrions amount and desired node size
        int calculateLevelSize(int recusionsAmount, int desiredNodeSize);

        //calculates desired room size based on dungeon depth
        int calculateDesiredNodeSize(int dungeonDepth);

        //calculates recursions amount based on dungeon depth
        int calculateRecursionsAmount(int dungeonDepth);
        


        // ### UTILS ###

        //util function to create random number inclusive
        int getRandomNumber(int minmumNumber, int maximumNumber);
            
};



#endif