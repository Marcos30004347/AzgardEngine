#ifndef RENDERER_H
#define RENDERER_H

#include "Mesh.hpp"

/*

StaticMesh model = renderer->CreateStaticMesh();

StaticMesh* model = new StaticMesh();

renderer->BeginFrame();

renderer->RenderCmd<StaticMesh>(model);
renderer->RenderCmd<InstancedStaticMesh>(model);

renderer->EndFrame();

*/

#include <vector>

enum RendererFeature {};

enum GraphicAPI {
    NO_GRAPHIC_API = 0,
    OPENGLES3,
};


class Renderer {
    public:
    virtual void FrameBegin() = 0;
    virtual void FrameEnd() = 0;

    virtual void DrawStaticMesh(StaticMesh mesh) = 0;

    virtual StaticMesh CreateStaticMesh(StaticVertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices) = 0;

    virtual void DestroyStaticMesh(StaticMesh mesh) = 0;

    virtual std::vector<RendererFeature> GetFeatures() = 0;
    virtual void EnableFeature(RendererFeature feat, void* feat_params = nullptr) = 0;
};


#endif