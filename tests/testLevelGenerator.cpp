#include <gtest/gtest.h>
#include <string>
#include <string.h>
#include <sstream>
#include <thread>
#include <chrono>

#include "../include/levelGenerator.h"


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
        using levelGenerator::calculateLevelSize; 
        using levelGenerator::calculateDesiredRoomSize; 
        using levelGenerator::calculateRecursionsAmount; 
        using levelGenerator::splitNodeBSP; 
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


TEST(levelGeneratorSuite, testCalculateLevelSize)
{
    wait();
    testLevelGeneratorClass generator;


    for(int i = 1; i < 9; i++)
    {
        int levelSize = generator.calculateLevelSize(i);

        switch (i) 
        {
            case 1:
                ASSERT_EQ(levelSize, 53);
                break;
            case 2:
                ASSERT_EQ(levelSize, 56);
                break;
            case 3:
                ASSERT_EQ(levelSize, 59);
                break;
            case 4:
                ASSERT_EQ(levelSize, 62);
                break;
            case 5:
                ASSERT_EQ(levelSize, 65);
                break;
            case 6:
                ASSERT_EQ(levelSize, 68);
                break;
            case 7:
                ASSERT_EQ(levelSize, 71);
                break;
            case 8:
                ASSERT_EQ(levelSize, 74);
                break;
            case 9:
                ASSERT_EQ(levelSize, 77);
                break;
            case 10:
                ASSERT_EQ(levelSize, 80);
                break;
            default:
                std::cout << "iteration " << i << std::endl;
                throw std::runtime_error("error");
        }

    }
    
}

TEST(levelGeneratorSuite, testCalculateDesiredRoomSize)
{

    wait();
    testLevelGeneratorClass generator;


    for(int i = 1; i < 9; i++)
    {
        int roomSize = generator.calculateDesiredRoomSize(i);

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



TEST(levelGeneratorSuite, testSplitBSPSingle)
{
    testLevelGeneratorClass generator;

    int recursions = 1;
    int size = 50;
    levelGenerator::nodeBSP root = {recursions, 0, 0, 50, 50, nullptr, nullptr, nullptr};
    generator.splitNodeBSP(&root, size);

    ASSERT_TRUE(root.room != nullptr);
    ASSERT_NE(root.firstNode, nullptr);
    ASSERT_NE(root.secondNode, nullptr);

    ASSERT_TRUE(false);
}


TEST(levelGeneratorSuite, testSplitBSP)
{
    wait();

    testLevelGeneratorClass generator;


    // ┌────┬────┐
    // │    │    │
    // └────┴────┘
    // size = 1/2 level size
    //
    // TEST 1 RECURSIONS
    for(int i = 0; i < 1000; i++)
    {
        int recursions = 1;
        int size = 10;
        int levelSize = 50;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }


    //  ┌────┬────┬────┬────┐ 
    //  │    │    │    │    │
    //  └────┴────┴────┴────┘
    //   
    //  size = 1/4 level size
    //
    // TEST 2 RECURSIONS
    for(int i = 0; i < 1000; i++)
    {
        int recursions = 2;
        int size = 10;
        int levelSize = 50;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }

    //  ┌────┬────┬────┬────┬────┬────┬────┬────┐ 
    //  │    │    │    │    │    │    │    │    │
    //  └────┴────┴────┴────┴────┴────┴────┴────┘
    //  size = 1/8 level size
    //
    // TEST 3 RECURSIONS
    for(int i = 0; i < 1000; i++)
    {
        int recursions = 3;
        int size = 10;
        int levelSize = 50;
        levelGenerator::nodeBSP root = {recursions, 0, 0, levelSize, levelSize , nullptr, nullptr, nullptr};
        generator.splitNodeBSP(&root, size);

        ASSERT_TRUE(root.room == nullptr);
        ASSERT_FALSE(root.firstNode == nullptr);
        ASSERT_FALSE(root.secondNode == nullptr);
    }

    

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
