#include <iostream>
#include <assert.h>

#include "definitions.hpp"

#ifdef SDL2_IMP
#include "Window/SDL2/WindowSDL2.hpp"
#endif

#include "WindowManager.hpp"


WindowManager* WindowManager::gInstance = nullptr;

WindowManager::WindowManager() {}
WindowManager::~WindowManager() {}

WindowManager* WindowManager::GetSingletonPtr(void) {
    assert(WindowManager::gInstance);
    return WindowManager::gInstance;
}

WindowManager& WindowManager::GetSingleton(void) {
    assert(WindowManager::gInstance);
    return *WindowManager::gInstance;
}

void WindowManager::StartUp() {
    std::cout << "starting up mesh manager" << std::endl;
    WindowManager::gInstance = new WindowManager();
}

void WindowManager::ShutDown() {
    std::cout << "shuting down LOG manager" << std::endl;
    delete WindowManager::gInstance;
}

Window* WindowManager::CreateWindow(const char* title, size_t width, size_t height) {
    #ifdef SDL2_IMP
    return new SDL2Window(title, width, height);
    #endif
}