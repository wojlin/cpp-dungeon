#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <iostream>

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


class level
{
    public:
        void show();

    private:
        int levelWidth;
        int levelHeight;
        std::vector<std::vector<levelTile>> levelTiles;



};



#endif