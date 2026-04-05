/**
 * @file test_drivers_main.cpp
 * @brief Google Test runner entry point for all driver unit tests.
 */
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
