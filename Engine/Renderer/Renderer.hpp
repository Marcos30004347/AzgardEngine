#ifndef RENDERER_H
#define RENDERER_H

#include "Mesh.hpp"
#include "Camera.hpp"

#include "DataStructures/Identifier.hpp"
#include "DataStructures/Vertice.hpp"
#include "DataStructures/Vec3.hpp"

enum RendererFeature {};

enum GraphicAPI {
    NO_GRAPHIC_API = 0,
    OPENGLES3,
};


class Renderer {
    public:
    virtual void FrameBegin() = 0;
    virtual void FrameEnd() = 0;

    virtual void DrawMesh(Mesh mesh) = 0;

    virtual Mesh CreateMesh(Vertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices) = 0;
    virtual Camera CreateCamera(Vec3 position, Vec3 forward) = 0;

    virtual void DestroyMesh(Mesh mesh) = 0;
    virtual void DestroyCamera(Camera camera) = 0;

    virtual std::vector<RendererFeature> GetFeatures() = 0;
    virtual void EnableFeature(RendererFeature feat, void* feat_params = nullptr) = 0;
};


#endif