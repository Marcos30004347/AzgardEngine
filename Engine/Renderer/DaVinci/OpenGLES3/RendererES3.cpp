#include "definitions.hpp"

#ifdef OPENGLES3_API
#include <GL/glew.h>


#include "RendererES3.hpp"


RendererES3::RendererES3() {
    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);

    glClearColor(1.f, 0.0f, 1.0f, 1.0f);

    this->gStaticMeshCollectionES3 = StaticMeshCollectionES3();
}

RendererES3::~RendererES3() {
    this->gStaticMeshCollectionES3.Destroy();
}

void RendererES3::FrameBegin() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererES3::FrameEnd() {}

void RendererES3::RenderCmd() {}

void RendererES3::EnableFeature(RendererFeature feat, void* feat_params) {}

std::vector<RendererFeature> RendererES3::GetFeatures() {
    return std::vector<RendererFeature>();
}


StaticMesh RendererES3::CreateStaticMesh(StaticVertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices) {
    Identifier id = this->gStaticMeshCollectionES3.Allocate(vertex_array_buffer, index_buffer_buffer, num_vertices);

    StaticMesh sm;

    sm.id = id;

    return sm;
}


void RendererES3::DestroyStaticMesh(StaticMesh mesh) {
    gStaticMeshCollectionES3.Dellocate(mesh.id);
}


void RendererES3::DrawStaticMesh(StaticMesh mesh) {

}




#endif