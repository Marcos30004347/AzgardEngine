#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "Renderer/Renderer.hpp"

class RendererManager {
    friend class Engine; 

    private:
    static RendererManager* gInstance;
    static Renderer* gRenderer;

    RendererManager();
    ~RendererManager();
    static void StartUp();
    static void ShutDown();

    public:

    static RendererManager& GetSingleton(void);
    static RendererManager* GetSingletonPtr(void);
    static Renderer* GetRendererPtr(void);
};

#endif