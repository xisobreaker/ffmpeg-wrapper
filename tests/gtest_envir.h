#pragma once

#include <gtest/gtest.h>

class GTestEnvir : public testing::Environment
{
public:
    void SetUp() override;
    void TearDown() override;

public:
    static std::string tests_dir;
};