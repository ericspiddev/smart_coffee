# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)
#include the cmake from esp-idf so we can build
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
#names the project
project(smartCoffee)
