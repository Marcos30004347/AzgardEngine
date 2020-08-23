#include<iostream>
#include<assert.h>

#include "definitions.hpp"

#ifdef SDL2_IMP
#include<SDL2/SDL.h>
#endif


#include "PlatformManager.hpp"


PlatformManager* PlatformManager::gInstance = nullptr;

PlatformManager::PlatformManager() {}
PlatformManager::~PlatformManager() {}

PlatformManager* PlatformManager::GetSingletonPtr(void) {
    assert(PlatformManager::gInstance);
    return PlatformManager::gInstance;
}

PlatformManager& PlatformManager::GetSingleton(void) {
    assert(PlatformManager::gInstance);
    return *PlatformManager::gInstance;
}

void PlatformManager::StartUp() {
    std::cout << "starting up Platform manager" << std::endl;
    PlatformManager::gInstance = new PlatformManager();

    #ifdef SDL2_IMP
    SDL_Init(SDL_INIT_EVERYTHING);
    #endif
}

void PlatformManager::ShutDown() {
    std::cout << "shuting down Platform manager" << std::endl;

    #ifdef SDL2_IMP
    SDL_Quit();
    #endif

    delete PlatformManager::gInstance;
}

const char* PlatformManager::GetFileSystemSeparator() {
    #ifdef BROWSER_PLATFORM
    return "/";
    #endif

    #ifdef LINUX_PLATFORM
    return "/";
    #endif

    #ifdef MACOS_PLATFORM
    return "/";
    #endif

    #ifdef WINDOWS_PLATFORM
    return "\\";
    #endif
}

Platform PlatformManager::GetPlatformId() {

    #ifdef BROWSER_PLATFORM
    return BROWSER;
    #endif

    #ifdef LINUX_PLATFORM
    return LINUX;
    #endif

    #ifdef MACOS_PLATFORM
    return MACOS;
    #endif

    #ifdef WINDOWS_PLATFORM
    return WINDOWS;
    #endif
}