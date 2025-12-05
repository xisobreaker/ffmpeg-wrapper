# ---------------------------------------------------------------------------------------
# Set headers
# ---------------------------------------------------------------------------------------
set(PROJECT_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include")

file(GLOB PROJECT_TOP_HEADERS ${PROJECT_INCLUDE_DIRS}/ffmpegcpp/*.h)

set(PROJECT_HEADER_FILES
    ${PROJECT_TOP_HEADERS})
