#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include "Renderer/Renderer.hpp"

class DrawManager {
    friend class Engine; 

    private:
    static DrawManager* gInstance;

    static Renderer* gRenderer;

    static GraphicAPI currentGraphicApi;

    DrawManager();
    ~DrawManager();
    static void StartUp();
    static void ShutDown();

    public:

    static DrawManager& GetSingleton(void);
    static DrawManager* GetSingletonPtr(void);

    static Renderer* GetRendererPtr(void);
    static void SwitchAPI(GraphicAPI api);
};

#endif