#ifndef SURFACE_MANAGER_H
#define SURFACE_MANAGER_H

#include "Window/Window.hpp"

class WindowManager {
    friend class Engine; 

    private:
    static WindowManager* gInstance;

    WindowManager();
    ~WindowManager();

    static void StartUp();
    static void ShutDown();

    public:

    static WindowManager& GetSingleton(void);
    static WindowManager* GetSingletonPtr(void);

    Window* CreateWindow(const char* title, size_t width, size_t height);
};

#endif