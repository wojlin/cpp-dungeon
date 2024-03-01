#include "../include/levelGenerator.h"


int levelGenerator::getRandomNumber(int minmumNumber, int maximumNumber)
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

void levelGenerator::traverseBSP(BSP* bsp, nodeBSP* node)
{
    
    std::cout << "node";
    std::cout << " depth:" << node->depth;
    std::cout << " x:" << node->posX;
    std::cout << " y:" << node->posY;
    std::cout << " w:" << node->width;
    std::cout << " h:" << node->height;
    
    bsp->nodesAmount += 1;
    bsp->visulatizationBSP += (createVisualization(node) + "\n");


    if(node->room != nullptr)
    {
        std::cout << " room ";
        std::cout << " x:" << node->posX;
        std::cout << " y:" << node->posY;
        std::cout << " w:" << node->width;
        std::cout << " h:" << node->height;
        bsp->rooms.push_back(node->room);
        bsp->roomsAmount += 1;
        bsp->visulatizationRooms += (createVisualization(node) + "\n");
    }

    std::cout << std::endl;
    
    if(node->firstNode != nullptr)
    {
        traverseBSP(bsp, node->firstNode);
    }

    if(node->secondNode != nullptr)
    {
        traverseBSP(bsp, node->secondNode);
    }

}

int levelGenerator::calculateMinimumNodeSize(int recursionsAmount, int levelSize)
{
    return static_cast<int>(std::floor( (1.0 / pow(2, recursionsAmount) ) * levelSize ));
}

int levelGenerator::calculateDesiredRoomSize(int dungeonDepth)
{
    return static_cast<int>(std::floor(sqrt(static_cast<float>(dungeonDepth)*2.0)+9.0));
}

int levelGenerator::calculateRecursionsAmount(int dungeonDepth)
{
    float calcMin = sqrt(static_cast<float>(dungeonDepth)/1.5)+1.2;
    float calcMax = sqrt(static_cast<float>(dungeonDepth)*2.0)+1.7;
    int minimumRecursion = static_cast<int>(std::floor(calcMin));
    int maximumRecursion = static_cast<int>(std::floor(calcMax));

    int recursionsAmount = getRandomNumber(minimumRecursion, maximumRecursion);
    return recursionsAmount;
}

int levelGenerator::calculateLevelSize(int dungeonDepth)
{
    return (dungeonDepth * 3) + 50;
}

levelGenerator::BSP levelGenerator::createBSP(int dungeonDepth)
{
    
    //step 1: choose rooms amount
    //rooms amount = recursions^2
    int recursionsAmount = calculateRecursionsAmount(dungeonDepth);

    //step 2: choose level size
    int levelSize = calculateLevelSize(dungeonDepth);

    //step 3: choose room size
    int desiredRoomSize = calculateDesiredRoomSize(dungeonDepth);
    
    nodeBSP root = {recursionsAmount,0, 0, levelSize, levelSize, nullptr, nullptr, nullptr};

    splitNodeBSP(&root, desiredRoomSize);
    
    BSP bsp;
    bsp.root = root;
    bsp.recursionAmount = recursionsAmount;
    
    return bsp;
}

void levelGenerator::splitNodeBSP(nodeBSP* node, int desiredRoomSize)
{
    int depth = node->depth;

    if(depth >= 0)
    {
        nodeBSP firstNode;
        nodeBSP secondNode;

        firstNode.firstNode = nullptr;
        firstNode.secondNode = nullptr;
        firstNode.room = nullptr;
        

        secondNode.firstNode = nullptr;
        secondNode.secondNode = nullptr;
        secondNode.room = nullptr;

        bool widthEnough = node->width > desiredRoomSize * (depth + 1);
        bool heightEnough = node->height > desiredRoomSize * (depth + 1);
        
        if(!widthEnough && !heightEnough)
        {
            throw std::runtime_error("error during creation of bsp tree");
        }


        //step 1: choose random split direction
        int isVerticalSplit;
        if(widthEnough && heightEnough)
        {
            isVerticalSplit = getRandomNumber(0,1);
        } 
        else if (!widthEnough)
        {
            isVerticalSplit = 1;
        }
        else
        {
            isVerticalSplit = 0;
        }
        //step 2: choose random position
        if(static_cast<bool>(isVerticalSplit))
        {

            int min = desiredRoomSize * depth;
            int max = node->height - (desiredRoomSize * depth);
            if(min > max)
            {
                throw std::range_error("not enough space to create node. try increasing level size");
            }

            int height = getRandomNumber(min, max);
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
            int min = desiredRoomSize * depth;
            int max = node->width - (desiredRoomSize * depth);
            if(min > max)
            {
                throw std::range_error("not enough space to create node. try increasing level size");
            }

            int width = getRandomNumber(min, max);
            firstNode.posX = node->posX;
            firstNode.posY = node->posY;
            firstNode.width = width;
            firstNode.height = node->height;

            secondNode.posX = node->posX + width + 1;
            secondNode.posY = node->posY;
            secondNode.width = node->width - width - 1;
            secondNode.height = node->height;
        }
        
        depth -= 1;
        firstNode.depth = depth;
        secondNode.depth = depth;

        node->firstNode = new nodeBSP(firstNode);
        node->secondNode = new nodeBSP(secondNode);

        splitNodeBSP(node->firstNode, desiredRoomSize);
        splitNodeBSP(node->secondNode, desiredRoomSize);
    }
    else
    {
        node->room = new roomBox(createRoom(node));
    }
    
}

//this will generate latex for demos: https://www.desmos.com/calculator/
std::string levelGenerator::visualization(int x, int y, int w, int h)
{   
    std::string desmos;
    desmos += std::to_string(x);
    desmos += "\\le x\\le";
    desmos += std::to_string(x+w);
    desmos += "\\left\\{";
    desmos +=  std::to_string(y);
    desmos += "\\le y\\le";
    desmos += std::to_string(y+h);
    desmos += "\\right\\}";
    
    return desmos;
}

//this will generate latex for demos: https://www.desmos.com/calculator/
std::string levelGenerator::createVisualization(nodeBSP* node)
{   
    int w = node->width;
    int h = node->height;
    int x = node->posX;
    int y = node->posY;
    
    return visualization(x,y,w,h);
}

//this will generate latex for demos: https://www.desmos.com/calculator/
std::string levelGenerator::createVisualization(roomBox* room)
{   
    int w = room->width;
    int h = room->height;
    int x = room->posX;
    int y = room->posY;

    return visualization(x,y,w,h);
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
    BSP bsp = createBSP(dungeonDepth);
    traverseBSP(&bsp, &bsp.root);
    std::cout << "recursion amount: " << bsp.recursionAmount << std::endl;
    std::cout << "nodes amount: " << bsp.nodesAmount << std::endl;
    std::cout << "rooms amount: " << bsp.roomsAmount << std::endl;
    std::cout << "bsp visualization: " << std::endl;
    std::cout << bsp.visulatizationBSP << std::endl;
    std::cout << "rooms visualization: " << std::endl;
    std::cout << bsp.visulatizationRooms << std::endl;

    return level();
}