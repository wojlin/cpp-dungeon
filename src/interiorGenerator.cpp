#include "../include/interiorGenerator.h"
#include <fstream>

interiorGenerator::interiorGenerator()
{
}

interiorElements interiorGenerator::createInterior(int dunegonDepth, BSP* bsp)
{

    std::cout << "generating interior..." << std::endl;


    

    entranceCoords entrance = createEntrance(bsp);

    interiorElements interior;
    interior.entrance = entrance;
    interior.playerPos.x = entrance.startingPos.x;
    interior.playerPos.y = entrance.startingPos.y;



    std::cout << "interior generated..." << std::endl;


    return interior;
}


std::vector<std::vector<level::levelTile>> interiorGenerator::createLevelTiles(BSP* bsp)
{

    std::vector<std::vector<level::levelTile>> tiles;

    for(int y = 0; y < bsp->root.height; y++)
    {
        std::vector<level::levelTile> layer;

        for(int x = 0; x < bsp->root.width; x++)
        {
            std::vector<level::TileBase> stack;
            level::wallType::type myType = level::wallType::type::EMPTY;
            level::wallType myItem(myType);
            level::levelTile tile = level::levelTile{0, myItem, stack};
            layer.push_back(tile);
        }
        tiles.push_back(layer);
    }

    for(int i = 0; i < bsp->roomsAmount; i++)
    {
        roomBox* room = bsp->rooms[i];
        
        for(int y = room->posY; y < room->posY+room->height; y++)
        {
            for(int x = room->posX; x < room->posX+room->width; x++)
            {   
                std::vector<level::TileBase> stack;
                level::floorType::type myType = level::floorType::type::NORMAL;
                level::floorType myItem(myType);
                tiles[y][x] = level::levelTile{0, myItem, stack};
            }
        }

        for(int x = room->posX; x < room->posX+room->width; x++)
        {
            std::vector<level::TileBase> stack;
            level::wallType::type myType = level::wallType::type::NORMAL;
            level::wallType myItem(myType);
            tiles[room->posY][x] = level::levelTile{0, myItem, stack};
        }
        
        for(int x = room->posX; x < room->posX+room->width; x++)
        {
            std::vector<level::TileBase> stack;
            level::wallType::type myType = level::wallType::type::NORMAL;
            level::wallType myItem(myType);
            tiles[room->posY + room->height - 1][x] = level::levelTile{0, myItem, stack};
        }
        
        for(int y = room->posY; y < room->posY+room->height; y++)
        {
            std::vector<level::TileBase> stack;
            level::wallType::type myType = level::wallType::type::NORMAL;
            level::wallType myItem(myType);
            tiles[y][room->posX] = level::levelTile{0, myItem, stack};
        }
        
        for(int y = room->posY; y < room->posY+room->height; y++)
        {
            std::vector<level::TileBase> stack;
            level::wallType::type myType = level::wallType::type::NORMAL;
            level::wallType myItem(myType);
            tiles[y][room->posX + room->width - 1] = level::levelTile{0, myItem, stack};
        }
        
    }
    
    for(int i = 0; i < bsp->corridorsAmount; i++)
    {
        corridorLine* corridor = bsp->corridors[i];

        if(corridor->startX == corridor->endX)
        {   
            int start = std::min(corridor->startY, corridor->endY);
            int amount = std::abs(corridor->startY - corridor->endY);
            for(int y = -1; y <= amount; y++)
            {   
                std::vector<level::TileBase> stack;
                level::floorType::type myType = level::floorType::type::NORMAL;
                level::floorType myItem(myType);
                tiles[start + y][corridor->startX] = level::levelTile{0, myItem, stack};

                std::vector<level::TileBase> wallStack;
                level::wallType::type wall = level::wallType::type::NORMAL;
                level::wallType wallItem(wall);
                
                if(!tiles[start + y][corridor->startX - 1].tile.isOfType(level::TileBase::Type::Floor))
                {
                    tiles[start + y][corridor->startX - 1] = level::levelTile{0, wallItem, wallStack};
                }
                if(!tiles[start + y][corridor->startX + 1].tile.isOfType(level::TileBase::Type::Floor))
                {
                    tiles[start + y][corridor->startX + 1] = level::levelTile{0, wallItem, wallStack};
                }                    
            }
        }


        if(corridor->startY == corridor->endY)
        {   
            int start = std::min(corridor->startX, corridor->endX);
            int amount = std::abs(corridor->startX - corridor->endX);
            for(int x = -1; x <= amount; x++)
            {   
                std::vector<level::TileBase> stack;
                level::floorType::type myType = level::floorType::type::NORMAL;
                level::floorType myItem(myType);
                tiles[corridor->startY][start + x] = level::levelTile{0, myItem, stack};

                std::vector<level::TileBase> wallStack;
                level::wallType::type wall = level::wallType::type::NORMAL;
                level::wallType wallItem(wall);
                
                if(!tiles[corridor->startY + 1][start + x].tile.isOfType(level::TileBase::Type::Floor))
                {
                    tiles[corridor->startY + 1][start + x] = level::levelTile{0, wallItem, wallStack};
                }
                if(!tiles[corridor->startY - 1][start + x].tile.isOfType(level::TileBase::Type::Floor))
                {
                    tiles[corridor->startY - 1][start + x] = level::levelTile{0, wallItem, wallStack};
                }                    
            }
        }
  
    }

    return tiles;
}

entranceCoords interiorGenerator::createEntrance(BSP* bsp)
{
    //step 1: find most distanced rooms
    std::pair<roomBox*, roomBox*> mostDistantRooms = std::make_pair(nullptr, nullptr);
    double maxDistance = -1;

    for (size_t i = 0; i < bsp->rooms.size(); ++i) 
    {
        for (size_t j = i + 1; j < bsp->rooms.size(); ++j) 
        {
            double distance = distanceBetweenRooms(bsp->rooms[i], bsp->rooms[j]);

            if (distance > maxDistance) 
            {
                maxDistance = distance;
                mostDistantRooms.first = bsp->rooms[i];
                mostDistantRooms.second = bsp->rooms[j];
            }

        }
    }

    //step 2: randomly place entrances
    roomBox* start = mostDistantRooms.first;
    roomBox* end = mostDistantRooms.second;

    entranceCoords entrance;
    entrance.startingPos.x = getRandomNumber(start->posX + 2, start->posX + start->width - 2);
    entrance.startingPos.y = getRandomNumber(start->posY  + 2, start->posY + start->height - 2);
    entrance.endingPos.x = getRandomNumber(end->posX + 2, end->posX + end->width - 2);
    entrance.endingPos.y = getRandomNumber(end->posY + 2, end->posY + end->height - 2);
    
    return entrance;

}

float interiorGenerator::distanceBetweenRooms(roomBox* room1, roomBox* room2) 
{
    int dx = room1->posX - room2->posX;
    int dy = room1->posY - room2->posY;
    return std::sqrt(dx * dx + dy * dy);
}

int interiorGenerator::getRandomNumber(int minmumNumber, int maximumNumber)
{
    if(minmumNumber > maximumNumber)
    {
        std::string error = "minimum number is higher or equal maximum:";
        error += " min=";
        error += std::to_string(minmumNumber);
        error += " max=";
        error +=  std::to_string(maximumNumber);
        throw std::runtime_error(error);
    }

    if(minmumNumber == maximumNumber)
    {
        return minmumNumber;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(minmumNumber, maximumNumber);
    return distribution(gen);
}