#include "window.h"

SDL2_Window::SDL2_Window(const char* title, unsigned int height, unsigned int width) {
    SDL_Init(SDL_INIT_EVERYTHING);

    #if __EMSCRIPTEN__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

    #else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
    #endif

    SDL_GL_SetSwapInterval(1);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    this->gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(this->window, this->gl_context);
}

SDL2_Window::~SDL2_Window() {
    SDL_GL_DeleteContext(this->gl_context);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void SDL2_Window::swap() {
    SDL_GL_SwapWindow(this->window);
}

void SDL2_Window::loop(void (*render)()) {
    SDL_Event event;
    while(event.type != SDL_QUIT){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                SDL_Quit();
            }
        }
        render();
    }
}

void SDL2_Window::useVsync(bool useVsync) {
    SDL_GL_SetSwapInterval(useVsync ? 1 : -1);
}