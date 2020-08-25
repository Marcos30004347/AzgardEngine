cmake_minimum_required(VERSION 3.10)

project(vec-t)

add_subdirectory(vendor)

include_directories(include)
include_directories(src)
link_libraries(CDT)

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    if (NOT Freetype)
    find_package(Freetype CONFIG REQUIRED)
    endif()

    link_libraries(${FREETYPE_LIBRARIES})
    include_directories(${FREETYPE_INCLUDE_DIRS})
else()

    add_compile_options("-s" "USE_FREETYPE=1")
    # include_directories(${FREETYPE_INCLUDE_DIRS})
endif()


add_library(
    vec-t
    src/bezier.cpp
    src/glyph.cpp
    src/shape.cpp
    src/stroke.cpp
    src/svg.cpp
    src/triangulation.cpp
)
    
target_include_directories(vec-t PUBLIC include)