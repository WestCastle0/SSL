#include <iostream>
#include <gtest/gtest.h>

#define USE_UNIT_TEST 1

int main(int argc, char** argv) 
{
#if USE_UNIT_TEST
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    return 1;
#endif
}
