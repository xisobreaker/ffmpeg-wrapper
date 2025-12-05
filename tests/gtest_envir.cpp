#include "gtest_envir.h"

#include <gtest/gtest.h>

std::string GTestEnvir::tests_dir = "";

void GTestEnvir::SetUp()
{
    tests_dir = testing::SrcDir() + "../../tests/";
}

void GTestEnvir::TearDown()
{
}