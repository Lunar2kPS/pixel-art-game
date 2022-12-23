# HUGE THANKS to https://cmake.org/cmake/help/latest/guide/tutorial/A Basic Starting Point.html
cmake_minimum_required(VERSION 3.19)
project("PixelArtGame" VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable("${PROJECT_NAME}" "${SRC_FILES}")

configure_file (
    # NOTE: THIS MUST have a different file name/extension, so that when you use #include in C++ files, it grabs from the SUBSTITUTED .h file!
    "${PROJECT_SOURCE_DIR}/src/includes/GameVersion.in.h"
    "${PROJECT_BINARY_DIR}/includes/GameVersion.h"
)

# We need this for our C++ program to find the .h header files when building:
target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}/includes")



# This turns OFF building the GLFW tests, examples and documentation:
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# SEE: Note from https://www.glfw.org/docs/latest/build_guide.html#build_link_cmake_source
# This adds GLFW to the build process!
# This adds a "glfw" target.
add_subdirectory("libraries/glfw")

# This links GLFW to our executable!
target_link_libraries("${PROJECT_NAME}" PUBLIC glfw)

# We need this for our C++ program to find the .h header files when building:
target_include_directories("${PROJECT_NAME}" PUBLIC "libraries/glfw/include")



target_compile_options("${PROJECT_NAME}" PUBLIC "-Wall")
target_compile_options("${PROJECT_NAME}" PUBLIC "-Wno-trigraphs")
