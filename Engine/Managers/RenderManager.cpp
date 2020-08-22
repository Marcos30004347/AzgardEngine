#include<iostream>
#include<assert.h>

#include "RenderManager.hpp"
#include "Renderer/Botticelli/Botticelli.hpp"


RendererManager* RendererManager::gInstance = nullptr;
Renderer* RendererManager::gRenderer = nullptr;

RendererManager::RendererManager() {}
RendererManager::~RendererManager() {}

RendererManager* RendererManager::GetSingletonPtr(void) {
    assert(RendererManager::gInstance);
    return RendererManager::gInstance;
}

Renderer* RendererManager::GetRendererPtr(void) {
    assert(RendererManager::gRenderer);
    return RendererManager::gRenderer;
}

RendererManager& RendererManager::GetSingleton(void) {
    assert(RendererManager::gInstance);
    return *RendererManager::gInstance;
}

void RendererManager::StartUp() {
    std::cout << "starting up mesh manager" << std::endl;
    RendererManager::gInstance = new RendererManager();

    Botticelli::StartUp();
    RendererManager::gRenderer = Botticelli::GetRendererPtr();
}

void RendererManager::ShutDown() {
    std::cout << "shuting down mesh manager" << std::endl;
    delete RendererManager::gInstance;
}