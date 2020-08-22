cmake_minimum_required(VERSION 3.10)


set(ENGINE_PROJECT_NAME engine)
project(${ENGINE_PROJECT_NAME})


function(link_sdl2)
    find_package(SDL2 REQUIRED)
    link_libraries(${SDL2_LIBRARIES})
    include_directories(${SDL2_INCLUDE_DIRS})
endfunction(link_sdl2)

function(link_opengl)
    set(OpenGL_GL_PREFERENCE GLVND)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
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
# set(USE_FLAGS "${USE_FLAGS} -s ALLOW_MEMORY_GROWTH=1")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
set(CMAKE_EXECUTABLE_SUFFIX .js)

elseif(APPLE)
#Compiling for macos

link_sdl2()
link_opengl()
link_harfbuzz()
link_freetype()
link_thread()

elseif (LINUX OR UNIX)
#Compiling for Linux/Unix

link_sdl2()
link_opengl()
link_harfbuzz()
link_freetype()
link_thread()

elseif(MSVC)
#Compiling for Windows

link_directories(${CMAKE_SOURCE_DIR}/lib)

link_sdl2()
link_opengl()
link_harfbuzz()
link_freetype()
link_thread()

endif()

include_directories(
    ${HarfBuzz_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
)


add_library(
    ${ENGINE_PROJECT_NAME}
    Managers/Engine.cpp
    Managers/MeshManager.cpp
    Managers/PlatformManager.cpp
    Managers/FileManager.cpp
    Managers/LogManager.cpp
    Managers/JobManager.cpp
    Managers/WindowManager.cpp
    Managers/EventManager.cpp

    Renderer/Botticelli/Botticelli.cpp
    Renderer/Botticelli/OpenGLES3/BotticelliOpenGLES3.cpp

    Window/SDL2/WindowSDL2.cpp
)

target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Managers)