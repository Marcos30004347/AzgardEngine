#ifndef BOTTICELLIOPENGLES3_H
#define BOTTICELLIOPENGLES3_H

#include "definitions.hpp"

#ifdef OPENGLES3_API

#include "Renderer/Renderer.hpp"

enum OpenGLES3SuportedFeatures {};

class BotticelliOpenGLES3 : public Renderer {
    public:
    BotticelliOpenGLES3();
    ~BotticelliOpenGLES3();

    void StartUp();
    void ShutDown();

    void FrameBegin();
    void FrameEnd();
    void RenderCmd();

    std::vector<RendererFeature> GetFeatures();
    void EnableFeature(RendererFeature feat, void* feat_params = nullptr);
};

#endif

#endif