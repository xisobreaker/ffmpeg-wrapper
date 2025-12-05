# ---------------------------------------------------------------------------------------
# Set sources
# ---------------------------------------------------------------------------------------
set(PROJECT_SOURCE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../src")

file(GLOB PROJECT_TOP_SOURCES ${PROJECT_SOURCE_DIRS}/*.cpp)

set(PROJECT_SOURCE_FILES
    ${PROJECT_TOP_SOURCES})
