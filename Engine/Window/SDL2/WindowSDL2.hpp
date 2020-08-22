#ifndef WINDOW_SDL2_H
#define WINDOW_SDL2_H


#include <SDL2/SDL.h>

#include "Window/Window.hpp"


class SDL2Window : public Window {
    private:
    
    SDL_Window *canvas;

    void* ctx;

    CanvasContext context_type;

    public:

    SDL2Window(const char* title, size_t width, size_t height);
    ~SDL2Window();

    void Swap();

    void SetContext(CanvasContext context);
    void SetVsync(bool useVsync);

};

#endif