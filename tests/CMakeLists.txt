include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/src)

set(TEST_UNITCASE 
    test_demuxer.cpp
)

set(TEST_SOURCE_FILES   tests.cpp
                        gtest_envir.cpp
                        ${TEST_UNITCASE})

add_executable(tests ${TEST_SOURCE_FILES})
target_link_libraries(tests ${GTEST_LIBRARIES})
target_link_libraries(tests ffmpegcpp)
gtest_discover_tests(tests)