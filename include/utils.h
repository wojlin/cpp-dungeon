#ifndef UTILS_H
#define UTILS_H


namespace generator
{
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

    struct entranceCoords
    {
        int startingPosX;
        int startingPosY;
        int endingPosX;
        int endingPosY;
    };

    struct enemy
    {
        int posX;
        int posY;
    };

    struct interiorElements
    {
        entranceCoords entrance;
        std::vector<enemy> enemys;
    };

}

namespace manager
{
    namespace Trap 
    {
        enum trapType
        {
            POISON,
            FIRE,
            CONFUSSION,
            DARKNESS,
            WEAKNESS
        };
    }

    namespace Floor 
    {
        enum floorType
        {
            NORMAL,
            DOOR,
            WATER,
            PUDDLE,
            TRAP,
            BUSH,
            TREASURE,
            GRAVE
        };
    }

    namespace Wall 
    {
        enum wallType
        {
            NORMAL,
            LIGHT
        };
    }

    struct levelTile
    {
        int id;
    };


}

#endif