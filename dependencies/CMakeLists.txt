cmake_minimum_required(VERSION 3.16)

set(TINYOBJLOADER_BUILD_TEST_LOADER OFF)
set(TINYOBJLOADER_BUILD_OBJ_STICHER OFF)

set(TINYGLTF_BUILD_LOADER_EXAMPLE OFF)
set(TINYGLTF_BUILD_GL_EXAMPLES OFF)
set(TINYGLTF_BUILD_VALIDATOR_EXAMPLE OFF)

set(RAPIDJSON_BUILD_DOC OFF)
set(RAPIDJSON_BUILD_EXAMPLES OFF)
set(RAPIDJSON_BUILD_TESTS OFF)
set(RAPIDJSON_BUILD_THIRDPARTY_GTEST OFF)

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
add_subdirectory(glew)
add_subdirectory(sdl2)
add_subdirectory(harfbuzz)
add_subdirectory(freetype2)
endif()

add_subdirectory(tinygltf)
add_subdirectory(tinyobjloader)
add_subdirectory(objwriter)
add_subdirectory(glm)
add_subdirectory(rapidjson)

