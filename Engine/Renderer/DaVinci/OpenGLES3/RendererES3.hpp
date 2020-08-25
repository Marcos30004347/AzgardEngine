#include "definitions.hpp"

#ifndef BOTTICELLIOPENGLES3_H
#ifdef OPENGLES3_API

#define BOTTICELLIOPENGLES3_H


#include "Renderer/Renderer.hpp"


#include "Mesh/MeshCollectionES3.hpp"
#include "Camera/CameraCollectionES3.hpp"

enum OpenGLES3SuportedFeatures {};

class RendererES3 : public Renderer {
    private:
    MeshCollectionES3 gMeshCollectionES3;
    CameraCollectionES3 gCameraCollectionES3;

    public:
    RendererES3();
    ~RendererES3();

    void FrameBegin();
    void FrameEnd();
    void RenderCmd();

    Mesh CreateMesh(Vertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices);
    Camera CreateCamera(Vec3 position, Vec3 forward);

    void DestroyMesh(Mesh mesh);
    void DestroyCamera(Camera camera);

    void DrawMesh(Mesh mesh);

    std::vector<RendererFeature> GetFeatures();
    void EnableFeature(RendererFeature feat, void* feat_params = nullptr);
};

#endif

#endif