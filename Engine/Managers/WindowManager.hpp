#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "Window/Window.hpp"

class WindowManager {
    friend class Engine; 

    private:
    static WindowManager* gInstance;
    static Window* gMainWindow;

    WindowManager();
    ~WindowManager();

    static void StartUp(const char* title, size_t width, size_t height);
    static void ShutDown();

    public:

    static WindowManager& GetSingleton(void);
    static WindowManager* GetSingletonPtr(void);
    static void SetContext(WindowContext context);

    static void Swap();
    static void UseVsync(bool vsync);
    // Window* CreateWindow(const char* title, size_t width, size_t height);
};

#endif