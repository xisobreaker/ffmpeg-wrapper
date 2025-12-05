#include "test_environment.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    testing::Environment *env = new TestEnvironment();
    testing::AddGlobalTestEnvironment(env);
    return RUN_ALL_TESTS();
}