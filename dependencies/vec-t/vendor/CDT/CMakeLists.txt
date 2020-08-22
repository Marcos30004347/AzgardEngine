cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME CDT)

project(${PROJECT_NAME})

add_library(${PROJECT_NAME} CDT.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)