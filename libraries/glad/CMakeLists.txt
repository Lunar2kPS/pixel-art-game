cmake_minimum_required(VERSION 3.19)
project(glad VERSION 2.0.2 LANGUAGES C)

add_library("${PROJECT_NAME}" "src/gl.c")
target_include_directories("${PROJECT_NAME}" PUBLIC "include")
