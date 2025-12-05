#pragma once

#include <boost/filesystem.hpp>
#include <gtest/gtest.h>

class TestEnvironment : public testing::Environment
{
public:
    void SetUp() override;
    void TearDown() override;

    static const boost::filesystem::path &testsDir();
    static const boost::filesystem::path &rootDir();
    static const boost::filesystem::path &tmpDir();

private:
    static boost::filesystem::path tests_dir_;
    static boost::filesystem::path root_dir_;
    static boost::filesystem::path tmp_dir_;
};
