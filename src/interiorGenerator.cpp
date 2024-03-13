#include "../include/interiorGenerator.h"
#include <fstream>

interiorGenerator::interiorGenerator()
{
}

interiorElements interiorGenerator::createInterior(int dunegonDepth, BSP* bsp)
{
    std::cout << "generating interior..." << std::endl;
    std::cout << "interior generated..." << std::endl;

    entranceCoords entrance = createEntrance(bsp);

    interiorElements interior;
    interior.entrance = entrance;
    interior.playerPos.x = entrance.startingPos.x;
    interior.playerPos.y = entrance.startingPos.y;
    return interior;
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