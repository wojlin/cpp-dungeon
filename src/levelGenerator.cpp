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
    
    bsp->nodesAmount += 1;
    bsp->visulatizationBSP += (createVisualization(node) + "\n");


    if(node->room != nullptr)
    {
        bsp->rooms.push_back(node->room);
        bsp->roomsAmount += 1;
        bsp->visulatizationRooms += (createVisualization(node->room) + "\n");
    }
    
    if(node->firstNode != nullptr)
    {
        traverseBSP(bsp, node->firstNode);
    }

    if(node->secondNode != nullptr)
    {
        traverseBSP(bsp, node->secondNode);
    }

    if(node->depth > 0)
    {
        createCorridor(bsp, node);  
    }
}


std::vector<roomBox*> levelGenerator::findRooms(nodeBSP* node)
{
    std::vector<roomBox*> rooms;

    if(node->room == nullptr)
    {
        nodeBSP* node1 = node->firstNode;
        nodeBSP* node2 = node->secondNode;    
        std::vector<roomBox*> foundRooms1 = findRooms(node1);
        std::vector<roomBox*> foundRooms2 = findRooms(node2);
        rooms.insert(rooms.end(), foundRooms1.begin(), foundRooms1.end());
        rooms.insert(rooms.end(), foundRooms2.begin(), foundRooms2.end());
    }
    else
    {
        rooms.push_back(node->room);
    }

    return rooms;
    
}

int levelGenerator::calculateMinimumNodeSize(int recursionsAmount, int desiredRoomSize)
{
    return static_cast<int>(pow(2, recursionsAmount)  * desiredRoomSize );
}

int levelGenerator::calculateDesiredNodeSize(int dungeonDepth)
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

int levelGenerator::calculateLevelSize(int recusionsAmount, int desiredNodeSize)
{   
    int min = 0;
    int max = 2 * recusionsAmount * desiredNodeSize;
    int randomAdd = getRandomNumber(min, max);
    return static_cast<int>((pow(2,recusionsAmount)*desiredNodeSize) + randomAdd);
}

BSP levelGenerator::createBSP(int dungeonDepth)
{
    
    //step 1: choose rooms amount
    //rooms amount = recursions^2
    int recursionsAmount = calculateRecursionsAmount(dungeonDepth);


    //step 2: choose node size
    int desiredNodeSize = calculateDesiredNodeSize(dungeonDepth);

    //step 3: choose level size
    int levelSize = calculateLevelSize(recursionsAmount, desiredNodeSize);

    
    
    nodeBSP root = {recursionsAmount,0, 0, levelSize, levelSize, nullptr, nullptr, nullptr};

    splitNodeBSP(&root, desiredNodeSize);
    
    BSP bsp;
    bsp.nodesAmount = 0;
    bsp.roomsAmount = 0;
    bsp.root = root;
    bsp.recursionAmount = recursionsAmount;
    
    return bsp;
}

void levelGenerator::splitNodeBSP(nodeBSP* node, int desiredNodeSize)
{
    int depth = node->depth;
    int minimumNodeSize = calculateMinimumNodeSize(depth, desiredNodeSize);


    std::string debugInfo;
    debugInfo += "depth:" + std::to_string(depth) + "\n";
    debugInfo += "desired node size:" + std::to_string(desiredNodeSize) + "\n";
    debugInfo += "node width:" + std::to_string(node->width) + "\n";
    debugInfo += "node height:" + std::to_string(node->height) + "\n";
    debugInfo += "min node size:" + std::to_string(minimumNodeSize) + "\n";

    if(depth > 0)
    {
        nodeBSP firstNode;
        nodeBSP secondNode;

        firstNode.firstNode = nullptr;
        firstNode.secondNode = nullptr;
        firstNode.room = nullptr;
        

        secondNode.firstNode = nullptr;
        secondNode.secondNode = nullptr;
        secondNode.room = nullptr;
        

        bool widthEnough = node->width - minimumNodeSize  >=0;
        bool heightEnough = node->height - minimumNodeSize  >=0;
        
        if(!widthEnough && !heightEnough)
        {
            throw std::runtime_error("error during splitting a BSP node. debug info below:\n" + debugInfo);
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

        //step 2: choose semi-random position
        if(static_cast<bool>(isVerticalSplit))
        {

            int min = minimumNodeSize / 2;
            int max = node->height - minimumNodeSize / 2;
            if(min > max)
            {
                throw std::range_error("not enough space to create node vertical. try increasing level size. debug info below:\n" + debugInfo);
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
            int min = minimumNodeSize / 2;
            int max = node->width - minimumNodeSize / 2;
            if(min > max)
            {
                throw std::range_error("not enough space to create node horizontal. try increasing level size. debug info below:\n" + debugInfo);
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

        splitNodeBSP(node->firstNode, desiredNodeSize);
        splitNodeBSP(node->secondNode, desiredNodeSize);
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

std::string levelGenerator::createVisualization(corridorLine* line)
{
    
    int x1 = line->startX;
    int y1 = line->startY;
    int x2 = line->endX;
    int y2 = line->endY;

    std::string desmos; 
    desmos += "\\left(\\left(1-t\\right)";
    desmos += std::to_string(x1);
    desmos += "+t";
    desmos += std::to_string(x2);
    desmos += ",\\left(1-t\\right)";
    desmos += std::to_string(y1);
    desmos += "+t";
    desmos += std::to_string(y2);
    desmos += "\\right)";

    return desmos;
}

roomBox levelGenerator::createRoom(nodeBSP* node)
{
    roomBox room;

    //step 1: choose room size
    int minRoomSize = 7;
    int width = getRandomNumber(minRoomSize, node->width);
    int height = getRandomNumber(minRoomSize, node->height);
    room.width = width;
    room.height = height;

    //step 2: choose room position

    int posX = getRandomNumber(node->posX, node->posX + node->width - width);
    int posY = getRandomNumber(node->posY, node->posY + node->height - height);
    room.posX = posX;
    room.posY = posY;

    return room;
}

void levelGenerator::createCorridor(BSP* bsp, nodeBSP* node)
{

    corridorLine line;

    if(node->depth == 1)
    {
        roomBox* room1 = node->firstNode->room;
        roomBox* room2 = node->secondNode->room;

        int xMin = std::max(room1->posX, room2->posX);
        int xMax = std::min(room1->posX+room1->width, room2->posX+room2->width);

        int yMin = std::max(room1->posY, room2->posY);
        int yMax = std::min(room1->posY+room1->height, room2->posY+room2->height);
        


        if(xMin < xMax)
        {
            int startX = getRandomNumber(xMin, xMax);
            int startY = yMin;
            int endX = startX;
            int endY = yMax ;
            line = {startX, startY, endX, endY};     
        }
        else if(yMin < yMax)
        {
            int startX = xMax;
            int startY = getRandomNumber(yMin, yMax); 
            int endX = xMin;
            int endY = startY;
            line = {startX, startY, endX, endY};
        }
        else
        {

            int startX = getRandomNumber(room1->posX, room1->posX+room1->width);
            int startY = room1->posY;
            int endX = room2->posX;
            int endY = getRandomNumber(room2->posY, room2->posY+room2->height);

            if(startY < endY)
            {
                startY+= room1->height;
            }

            if(startX > endX)
            {
                endX+= room2->width;
            }
            

            line = {startX, startY, endX, endY};
        }
    }
    else if(node->depth > 1)
    {
        //std::cout << "connecting nodes..." << std::endl;

        nodeBSP* node1 = node->firstNode;
        nodeBSP* node2 = node->secondNode;

        //step 1: determine if node is split vertical or horizontal
        bool isVerticalSplit = false;
        if(node1->posX == node2->posX)
        {
            isVerticalSplit = true;
        }

        //step 3: decide merge direction
        if(isVerticalSplit)
        {
            // top
            if(node1->posY > node2->posY)
            {
                node1 = node->secondNode;
                node2 = node->firstNode;
            }
            // else bottom
        }
        else
        {
            // right
            if(node1->posX > node2->posX)
            {
                node1 = node->secondNode;
                node2 = node->firstNode;
            }
            // else left
        }

        //step 2: find all rooms contained in that node
        std::vector<roomBox*> rooms1 = findRooms(node1);
        std::vector<roomBox*> rooms2 = findRooms(node2);


        //step 4: calculate merge spots
        struct mergeSpot
        {
            int posX1;
            int posY1;
            int posX2;
            int posY2;
        };


        std::vector<mergeSpot> spots;

        if(isVerticalSplit)
        {
            //std::cout << "merging vertical" << std::endl;

            std::map<int, int> bottomSide = {};
            std::map<int, int> topSide = {};

            //fill left side with coords
            for(int i = 0; i < rooms1.size(); i++)
            {
                for(int x = rooms1[i]->posX; x < rooms1[i]->posX+rooms1[i]->width; x++)
                {
                    if(bottomSide.find(x) == bottomSide.end() || rooms1[i]->posY > bottomSide[x]) 
                    {
                        bottomSide[x] = rooms1[i]->posY + rooms1[i]->height;
                    }
                }
            }

            //fill right side with coords
            for(int i = 0; i < rooms2.size(); i++)
            {
                for(int x = rooms2[i]->posX; x < rooms2[i]->posX+rooms2[i]->width; x++)
                {
                    if(topSide.find(x) == topSide.end() || rooms2[i]->posY < topSide[x]) 
                    {
                        topSide[x] = rooms2[i]->posY;
                    }
                }
            }

            //std::cout << "map1 len:" << bottomSide.size() << " map2 len:" << topSide.size() << std::endl;

            for (auto a = bottomSide.begin(); a != bottomSide.end(); a++) 
            {
                for (auto b = topSide.begin(); b != topSide.end(); b++) 
                {
                    if(a->first == b->first)
                    {   
                        mergeSpot spot = {a->first, a->second, b->first, b->second};
                        
                        //std::cout << "x1:" << a->first << ", y1:" << a->second << ", x2:" << b->first << "y2" << b->second << std::endl;
                        spots.push_back(spot);
                    }
                }
            }

            if(spots.size() == 0)
            {
                mergeSpot spot = {rooms1[0]->posX, rooms1[0]->posY, rooms2[0]->posX, rooms2[0]->posY};
                spots.push_back(spot);
            }

        }
        else
        {
            //std::cout << "merging horizontal" << std::endl;

            std::map<int, int> leftSide = {};
            std::map<int, int> rightSide = {};

            //fill left side with coords
            for(int i = 0; i < rooms1.size(); i++)
            {
                for(int y = rooms1[i]->posY; y < rooms1[i]->posY+rooms1[i]->height; y++)
                {
                    if(leftSide.find(y) == leftSide.end() || rooms1[i]->posX > leftSide[y]) 
                    {
                        leftSide[y] = rooms1[i]->posX + rooms1[i]->width;
                    }
                }
            }

            //fill right side with coords
            for(int i = 0; i < rooms2.size(); i++)
            {
                for(int y = rooms2[i]->posY; y < rooms2[i]->posY+rooms2[i]->height; y++)
                {
                    if(rightSide.find(y) == rightSide.end() || rooms2[i]->posX < rightSide[y]) 
                    {
                        rightSide[y] = rooms2[i]->posX;
                    }
                }
            }

            //std::cout << "map1 len:" << leftSide.size() << " map2 len:" << rightSide.size() << std::endl;

            for (auto a = leftSide.begin(); a != leftSide.end(); a++) 
            {
                for (auto b = rightSide.begin(); b != rightSide.end(); b++) 
                {
                    if(a->first == b->first)
                    {   
                        mergeSpot spot = {a->second, a->first, b->second, b->first};
                        
                        //std::cout << "x1:" << a->second << ", y1:" << a->first << ", x2:" << b->second << "y2" << b->first << std::endl;
                        spots.push_back(spot);
                    }
                }
            }


            if(spots.size() == 0)
            {
                mergeSpot spot = {rooms1[0]->posX, rooms1[0]->posY, rooms2[0]->posX, rooms2[0]->posY};
                spots.push_back(spot);
            }


        }
   

        //step 5: pick random merge spot
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, spots.size() - 1);
        int randomIndex = dis(gen);
        mergeSpot spot = spots[randomIndex];
        line = {spot.posX1, spot.posY1, spot.posX2, spot.posY2};      

    }


    
    //step 6: split corridor if neeeded
    if(line.startX != line.endX && line.startY != line.endY)
    {
        
         int diffX = std::abs(line.startX - line.endX);
        int diffY = std::abs(line.startY - line.endY);

        // Decide whether to start with a horizontal or vertical line
        corridorLine horizontalLine, verticalLine;
        if (diffX > diffY) { // Start with horizontal line
            horizontalLine = {line.startX, line.startY, line.endX, line.startY};
            verticalLine = {line.endX, line.startY, line.endX, line.endY};
        } else { // Start with vertical line
            horizontalLine = {line.startX, line.startY, line.startX, line.endY};
            verticalLine = {line.startX, line.endY, line.endX, line.endY};
        }

        bsp->corridors.push_back(new corridorLine(horizontalLine));
        bsp->corridors.push_back(new corridorLine(verticalLine));
        bsp->corridorsAmount +=2;
        bsp->visulatizationCorridors += (createVisualization(&horizontalLine) + "\n"); 
        bsp->visulatizationCorridors += (createVisualization(&verticalLine) + "\n"); 
    }
    else
    {
        bsp->corridors.push_back(new corridorLine(line));
        bsp->corridorsAmount +=1;
        bsp->visulatizationCorridors += (createVisualization(&line) + "\n"); 
    }



    
}

levelManager levelGenerator::createLevel(int dungeonDepth)
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
    std::cout << "corridors visualization: " << std::endl;
    std::cout << bsp.visulatizationCorridors << std::endl;

    return levelManager(dungeonDepth, bsp);
}