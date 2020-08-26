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

    this->gModelCollectionES3 = ModelCollectionES3();
    this->gCameraCollectionES3 = CameraCollectionES3();
}

RendererES3::~RendererES3() {
    this->gModelCollectionES3.Destroy();
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

void RendererES3::FrameSetCamera(CameraHandle camera) {
   this->activeCamera = this->gCameraCollectionES3.Get(camera.id); 
}



std::vector<RendererFeature> RendererES3::GetFeatures() {
    return std::vector<RendererFeature>();
}

/*
    Model
*/
ModelHandle RendererES3::ModelCreate(ModelData data) {
    Identifier id = this->gModelCollectionES3.Allocate(data);

    ModelHandle sm;
    sm.id = id;
    sm.name = data.name;

    return sm;
}

void RendererES3::ModelDestroy(ModelHandle mesh) {
    this->gModelCollectionES3.Dellocate(mesh.id);
}

void RendererES3::ModelDraw(ModelHandle model) {
    this->gModelCollectionES3.Get(model.id).Draw();
    // internModel->Draw();
}




/*
    Camera
*/
CameraHandle RendererES3::CameraCreate(Vec3 position, Vec3 forward, CameraProjection projection){
    Identifier id = this->gCameraCollectionES3.Allocate(glm::vec3(position.x, position.y, position.z), glm::vec3(forward.x, forward.y, forward.z), projection);

    CameraHandle cam;
    cam.id = id;

    return cam;
}


void RendererES3::CameraDestroy(CameraHandle camera) {
    this->gCameraCollectionES3.Dellocate(camera.id);
}

void RendererES3::CameraTranslate(CameraHandle camera, Vec3 to) {
    this->gCameraCollectionES3.Get(camera.id).Translate(glm::vec3(to.x, to.y, to.z));
}
void RendererES3::CameraRotate(CameraHandle camera, float angle, Vec3 axis) {
    this->gCameraCollectionES3.Get(camera.id).Rotate(angle, glm::vec3(axis.x, axis.y, axis.z));
}
void RendererES3::CameraLookAt(CameraHandle camera, Vec3 position) {
    this->gCameraCollectionES3.Get(camera.id).LookAt(glm::vec3(position.x, position.y, position.z));
}


#endif