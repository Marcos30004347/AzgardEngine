#ifndef BOTTICELLI_H
#define BOTTICELLI_H

#include "Renderer/Renderer.hpp"

class Botticelli {
    private:
    static Renderer* gRenderer;

    Botticelli();
    ~Botticelli();

    public:
    static Renderer* GetRendererPtr();

    static void SelectApi(GraphicAPI api);
    static void StartUp();
    static void ShutDown();
};

#endif