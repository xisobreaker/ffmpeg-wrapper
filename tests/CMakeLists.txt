file(GLOB_RECURSE TEST_SOURCE_FILES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/unit/*.cpp")

include_directories(${CMAKE_CURRENT_LIST_DIR}/unit)

find_package(Boost REQUIRED COMPONENTS filesystem)

# 编译测试可执行文件
add_executable(tests ${TEST_SOURCE_FILES})

# add compile definitions
target_compile_definitions(tests 
    PRIVATE 
        TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(tests
    SYSTEM PRIVATE
        ${GTEST_INCLUDE_DIRS})

# 链接测试可执行文件所需的库
target_link_libraries(tests
    PRIVATE
        ${GTEST_LIBRARIES}
        Boost::filesystem
        avkit)

# discover tests
gtest_discover_tests(tests)