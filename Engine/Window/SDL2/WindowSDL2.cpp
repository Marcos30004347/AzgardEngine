#include "WindowSDL2.hpp"
#include "definitions.hpp"
#include<iostream>

#ifdef SDL2_IMP


#ifdef OPENGLES3_API
#include<GL/glew.h>
#endif

SDL2Window::SDL2Window(const char* title, size_t width, size_t height) {

    #ifdef BROWSER_PLATFORM
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

    #ifdef OPENGLES3_API

    this->glContext = SDL_GL_CreateContext(canvas);

    if(!this->glContext) {
        std::cout << "Context not initialized!" << std::endl;
        throw;
    }

    if(glewInit() != GLEW_OK) {
        std::cout << "Glew not initialized!" << std::endl;
        throw;
    }

    #endif

    this->currentContextType = NullContext;
}

SDL2Window::~SDL2Window() {
    if(this->currentContextType == OpenGLES3Context && this->glContext)
        SDL_GL_DeleteContext(this->glContext);

    SDL_DestroyWindow(this->canvas);
}

void SDL2Window::Swap() {
    SDL_GL_SwapWindow(this->canvas);
}

void SDL2Window::SetVsync(bool useVsync) {
    SDL_GL_SetSwapInterval(useVsync ? 1 : -1);
}

void SDL2Window::SetContext(WindowContext context) {
    if(context == OpenGLES3Context) {
        #ifdef OPENGLES3_API

        SDL_GL_MakeCurrent(this->canvas, glContext);
    
        #elif
        #error OPENGLES3 NOT SUPORTED
        #endif

    }
}

#endif