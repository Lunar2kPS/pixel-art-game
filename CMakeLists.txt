# HUGE THANKS to https://cmake.org/cmake/help/latest/guide/tutorial/A Basic Starting Point.html
cmake_minimum_required(VERSION 3.19)
project("PixelArtGame")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable("${PROJECT_NAME}" "${SRC_FILES}")
target_compile_options("${PROJECT_NAME}" PUBLIC "-Wall")
target_compile_options("${PROJECT_NAME}" PUBLIC "-Wno-trigraphs")
