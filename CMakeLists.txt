cmake_minimum_required(VERSION 3.15)

project(DVariant VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(DVariant SHARED DVariant.cpp)

