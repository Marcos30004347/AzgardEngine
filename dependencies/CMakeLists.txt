cmake_minimum_required(VERSION 3.16)

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
add_subdirectory(glew)
add_subdirectory(sdl2)
add_subdirectory(harfbuzz)
add_subdirectory(freetype2)
endif()

add_subdirectory(text_tree)
add_subdirectory(vec-t)
add_subdirectory(glm)