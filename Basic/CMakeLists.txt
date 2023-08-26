cmake_minimum_required(VERSION 3.15)

project(DVariantBasic VERSION 0.4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(DVariantBasic INTERFACE DVariant.h)
