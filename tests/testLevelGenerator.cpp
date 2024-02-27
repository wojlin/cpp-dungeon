#include <gtest/gtest.h>
#include <string>
#include <string.h>
#include <sstream>

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
};


TEST(levelGeneratorSuite, testRandomNumber)
{
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


TEST(levelGeneratorSuite, testAnother)
{
    ASSERT_EQ(1,1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
