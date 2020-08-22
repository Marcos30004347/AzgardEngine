cmake_minimum_required(VERSION 3.10)

project(text_tree)

add_library(text_tree src/text_tree.cpp)

target_include_directories(text_tree PUBLIC src)


if(${ADD_TESTS}) 
enable_testing()
add_subdirectory(tests)
endif()