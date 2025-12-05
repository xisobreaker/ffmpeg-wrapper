cmake_minimum_required(VERSION 3.10...3.21)

# ---------------------------------------------------------------------------------------
# Start project
# ---------------------------------------------------------------------------------------
include(cmake/project_headers.cmake)
include(cmake/project_sources.cmake)

project(ffmpegcpp VERSION 0.0.1 LANGUAGES CXX)

# ---------------------------------------------------------------------------------------
# Set default environment variable
# ---------------------------------------------------------------------------------------
include(GNUInstallDirs)

# ---------------------------------------------------------------------------------------
# Set default build to release
# ---------------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()
message(STATUS "Build ${PROJECT_NAME}: ${PROJECT_VERSION} ${CMAKE_BUILD_TYPE}")

# ---------------------------------------------------------------------------------------
# Compiler config
# ---------------------------------------------------------------------------------------
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------------------
option(BUILD_SHARED_LIBS             "Build with shared libs"  ON)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Export compile commands" ON)
option(BUILD_EXAMPLES                "Build with examples"     ON)
option(BUILD_TESTING                 "Build tests"             ON)

# ---------------------------------------------------------------------------------------
# Set output directory
# ---------------------------------------------------------------------------------------
if (NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
endif()
if (NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
endif()
if (NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
endif()

# ---------------------------------------------------------------------------------------
# Find packages
# ---------------------------------------------------------------------------------------
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)
find_package(glog REQUIRED)

pkg_check_modules(FFMPEG REQUIRED 
    libavcodec 
    libavdevice 
    libavfilter 
    libavformat 
    libavutil 
    libswscale
)

include_directories(
    ${FFMPEG_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)

# generator version file
configure_file(
    "${PROJECT_SOURCE_DIR}/version.h.in" 
    "${PROJECT_SOURCE_DIR}/include/version.h")

# ---------------------------------------------------------------------------------------
# Static/Shared library
# ---------------------------------------------------------------------------------------
if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES})
else()
    add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    Threads::Threads
    glog::glog
    ${OpenCV_LIBRARIES}
    ${FFMPEG_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    VERSION ${PROJECT_VERSION} 
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

# ---------------------------------------------------------------------------------------
# Build examples
# ---------------------------------------------------------------------------------------
if(BUILD_EXAMPLES)
    message(STATUS "Generating examples")

    add_subdirectory(examples)
endif()

# ---------------------------------------------------------------------------------------
# Build tests
# ---------------------------------------------------------------------------------------
if(BUILD_TESTING)
    find_package(GTest QUIET)
    if(GTest_FOUND)
        message(STATUS "Generating tests")

        enable_testing()
        add_subdirectory(tests)
    endif()
endif()


# ---------------------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)
install(
    DIRECTORY ${PROJECT_INCLUDE_DIRS}/ffmpegcpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_SYSCONFDIR)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

# ---------------------------------------------------------------------------------------
# Configure uninstall target
# ---------------------------------------------------------------------------------------
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# ---------------------------------------------------------------------------------------
# Configure cppcheck target
# ---------------------------------------------------------------------------------------
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_cppcheck.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/make_cppcheck.cmake"
    IMMEDIATE @ONLY)

add_custom_target(cppcheck
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/make_cppcheck.cmake)