#include <iostream>
#include <assert.h>

#include "definitions.hpp"

#ifdef SDL2_IMP
#include "Window/SDL2/WindowSDL2.hpp"
#endif

#include "WindowManager.hpp"


WindowManager* WindowManager::gInstance = nullptr;
Window* WindowManager::gMainWindow = nullptr;

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

void WindowManager::StartUp(const char* title, size_t width, size_t height) {
    std::cout << "starting up mesh manager" << std::endl;
    WindowManager::gInstance = new WindowManager();

    #ifdef SDL2_IMP
    gMainWindow = new SDL2Window(title, width, height);
    #endif

}

void WindowManager::ShutDown() {
    std::cout << "shuting down LOG manager" << std::endl;
    delete WindowManager::gInstance;
}

void WindowManager::SetContext(WindowContext context) {
    gMainWindow->SetContext(context);
}
// Window* WindowManager::CreateWindow(const char* title, size_t width, size_t height) {

// }

void WindowManager::Swap() {
    gMainWindow->Swap();
}

void WindowManager::UseVsync(bool vsync) {
    gMainWindow->SetVsync(vsync);
}