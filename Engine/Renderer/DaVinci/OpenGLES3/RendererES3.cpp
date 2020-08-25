#include "definitions.hpp"

#ifdef OPENGLES3_API
#include <GL/glew.h>


#include "RendererES3.hpp"

/*
    Constructors and DEstructors Functions
*/
RendererES3::RendererES3() {
    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);

    glClearColor(1.f, 0.0f, 1.0f, 1.0f);

    this->gMeshCollectionES3 = MeshCollectionES3();
    this->gCameraCollectionES3 = CameraCollectionES3();
}

RendererES3::~RendererES3() {
    this->gMeshCollectionES3.Destroy();
    this->gCameraCollectionES3.Destroy();
}


/*
    Geral Functions
*/
void RendererES3::EnableFeature(RendererFeature feat, void* feat_params) {}

/*
    Frame Functions
*/

void RendererES3::FrameBegin() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererES3::FrameEnd() {
    
}

void RendererES3::RenderCmd() {

}


std::vector<RendererFeature> RendererES3::GetFeatures() {
    return std::vector<RendererFeature>();
}

/*
    Creators
*/
Mesh RendererES3::CreateMesh(Vertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices) {
    Identifier id = this->gMeshCollectionES3.Allocate(vertex_array_buffer, index_buffer_buffer, num_vertices);

    Mesh sm;
    sm.id = id;

    return sm;
}

Camera RendererES3::CreateCamera(Vec3 position, Vec3 forward){
    Identifier id = this->gCameraCollectionES3.Allocate(glm::vec3(position.x, position.y, position.z), glm::vec3(forward.x, forward.y, forward.z));

    Camera cam;
    cam.id = id;

    return cam;
}


/*
    Destructors
*/
void RendererES3::DestroyCamera(Camera camera) {
    this->gCameraCollectionES3.Dellocate(camera.id);
}


void RendererES3::DestroyMesh(Mesh mesh) {
    this->gMeshCollectionES3.Dellocate(mesh.id);
}


/*
    Render Commands
*/
void RendererES3::DrawMesh(Mesh mesh) {
    MeshES3 _mesh = this->gMeshCollectionES3.Get(mesh.id);

    glBindBuffer(_mesh.VertexArrayBuffer, GL_VERTEX_ARRAY);
    glBindBuffer(_mesh.IndexBuffer, GL_ELEMENT_ARRAY_BUFFER);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
   
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glDrawElements(GL_TRIANGLES, _mesh.num_indices, GL_UNSIGNED_INT, nullptr);
}


#endif