cmake_minimum_required(VERSION 3.16)

project(objwriter)

add_definitions(-DCONF_NO_GL)

add_library(objwriter obj.c)

target_include_directories(objwriter PUBLIC .)