#include "gtest_envir.h"
#include <cstdlib>
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    testing::Environment *env = new GTestEnvir();
    testing::AddGlobalTestEnvironment(env);
    return RUN_ALL_TESTS();
}