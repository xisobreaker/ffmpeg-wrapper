#include "test_environment.h"

#include <boost/filesystem/operations.hpp>

boost::filesystem::path TestEnvironment::tests_dir_ = "";
boost::filesystem::path TestEnvironment::root_dir_  = "";
boost::filesystem::path TestEnvironment::tmp_dir_   = "";

void TestEnvironment::SetUp()
{
    tests_dir_ = boost::filesystem::path(TEST_SOURCE_DIR);
    root_dir_  = tests_dir_.parent_path();
    tmp_dir_   = boost::filesystem::temp_directory_path();
}

void TestEnvironment::TearDown()
{
}

const boost::filesystem::path &TestEnvironment::testsDir()
{
    return tests_dir_;
}

const boost::filesystem::path &TestEnvironment::rootDir()
{
    return root_dir_;
}

const boost::filesystem::path &TestEnvironment::tmpDir()
{
    return tmp_dir_;
}