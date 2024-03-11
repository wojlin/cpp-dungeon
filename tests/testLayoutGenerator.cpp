#include <gtest/gtest.h>
#include <string>
#include <string.h>
#include <sstream>
#include <thread>
#include <chrono>

#include "../include/levelGenerator.h"
#include "../include/levelManager.h"

class levelGeneratorSuite : public ::testing::Test {
protected:
    // Per-test-case set-up
    static void SetUpTestSuite() {
        // Code here will be called before the first test in the test suite
    }

    // Per-test-case tear-down
    static void TearDownTestSuite() {
        // Code here will be called after the last test in the test suite
    }

    // Per-test set-up
    void SetUp() override {
        // Code here will be called before each test
    }

    // Per-test tear-down
    void TearDown() override {
        // Code here will be called after each test
    }
};


class testLevelGeneratorClass : public levelGenerator 
{
    public:
        using levelGenerator::getRandomNumber;
        using levelGenerator::calculateMinimumNodeSize;  
        using levelGenerator::calculateLevelSize; 
        using levelGenerator::calculateDesiredNodeSize; 
        using levelGenerator::calculateRecursionsAmount; 
        using levelGenerator::splitNodeBSP; 
        using levelGenerator::createBSP;
        using levelGenerator::visualization;
        using levelGenerator::createVisualization;
        using levelGenerator::traverseBSP;
        using levelGenerator::createRoom; 
        using levelGenerator::createCorridor;
};


void wait()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST(levelGeneratorSuite, testRandomNumber)
{
    wait();
    testLevelGeneratorClass generator;

    //tc 1 : test diffrent values
    for(int i = -1000; i < 1000; i++)
    {
        int min = i;
        int max = i + 100;
        int number = generator.getRandomNumber(min, max);

        if(number < min || number > max)
        {
            std::stringstream ss;
            ss <<  min << " < " << number << " < " << max << std::endl;
            std::cout << ss.str();
        }
        
        ASSERT_GE(number, min);
        ASSERT_LE(number, max);
    }

    //tc 2 : test same value
    for(int i = -1000; i < 1000; i++)
    {
        int number = generator.getRandomNumber(i, i);


        if(number > i || number < i)
        {
            std::stringstream ss;
            ss <<  i << " = " << number << " = " << i << std::endl;
            std::cout << ss.str();
        }
        

        ASSERT_EQ(i, number);
    }

    //tc 3 : test wrong values
    for(int i = -1000; i < 1000; i++)
    {
        int min = i;
        int max = i -100;
        ASSERT_THROW(generator.getRandomNumber(min, max), std::runtime_error);
    }
}


TEST(levelGeneratorSuite, testCalculateMinimumNodeSize)
{
    wait();
    testLevelGeneratorClass generator;


    for(int i = 1; i < 6; i++)
    {
        int nodeSize = generator.calculateMinimumNodeSize(i, 10);

        switch (i) 
        {
            case 1:
                ASSERT_EQ(nodeSize, 20);
                break;
            case 2:
                ASSERT_EQ(nodeSize, 40);
                break;
            case 3:
                ASSERT_EQ(nodeSize, 80);
                break;
            case 4:
                ASSERT_EQ(nodeSize, 160);
                break;
            case 5:
                ASSERT_EQ(nodeSize, 320);
                break;
            case 6:
                ASSERT_EQ(nodeSize, 640);
                break;
            case 7:
                ASSERT_EQ(nodeSize, 1280);
                break;
            default:
                std::cout << "iteration " << i << std::endl;
                throw std::runtime_error("error");
        }
    }
}


TEST(levelGeneratorSuite, testCalculateLevelSize)
{
    wait();
    testLevelGeneratorClass generator;


    for(int i = 1; i < 6; i++)
    {
        int levelSize = generator.calculateLevelSize(i, 10);

        switch (i) 
        {
            case 1:
                ASSERT_GE(levelSize, 20);
                ASSERT_LE(levelSize, 20+(2*i*10));
                break;
            case 2:
                ASSERT_GE(levelSize, 40);
                ASSERT_LE(levelSize, 40+(2*i*10));
                break;
            case 3:
                ASSERT_GE(levelSize, 80);
                ASSERT_LE(levelSize, 80+(2*i*10));
                break;
            case 4:
                ASSERT_GE(levelSize, 160);
                ASSERT_LE(levelSize, 160+(2*i*10));
                break;
            case 5:
                ASSERT_GE(levelSize, 320);
                ASSERT_LE(levelSize, 320+(2*i*10));
                break;
            case 6:
                ASSERT_GE(levelSize, 640);
                ASSERT_LE(levelSize, 640+(2*i*10));
                break;
            case 7:
                ASSERT_GE(levelSize, 1280);
                ASSERT_LE(levelSize, 1280+(2*i*10));
                break;
            default:
                std::cout << "iteration " << i << std::endl;
                throw std::runtime_error("error");
        }

    }
    
}

TEST(levelGeneratorSuite, testCalculateDesiredNodeSize)
{

    wait();
    testLevelGeneratorClass generator;


    for(int i = 1; i < 9; i++)
    {
        int roomSize = generator.calculateDesiredNodeSize(i);

        switch (i) 
        {
            case 1:
                ASSERT_EQ(roomSize, 10);
                break;
            case 2:
                ASSERT_EQ(roomSize, 11);
                break;
            case 3:
                ASSERT_EQ(roomSize, 11);
                break;
            case 4:
                ASSERT_EQ(roomSize, 11);
                break;
            case 5:
                ASSERT_EQ(roomSize, 12);
                break;
            case 6:
                ASSERT_EQ(roomSize, 12);
                break;
            case 7:
                ASSERT_EQ(roomSize, 12);
                break;
            case 8:
                ASSERT_EQ(roomSize, 13);
                break;
            case 9:
                ASSERT_EQ(roomSize, 13);
                break;
            case 10:
                ASSERT_EQ(roomSize, 13);
                break;
            default:
                std::cout << "iteration " << i << std::endl;
                throw std::runtime_error("error");
        }

    }
}

TEST(levelGeneratorSuite, testCalculateRecursionsAmount)
{
    wait();
    testLevelGeneratorClass generator;

    for( int x = 0; x < 1000; x++)
    {
        for(int i = 1; i < 9; i++)
        {
            int recursions = generator.calculateRecursionsAmount(i);

            switch (i) 
            {
                case 1:
                    ASSERT_GE(recursions, 2);
                    ASSERT_LE(recursions, 3);
                    break;
                case 2:
                    ASSERT_GE(recursions, 2);
                    ASSERT_LE(recursions, 3);
                    break;
                case 3:
                    ASSERT_GE(recursions, 2);
                    ASSERT_LE(recursions, 4);
                    break;
                case 4:
                    ASSERT_GE(recursions, 2);
                    ASSERT_LE(recursions, 4);
                    break;
                case 5:
                    ASSERT_GE(recursions, 3);
                    ASSERT_LE(recursions, 4);
                    break;
                case 6:
                    ASSERT_GE(recursions, 3);
                    ASSERT_LE(recursions, 5);
                    break;
                case 7:
                    ASSERT_GE(recursions, 3);
                    ASSERT_LE(recursions, 5);
                    break;
                case 8:
                    ASSERT_GE(recursions, 3);
                    ASSERT_LE(recursions, 5);
                    break;
                case 9:
                    ASSERT_GE(recursions, 3);
                    ASSERT_LE(recursions, 5);
                    break;
                case 10:
                    ASSERT_GE(recursions, 3);
                    ASSERT_LE(recursions, 6);
                    break;
                default:
                    std::cout << "iteration " << i << std::endl;
                    throw std::runtime_error("error");
            }

        }
    }
}

TEST(levelGeneratorSuite, testSplitBSP_fail)
{
    wait();

    testLevelGeneratorClass generator;

    for(int i = 0; i < 10000; i++)
    {
        int recursions = 1;
        int levelSize = 20;
        int size = generator.getRandomNumber(levelSize, levelSize + 50);
        levelGenerator::nodeBSP node = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        EXPECT_THROW(generator.splitNodeBSP(&node, size), std::runtime_error);
    }

}

TEST(levelGeneratorSuite, testSplitBSP_normal)
{
    wait();
    testLevelGeneratorClass generator;

    std::cout << "testing level 1 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 1;
        int size = 10;
        int levelSize = 20*3;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 1 recursion passed!" << std::endl;

    std::cout << "testing level 2 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 2;
        int size = 10;
        int levelSize = 40*3;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 2 recursion passed!" << std::endl;

    std::cout << "testing level 3 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 3;
        int size = 10;
        int levelSize = 80*3;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 3 recursion passed!" << std::endl;

    std::cout << "testing level 4 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 4;
        int size = 10;
        int levelSize = 160*3;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 4 recursion passed!" << std::endl;

    std::cout << "testing level 5 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 5;
        int size = 10;
        int levelSize = 320*3;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 5 recursion passed!" << std::endl;
    

    std::cout << "testing level 6 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 6;
        int size = 10;
        int levelSize = 640*3;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 6 recursion passed!" << std::endl;
}


TEST(levelGeneratorSuite, testSplitBSP_edge)
{
    wait();

    testLevelGeneratorClass generator;


    // ┌────┬────┐
    // │    │    │
    // └────┴────┘
    // size = 1/2 level size
    //
    // TEST 1 RECURSIONS
    std::cout << "testing level 1 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 1;
        int size = 10;
        int levelSize = 20;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 1 recursion passed!" << std::endl;

    //  ┌────┬────┬────┬────┐ 
    //  │    │    │    │    │
    //  └────┴────┴────┴────┘
    //   
    //  size = 1/4 level size
    //
    // TEST 2 RECURSIONS
    std::cout << "testing level 2 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 2;
        int size = 10;
        int levelSize = 40;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 2 recursion passed!" << std::endl;

    //  ┌────┬────┬────┬────┬────┬────┬────┬────┐ 
    //  │    │    │    │    │    │    │    │    │
    //  └────┴────┴────┴────┴────┴────┴────┴────┘
    //  size = 1/8 level size
    //
    // TEST 3 RECURSIONS
    std::cout << "testing level 3 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 3;
        int size = 10;
        int levelSize = 80;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 3 recursion passed!" << std::endl;


    //  ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐ 
    //  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │  │
    //  └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘
    //  size = 1/16 level size
    //
    // TEST 4 RECURSIONS
    std::cout << "testing level 4 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 4;
        int size = 10;
        int levelSize = 160;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 4 recursion passed!" << std::endl;


    //  ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐ 
    //  │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
    //  └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘
    //  size = 1/32 level size
    //
    // TEST 5 RECURSIONS
    std::cout << "testing level 5 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 5;
        int size = 10;
        int levelSize = 320;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 5 recursion passed!" << std::endl;
    

    //  drawing to complex xD
    //  size = 1/64 level size
    //
    // TEST 6 RECURSIONS
    std::cout << "testing level 6 recursion..." << std::endl;
    for(int i = 0; i < 10000; i++)
    {
        int recursions = 6;
        int size = 10;
        int levelSize = 640;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }
    std::cout << "level 6 recursion passed!" << std::endl;

}

TEST(levelGeneratorSuite, testCreateBSP)
{
    wait();

    testLevelGeneratorClass generator;

    for(int x = 0; x < 100; x++)
    {
        for(int i = 1; i < 35; i++)
        {
            levelGenerator::BSP bsp = generator.createBSP(i);
        }
    } 
}

TEST(levelGeneratorSuite, testVisalization)
{
    wait();

    testLevelGeneratorClass generator;
    std::string received = generator.visualization(100, 50, 30, 40);
    std::string expected = "100\\le x\\le130\\left\\{50\\le y\\le90\\right\\}";

    ASSERT_EQ(received, expected);
}


TEST(levelGeneratorSuite, testCreateVisalizationNode)
{
    wait();

    testLevelGeneratorClass generator;

    levelGenerator::nodeBSP node = {0, 0, 0, 50, 100, nullptr, nullptr, nullptr};

    std::string received = generator.createVisualization(&node);
    std::string expected = "0\\le x\\le50\\left\\{0\\le y\\le100\\right\\}";

    ASSERT_EQ(received, expected);

}

TEST(levelGeneratorSuite, testCreateVisalizationRoom)
{
    wait();

    testLevelGeneratorClass generator;

    levelGenerator::roomBox room = {0, 0, 50, 100};

    std::string received = generator.createVisualization(&room);
    std::string expected = "0\\le x\\le50\\left\\{0\\le y\\le100\\right\\}";

    ASSERT_EQ(received, expected);
}


TEST(levelGeneratorSuite, testTraverseBSP)
{
    wait();

    testLevelGeneratorClass generator;

    for(int x = 0; x < 100; x++)
    {
        for(int i = 1; i < 35; i++)
        {
            levelGenerator::BSP bsp = generator.createBSP(i);
            generator.traverseBSP(&bsp, &bsp.root);
            ASSERT_GE(bsp.roomsAmount, 0);
            if(bsp.roomsAmount % 2 != 0)
            {
                std::cerr << "dungeon depth: "<< i <<", recusions amount: "<< bsp.recursionAmount<<", nodes amount: "<< bsp.nodesAmount<<", rooms amount:" << bsp.roomsAmount << std::endl;
            }
            ASSERT_TRUE(bsp.roomsAmount % 2 == 0);

        }
    } 
}

TEST(levelGeneratorSuite, testCreateRoom)
{
    wait();

    testLevelGeneratorClass generator;

    for(int x = 0; x < 1000; x++)
    {   
        int width = 50;
        int height = 100;
        levelGenerator::nodeBSP node = {0, 0, 0, width, height, nullptr, nullptr, nullptr};
        levelGenerator::roomBox room = generator.createRoom(&node);
        ASSERT_GT(room.width, 0);
        ASSERT_GT(room.height, 0);
        ASSERT_LE(room.width, width);
        ASSERT_LE(room.height, height);

        ASSERT_GE(room.posX, node.posX);
        ASSERT_GE(room.posY, node.posY);

        ASSERT_LE(room.posX - room.width, node.posX + node.width);
        ASSERT_LE(room.posY - room.height, node.posY + node.height);
    } 
}

TEST(levelGeneratorSuite, testCreateCorridors)
{
    wait();
    testLevelGeneratorClass generator;

    int width = 10;
    int height = 10;
    int room1X;
    int room1Y;
    int room2X;
    int room2Y;

    levelGenerator::roomBox room1;
    levelGenerator::roomBox room2;
    levelGenerator::nodeBSP node1;
    levelGenerator::nodeBSP node2;
    levelGenerator::nodeBSP root;
    std::vector<levelGenerator::roomBox*> rooms;
    levelGenerator::BSP bsp;
    levelGenerator::corridorLine corridor;

    //test horizontal
    room1X = 0;
    room1Y = 0;
    room2X = 20;
    room2Y = 0;
    room1 = {room1X, room1Y, width, height};
    room2 = {room2X, room2Y, width, height};
    node1 = {0, 0, 0, 10, 10, nullptr, nullptr, &room1};
    node2 = {0, 20, 0, 10, 10, nullptr, nullptr, &room2};
    root = {1, 0, 0, 30, 30, &node1, &node2, nullptr};
    rooms = {&room1, &room2};
    bsp = {root, "", "", "", 1, 3, 2, 0, rooms};
    corridor = generator.createCorridor(&root);

    ASSERT_EQ(corridor.startX, room1X + width);
    ASSERT_EQ(corridor.endX, room2X);
    ASSERT_EQ(corridor.startY, corridor.endY);


    //test vertical
    room1X = 0;
    room1Y = 0;
    room2X = 0;
    room2Y = 20;
    room1 = {room1X, room1Y, width, height};
    room2 = {room2X, room2Y, width, height};
    node1 = {0, 0, 0, 10, 10, nullptr, nullptr, &room1};
    node2 = {0, 0, 20, 10, 10, nullptr, nullptr, &room2};
    root = {1, 0, 0, 30, 30, &node1, &node2, nullptr};
    rooms = {&room1, &room2};
    bsp = {root, "", "", "", 1, 3, 2, 0, rooms};
    corridor = generator.createCorridor(&root);

    ASSERT_EQ(corridor.endY, room1Y + height);
    ASSERT_EQ(corridor.startY, room2Y);
    ASSERT_EQ(corridor.startX, corridor.endX);


    //test bend 1
    room1X = 0;
    room1Y = 20;
    room2X = 20;
    room2Y = 0;
    room1 = {room1X, room1Y, width, height};
    room2 = {room2X, room2Y, width, height};
    node1 = {0, 0, 0, 15, 30, nullptr, nullptr, &room1};
    node2 = {0, 15, 0, 15, 30, nullptr, nullptr, &room2};
    root = {1, 0, 0, 30, 30, &node1, &node2, nullptr};
    rooms = {&room2, &room1};
    bsp = {root, "", "", "", 1, 3, 2, 0, rooms};
    corridor = generator.createCorridor(&root);

    ASSERT_EQ(corridor.startY, room1Y);
    ASSERT_EQ(corridor.endX, room2X);

    //test bend 2
    room1X = 0;
    room1Y = 0;
    room2X = 20;
    room2Y = 20;
    room1 = {room1X, room1Y, width, height};
    room2 = {room2X, room2Y, width, height};
    node1 = {0, 0, 0, 15, 30, nullptr, nullptr, &room1};
    node2 = {0, 15, 0, 15, 30, nullptr, nullptr, &room2};
    root = {1, 0, 0, 30, 30, &node1, &node2, nullptr};
    rooms = {&room2, &room1};
    bsp = {root, "", "", "", 1, 3, 2, 0, rooms};
    corridor = generator.createCorridor(&root);

    ASSERT_EQ(corridor.startY, room1Y + room1.height);
    ASSERT_EQ(corridor.endX, room2X);


    //test bend 3
    room1X = 20;
    room1Y = 0;
    room2X = 0;
    room2Y = 20;
    room1 = {room1X, room1Y, width, height};
    room2 = {room2X, room2Y, width, height};
    node1 = {0, 0, 0, 15, 30, nullptr, nullptr, &room1};
    node2 = {0, 15, 0, 15, 30, nullptr, nullptr, &room2};
    root = {1, 0, 0, 30, 30, &node1, &node2, nullptr};
    rooms = {&room2, &room1};
    bsp = {root, "", "", "", 1, 3, 2, 0, rooms};
    corridor = generator.createCorridor(&root);

    ASSERT_EQ(corridor.startY, room1Y + room1.height);
    ASSERT_EQ(corridor.endX, room2X + room2.width);


    //test bend 4
    room1X = 20;
    room1Y = 20;
    room2X = 0;
    room2Y = 0;
    room1 = {room1X, room1Y, width, height};
    room2 = {room2X, room2Y, width, height};
    node1 = {0, 0, 0, 15, 30, nullptr, nullptr, &room1};
    node2 = {0, 15, 0, 15, 30, nullptr, nullptr, &room2};
    root = {1, 0, 0, 30, 30, &node1, &node2, nullptr};
    rooms = {&room2, &room1};
    bsp = {root, "", "", "", 1, 3, 2, 0, rooms};
    corridor = generator.createCorridor(&root);

    ASSERT_EQ(corridor.startY, room1Y);
    ASSERT_EQ(corridor.endX, room2X + room2.width);
    


}

TEST(levelGeneratorSuite, testCreateLevel)
{
    wait();

    for(int x = 0; x < 10; x++)
    {   
        for(int i = 1; i < 35; i++)
        {   
            levelGenerator generator;
            generator.createLevel(i);
        }
    } 
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
