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

    struct coords
    {
        int x;
        int y;
    };

    struct entranceCoords
    {
        coords startingPos;
        coords endingPos;
    };

    

    struct interiorElements
    {
        entranceCoords entrance;
        coords playerPos;
        std::vector<coords> enemys;
        
    };

}

namespace level
{
    class TileBase 
    {
        public:
            enum class Type { Item, Entity, Trap, Floor, Wall };
            Type tileType;

            wchar_t value = L'0';

            TileBase(Type type, wchar_t val) : tileType(type), value(val) {
            }

            bool isOfType(Type type) const {
            return type == tileType;
        }
    };

    class itemType : public TileBase 
    {
        public:
            enum class type: wchar_t
            {
                HERB = L'❀',
                POTION = L'⇩', 
                SCROLL = L'⌘',
                ARMOR = L'♕',
                WEAPON = L'†',
                THROWABLE = L'➳',
                ITEM = L'♲',
                TREASURE = L'⟏',
                GRAVE = L'🕈',
                BUSH = L'𝦵',
                ENTER = L'☰',
                EXIT = L'⦿'
            };

            itemType(type val) : TileBase(Type::Item, static_cast<wchar_t>(val))
            {
            }
    };

    class entityType : public TileBase 
    {
        public:
            enum class type: wchar_t
            {
                PLAYER = L'🯅',
                ENEMY1 = L'🩑',
                ENEMY2 = L'♝',
                ENEMY3 = L'♚',
                ENEMY4 = L'♟',
                ENEMY5 = L'🨀',
                ENEMY6 = L'🩓',
            };

            entityType(type val) : TileBase(Type::Entity, static_cast<wchar_t>(val))
            {
            }
    };

    class trapType : public TileBase 
    {
        public:
            enum class type: wchar_t
            {
                POISON = L'①',
                THUNDER = L'②',
                FIRE = L'③',
                CONFUSSION = L'④',
                DARKNESS = L'⑤',
                WEAKNESS = L'⑥'
            };

            trapType(type val) : TileBase(Type::Trap, static_cast<wchar_t>(val))
            {
            }
    };

    class floorType : public TileBase 
    {
        public:
            enum class type: wchar_t
            {
                NORMAL = L' ',
                DOOR = L'▤',
                HOLE = L'▓',
                PUDDLE = L'░',
            };

            floorType(type val) : TileBase(Type::Floor, static_cast<wchar_t>(val))
            {
            }
    };


    class wallType : public TileBase 
    {
        public:
            enum class type: wchar_t
            {
                EMPTY = L'*',
                NORMAL = L'█',
                LIGHT = L'▟'
            };

            wallType(type val) : TileBase(Type::Wall, static_cast<wchar_t>(val))
            {
            }
    };


    
    

    struct levelTile
    {
        int id;
        TileBase tile;
        std::vector<TileBase> stack;
    };


}

#endif