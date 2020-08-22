#include <assert.h>

#include "definitions.hpp"

#include "Botticelli.hpp"

#ifdef OPENGLES3_API
#include "OpenGLES3/BotticelliOpenGLES3.hpp"
#endif

Renderer* Botticelli::gRenderer = nullptr;

Botticelli::Botticelli(){}
Botticelli::~Botticelli(){}


void Botticelli::StartUp() {
    #ifdef __EMSCRIPTEN__
        GraphicAPI defaultApi = OPENGLES3;
    #elif __linux__
        GraphicAPI defaultApi = OPENGLES3;
    #elif _WIN32
        GraphicAPI defaultApi = OPENGLES3;
    #endif

    #ifdef OPENGLES3_API
    if(defaultApi == OPENGLES3) Botticelli::gRenderer = new BotticelliOpenGLES3();
    Botticelli::gRenderer->StartUp();
    #endif

}

void Botticelli::ShutDown() {
    Botticelli::gRenderer->ShutDown();
    delete Botticelli::gRenderer;
}

Renderer* Botticelli::GetRendererPtr() {
    assert(gRenderer && "Renderer API not initialized or not suported!");
    return Botticelli::gRenderer;
}

void Botticelli::SelectApi(GraphicAPI api) {
    if(api == OPENGLES3) {
        #ifdef OPENGLES3_API
        Botticelli::gRenderer = new BotticelliOpenGLES3();
        #else
        #error Renderer API selected is not suported!
        #endif
    } else {
        assert(0 && "Renderer API selected is not suported!");
    }
}
