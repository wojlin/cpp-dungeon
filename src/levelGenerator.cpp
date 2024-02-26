#include "../include/levelGenerator.h"


int levelGenerator::getRandomNumber(int minmumNumber, int maximumNumber)
{
    if(minmumNumber >= maximumNumber)
    {
        std::cerr << "minimum number is higher or equal maximum:";
        std::cerr << " min=" << minmumNumber << " max=" << maximumNumber << std::endl;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(minmumNumber, maximumNumber);
    return distribution(gen);
}

void levelGenerator::traverseBSP(nodeBSP* node)
{
    /*
    std::cout << "node";
    std::cout << " depth:" << node->depth;
    std::cout << " x:" << node->posX;
    std::cout << " y:" << node->posY;
    std::cout << " w:" << node->width;
    std::cout << " h:" << node->height;
    std::cout << std::endl;
    */

    if(node->room != nullptr)
    {
        std::cout << "room ";
        std::cout << " x:" << node->posX;
        std::cout << " y:" << node->posY;
        std::cout << " w:" << node->width;
        std::cout << " h:" << node->height;
        std::cout << std::endl;
    }
    
    if(node->firstNode != nullptr)
    {
        traverseBSP(node->firstNode);
    }

    if(node->secondNode != nullptr)
    {
        traverseBSP(node->firstNode);
    }

}

int levelGenerator::calculateRecursionsAmount(int dungeonDepth)
{
    float calcMin = sqrt(static_cast<float>(dungeonDepth)/1.5)+0.2;
    float calcMax = sqrt(static_cast<float>(dungeonDepth)*2.0)+1.0;
    int minimumRecursion = static_cast<int>(std::floor(calcMin));
    int maximumRecursion = static_cast<int>(std::floor(calcMax));
    int recursionsAmount = getRandomNumber(minimumRecursion, maximumRecursion);
    return recursionsAmount;
}

int levelGenerator::calculateLevelSize(int dungeonDepth)
{
    return (dungeonDepth * 2) + 50;
}

levelGenerator::nodeBSP levelGenerator::createBSP(int dungeonDepth)
{
    
    //step 1: choose rooms amount
    //rooms amount = recursions^2
    int recursionsAmount = calculateRecursionsAmount(dungeonDepth);

    //step 2: choose level size
    int levelSize = calculateLevelSize(dungeonDepth);

    nodeBSP root = {recursionsAmount,0, 0, levelSize, levelSize, nullptr, nullptr, nullptr};

    splitNodeBSP(&root, recursionsAmount);

    return root;
}

void levelGenerator::splitNodeBSP(nodeBSP* node, int depth)
{
    nodeBSP firstNode;
    nodeBSP secondNode;

    firstNode.firstNode = nullptr;
    firstNode.secondNode = nullptr;
    firstNode.room = nullptr;
    firstNode.depth = depth;

    secondNode.firstNode = nullptr;
    secondNode.secondNode = nullptr;
    secondNode.room = nullptr;
    secondNode.depth = depth;

    //step 1: choose random split direction
    int isVerticalSplit = getRandomNumber(0,1);
    //step 2: choose random position
    if(static_cast<bool>(isVerticalSplit))
    {
        int height = getRandomNumber(0, node->height - MINIMUM_ROOM_SIZE);
        firstNode.posX = node->posX;
        firstNode.posY = node->posY;
        firstNode.width = node->width;
        firstNode.height = height;

        secondNode.posX = node->posX;
        secondNode.posY = node->posY + height + 1;
        secondNode.width = node->width;
        secondNode.height = node->height - height - 1;
    }
    else
    {
        int width = getRandomNumber(0, node->width - MINIMUM_ROOM_SIZE);
        firstNode.posX = node->posX;
        firstNode.posY = node->posY;
        firstNode.width = width;
        firstNode.height = node->height;

        secondNode.posX = node->posX + width + 1;
        secondNode.posY = node->posY;
        secondNode.width = node->width - width - 1;
        secondNode.height = node->height;
    }

    node->firstNode = new nodeBSP(firstNode);
    node->secondNode = new nodeBSP(secondNode);

    depth -= 1;
    if(depth >= 0)
    {   
        bool isFirstNodeWidthEnough = node->firstNode->height > MINIMUM_ROOM_SIZE;
        bool isFirstNodeHeightEnough = node->firstNode->width > MINIMUM_ROOM_SIZE;
        
        bool isSecondNodeWidthEnough = node->secondNode->height > MINIMUM_ROOM_SIZE;
        bool isSecondNodeHeightEnough = node->secondNode->width > MINIMUM_ROOM_SIZE;

        if(isFirstNodeWidthEnough && isFirstNodeHeightEnough)
        {
            splitNodeBSP(node->firstNode, depth);
        }else
        {
            
        }

        if(isSecondNodeWidthEnough && isSecondNodeHeightEnough)
        {
            splitNodeBSP(node->secondNode, depth);
        }else
        {

        }
    }else
    {
        node->room = new roomBox(createRoom(node));
    }
}

levelGenerator::roomBox levelGenerator::createRoom(nodeBSP* node)
{
    roomBox room;
    room.posX = node->posX;
    room.posY = node->posY;
    room.width = node->width;
    room.height = node->height;
    return room;
}

level levelGenerator::createLevel(int dungeonDepth)
{
    nodeBSP root = createBSP(dungeonDepth);
    traverseBSP(&root);
    return level();
}