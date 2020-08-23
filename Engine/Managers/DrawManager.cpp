#include<iostream>
#include<assert.h>

#include "definitions.hpp"

#include "DrawManager.hpp"


#ifdef OPENGLES3_API
#include "Renderer/DaVinci/OpenGLES3/RendererES3.hpp"
#endif

DrawManager* DrawManager::gInstance = nullptr;
Renderer* DrawManager::gRenderer = nullptr;
GraphicAPI DrawManager::currentGraphicApi = OPENGLES3;

DrawManager::DrawManager() {}
DrawManager::~DrawManager() {}

DrawManager* DrawManager::GetSingletonPtr(void) {
    assert(DrawManager::gInstance);
    return DrawManager::gInstance;
}

Renderer* DrawManager::GetRendererPtr(void) {
    assert(DrawManager::gRenderer);
    return DrawManager::gRenderer;
}

DrawManager& DrawManager::GetSingleton(void) {
    assert(DrawManager::gInstance);
    return *DrawManager::gInstance;
}

void DrawManager::StartUp() {
    std::cout << "starting up mesh manager" << std::endl;
    DrawManager::gInstance = new DrawManager();
    if(currentGraphicApi == GraphicAPI::OPENGLES3) {
        #ifdef OPENGLES3_API 
        gRenderer = new RendererES3();
        #elif
        assert(0 && "OpenGLES3 not suported");
        #endif
    }

    // Botticelli::StartUp();
    // DrawManager::gRenderer = Botticelli::GetRendererPtr();
}

void DrawManager::ShutDown() {
    std::cout << "shuting down mesh manager" << std::endl;
    delete DrawManager::gInstance;
}

void DrawManager::SwitchAPI(GraphicAPI api) {
    currentGraphicApi = api;

    if(currentGraphicApi == OPENGLES3) {
        #ifdef OPENGLES3_API 
        gRenderer = new RendererES3();
        #elif
        assert(0 && "OpenGLES3 not suported");
        #endif
    }
    // Botticelli::SelectApi(api);
}
