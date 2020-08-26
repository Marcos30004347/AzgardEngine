cmake_minimum_required(VERSION 3.10)


set(ENGINE_PROJECT_NAME AzgardEngine)

project(${ENGINE_PROJECT_NAME})



function(link_sdl2)
    if (NOT SDL2)
    find_package(SDL2 REQUIRED)
    endif()

    link_libraries(${SDL2_LIBRARIES})
    include_directories(${SDL2_INCLUDE_DIRS})
endfunction(link_sdl2)

function(link_opengl)
    set(OpenGL_GL_PREFERENCE "GLVND")
    find_package(OpenGL REQUIRED)

    if (NOT GLEW)
    find_package(GLEW REQUIRED)
    endif()

    link_libraries(${OPENGL_LIBRARIES})
    link_libraries(${GLEW_LIBRARIES})
    include_directories(${GLEW_INCLUDE_DIRS})
    include_directories(${OPENGL_INCLUDE_DIRS})
endfunction(link_opengl)

function(link_harfbuzz)
    if (NOT HarfBuzz)
    find_package(HarfBuzz CONFIG REQUIRED)
    endif()
    link_libraries(${HARFBUZZ_LIBRARY})
    include_directories(${HarfBuzz_INCLUDE_DIR})
endfunction(link_harfbuzz)

function(link_freetype)
    if (NOT Freetype)
    find_package(Freetype CONFIG REQUIRED)
    endif()

    link_libraries(${FREETYPE_LIBRARIES})
    include_directories(${FREETYPE_INCLUDE_DIRS})
endfunction(link_freetype)

function(link_thread)
    # set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    link_libraries(Threads::Threads)
endfunction(link_thread)



function(link_glm)
    if(NOT glm)
    find_library(glm REQUIRED)
    endif()

    link_libraries(glm)
endfunction(link_glm)


function(link_tinygltf)
    if(NOT tinygltf)
    find_library(tinygltf REQUIRED)
    endif()

    link_libraries(tinygltf)
endfunction(link_tinygltf)

function(link_rapidjson)
    if(NOT RapidJSON)
    find_package(RapidJSON REQUIRED)
    endif()

    link_libraries(rapidjson)
endfunction(link_rapidjson)

function(link_tinyobjloader)
    if(NOT tinyobjloader)
    find_library(tinyobjloader REQUIRED)
    endif()

    link_libraries(tinyobjloader)
endfunction(link_tinyobjloader)

function(link_objwriter)
    # if(NOT objwriter)
    # find_package(objwriter CONFIG REQUIRED)
    # endif()

    link_libraries(objwriter)
endfunction(link_objwriter)


#Link platform specific libraries
if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
#Compiling for browser

set(USE_FLAGS "${USE_FLAGS} -o3")
set(USE_FLAGS "${USE_FLAGS} -std=c++11")
set(USE_FLAGS "${USE_FLAGS} -s WASM=1")
set(USE_FLAGS "${USE_FLAGS} -s FULL_ES3=1")
set(USE_FLAGS "${USE_FLAGS} -s USE_GLFW=3")
set(USE_FLAGS "${USE_FLAGS} -s USE_WEBGL2=1")
set(USE_FLAGS "${USE_FLAGS} -s USE_SDL=2")
set(USE_FLAGS "${USE_FLAGS} -s USE_HARFBUZZ=1")
set(USE_FLAGS "${USE_FLAGS} -s USE_FREETYPE=1")
set(USE_FLAGS "${USE_FLAGS} -s USE_PTHREADS=1")
set(USE_FLAGS "${USE_FLAGS} -s PTHREAD_POOL_SIZE=8")
set(USE_FLAGS "${USE_FLAGS} -s ALLOW_MEMORY_GROWTH=1")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
set(CMAKE_EXECUTABLE_SUFFIX .js)

link_glm()
link_tinygltf()
link_objwriter()
link_tinyobjloader()


elseif(APPLE)
#Compiling for macos

link_sdl2()
link_opengl()
link_harfbuzz()
link_freetype()
link_thread()
link_glm()
link_tinygltf()
link_rapidjson()
link_tinyobjloader()
link_objwriter()

elseif (LINUX OR UNIX)
#Compiling for Linux/Unix

link_sdl2()
link_opengl()
link_harfbuzz()
link_freetype()
link_thread()
link_glm()
link_tinygltf()
link_rapidjson()
link_objwriter()

elseif(MSVC)
#Compiling for Windows

link_directories(${CMAKE_SOURCE_DIR}/lib)

link_sdl2()
link_opengl()
link_harfbuzz()
link_freetype()
link_thread()
link_glm()
link_tinygltf()
link_rapidjson()
link_objwriter()

endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Window)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Renderer)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Managers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/DataStructures)


add_library(
    ${ENGINE_PROJECT_NAME}

    DataStructures/Identifier.cpp

    Managers/Engine.cpp
    Managers/MeshManager.cpp
    Managers/PlatformManager.cpp
    Managers/FileManager.cpp
    Managers/LogManager.cpp
    Managers/JobManager.cpp
    Managers/EventManager.cpp
    Managers/WindowManager.cpp
    Managers/DrawManager.cpp
    Managers/SceneManager.cpp

    FileFormats/Gltf2/Parser.cpp
    FileFormats/Obj/Parser.cpp
    FileFormats/Base64.cpp

    Renderer/DaVinci/OpenGLES3/RendererES3.cpp

    Renderer/DaVinci/OpenGLES3/Material/ShaderES3.cpp
    Renderer/DaVinci/OpenGLES3/Material/MaterialES3.cpp
    Renderer/DaVinci/OpenGLES3/Material/MaterialCollectionES3.cpp

    Renderer/DaVinci/OpenGLES3/Mesh/MeshES3.cpp
    Renderer/DaVinci/OpenGLES3/Mesh/ModelES3.cpp
    Renderer/DaVinci/OpenGLES3/Mesh/ModelCollectionES3.cpp

    Renderer/DaVinci/OpenGLES3/Camera/CameraES3.cpp
    Renderer/DaVinci/OpenGLES3/Camera/CameraCollectionES3.cpp

    Window/SDL2/WindowSDL2.cpp
)

target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${HarfBuzz_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS})
target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

