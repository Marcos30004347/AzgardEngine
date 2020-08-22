#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

enum RendererFeature {};

enum GraphicAPI {
    NONE = 0,
    OPENGLES3,
};


class Renderer {
    public:
    Renderer();
    ~Renderer();

    virtual void FrameBegin() = 0;
    virtual void FrameEnd() = 0;
    virtual void RenderCmd() = 0;

    virtual void StartUp() = 0;
    virtual void ShutDown() = 0;

    virtual std::vector<RendererFeature> GetFeatures() = 0;
    virtual void EnableFeature(RendererFeature feat, void* feat_params = nullptr) = 0;
};

#endif