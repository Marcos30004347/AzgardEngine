
#include "WindowSDL2.hpp"

SDL2Window::SDL2Window(const char* title, size_t width, size_t height) {
    SDL_Init(SDL_INIT_EVERYTHING);

    #if BROWSER_PLATFORM
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

    this->canvas = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    this->context_type = NullContext;
}

SDL2Window::~SDL2Window() {
    if(this->context_type == OpenGLES3Context)
        SDL_GL_DeleteContext(this->ctx);

    SDL_DestroyWindow(this->canvas);
}

void SDL2Window::Swap() {
    SDL_GL_SwapWindow(this->canvas);
}

void SDL2Window::SetVsync(bool useVsync) {
    SDL_GL_SetSwapInterval(useVsync ? 1 : -1);
}

void SDL2Window::SetContext(CanvasContext context) {
    if(context == OpenGLES3Context) {
        this->ctx = SDL_GL_CreateContext(canvas);
        SDL_GL_MakeCurrent(this->canvas, ctx);
    }
}