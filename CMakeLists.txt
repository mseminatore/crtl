cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(crtl VERSION 1.0)

# add the includes
include_directories(${PROJECT_SOURCE_DIR})

# add the library
add_library(crtl assert.c stdio.c string.c stdlib.c)

# add the executable
add_executable(crtl_test main.c)