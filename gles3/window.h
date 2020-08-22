#ifndef OLYMPUS_SDL2_WINDOW_API_H
#define OLYMPUS_SDL2_WINDOW_API_H

#include <SDL2/SDL.h>

class SDL2_Window {
    private:
    SDL_Window *window;
    SDL_GLContext gl_context;
    unsigned int _width;
    unsigned int _height;
    public:
    SDL2_Window(const char* title, unsigned int height, unsigned int width);
    ~SDL2_Window();

    void swap();
    void useVsync(bool useVsync);
    void loop(void (*render)());

    inline unsigned int getHeight() { return this->_height; } 
    inline unsigned int getWidth() { return this->_width; } 
};

#endif