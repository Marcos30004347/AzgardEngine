cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME sdl2_window)

project(${PROJECT_NAME})


if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    find_package(SDL2 REQUIRED)
    link_libraries(${SDL2_LIBRARIES})
else()
    set(USE_FLAGS "${USE_FLAGS} -o3")
    set(USE_FLAGS "${USE_FLAGS} -std=c++11")

    set(USE_FLAGS "${USE_FLAGS} -s WASM=1")
    set(USE_FLAGS "${USE_FLAGS} -s USE_SDL=2")
    set(USE_FLAGS "${USE_FLAGS} -s EXPORT_ALL=1")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .js)
endif()

include_directories(${CMAKE_SOURCE_DIR} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

add_library(
    ${PROJECT_NAME}
    BotticelliOpenGLES3.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC .)
