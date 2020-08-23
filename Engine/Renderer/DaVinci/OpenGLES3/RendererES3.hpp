#include "definitions.hpp"

#ifndef BOTTICELLIOPENGLES3_H
#ifdef OPENGLES3_API

#define BOTTICELLIOPENGLES3_H


#include "Renderer/Renderer.hpp"
#include "DataStructures/Identifier.hpp"
#include "Mesh/StaticMeshCollectionES3.hpp"

enum OpenGLES3SuportedFeatures {};

class RendererES3 : public Renderer {
    private:
    StaticMeshCollectionES3 gStaticMeshCollectionES3;

    public:
    RendererES3();
    ~RendererES3();

    void FrameBegin();
    void FrameEnd();
    void RenderCmd();

    StaticMesh CreateStaticMesh(StaticVertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices);

    void DestroyStaticMesh(StaticMesh mesh);

    void DrawStaticMesh(StaticMesh mesh);

    std::vector<RendererFeature> GetFeatures();
    void EnableFeature(RendererFeature feat, void* feat_params = nullptr);
};

#endif

#endif