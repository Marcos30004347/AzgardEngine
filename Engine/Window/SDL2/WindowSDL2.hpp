#ifndef WINDOW_SDL2_H
#define WINDOW_SDL2_H


#include <SDL2/SDL.h>

#include "Window/Window.hpp"


class SDL2Window : public Window {
    private:
    
    SDL_Window *window;

    SDL_GLContext glContext;

    WindowContext currentContextType;

    public:

    SDL2Window(const char* title, size_t width, size_t height);
    ~SDL2Window();

    void Swap();

    void SetContext(WindowContext context);
    void SetVsync(bool useVsync);

};

#endif