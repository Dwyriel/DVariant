cmake_minimum_required(VERSION 3.24)
project(DVariant)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(DVariant SHARED DVariant.cpp main.cpp)
