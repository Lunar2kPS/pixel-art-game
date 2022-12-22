# HUGE THANKS to https://cmake.org/cmake/help/latest/guide/tutorial/A Basic Starting Point.html
cmake_minimum_required(VERSION 3.19)
project("PixelArtGame" VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

configure_file (
    # NOTE: THIS MUST have a different file name/extension, so that when you use #include in C++ files, it grabs from the SUBSTITUTED .h file!
    "${PROJECT_SOURCE_DIR}/src/includes/GameVersion.in.h"
    "${PROJECT_BINARY_DIR}/includes/GameVersion.h"
)

add_executable("${PROJECT_NAME}" "${SRC_FILES}")

target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}/includes")

target_compile_options("${PROJECT_NAME}" PUBLIC "-Wall")
target_compile_options("${PROJECT_NAME}" PUBLIC "-Wno-trigraphs")
