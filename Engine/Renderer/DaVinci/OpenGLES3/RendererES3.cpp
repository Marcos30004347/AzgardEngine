#include "definitions.hpp"

#ifdef OPENGLES3_API
#include <GL/glew.h>

#include "RendererES3.hpp"
#include "CollectionsES3.hpp"

/*
    Constructors and DEstructors Functions
*/
RendererES3::RendererES3() {
    CollectionsES3::StartUp();

    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.f, 1.0f, 1.0f, 1.0f);
}

RendererES3::~RendererES3() {
    CollectionsES3::ShutDown();
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
   this->activeCamera = camera; 
}



std::vector<RendererFeature> RendererES3::GetFeatures() {
    return std::vector<RendererFeature>();
}

/*
    Model
*/
ModelHandle RendererES3::ModelCreate(ModelData& data) {
    ModelES3 model(data);

    ModelHandle sm;
    sm.id = CollectionsES3::Models->Insert(model);
    sm.name = data.name;
    return sm;
}

void RendererES3::ModelDestroy(ModelHandle& model) {
    CollectionsES3::Models->Delete(model.id);
    model.id = UINT32_MAX;
}

void RendererES3::ModelDraw(ModelHandle model) {
    CollectionsES3::Models->Get(model.id).Draw(this->activeCamera);
}

void RendererES3::ModelSetMeshShader(ModelHandle model, unsigned int mesh_key, ShaderHandle shader) {
    CollectionsES3::Models->Get(model.id).SetMeshShader(mesh_key, shader);
}


/*
    Camera
*/
CameraHandle RendererES3::CameraCreate(Vec3 position, Vec3 forward, CameraProjection projection){
    CameraES3 camera(glm::vec3(position.x, position.y, position.z), glm::vec3(forward.x, forward.y, forward.z), projection);

    CameraHandle cam;
    cam.id = CollectionsES3::Cameras->Insert(camera);
    return cam;
}


void RendererES3::CameraDestroy(CameraHandle& camera) {
    CollectionsES3::Cameras->Delete(camera.id);
    camera.id = UINT32_MAX;
}

void RendererES3::CameraTranslate(CameraHandle camera, Vec3 to) {
    CollectionsES3::Cameras->Get(camera.id).Translate(glm::vec3(to.x, to.y, to.z));
}

void RendererES3::CameraRotate(CameraHandle camera, float angle, Vec3 axis) {
    CollectionsES3::Cameras->Get(camera.id).Rotate(angle, glm::vec3(axis.x, axis.y, axis.z));
}

void RendererES3::CameraLookAt(CameraHandle camera, Vec3 position) {
    CollectionsES3::Cameras->Get(camera.id).LookAt(glm::vec3(position.x, position.y, position.z));
}


/*
    Shader
*/
ShaderHandle RendererES3::ShaderCreate(ShaderData& shader) {
    ShaderES3 shaderes3(shader);

    ShaderHandle shaderHandle = {};
    shaderHandle.id = CollectionsES3::Shaders->Insert(shaderes3);
    return shaderHandle;
}

void RendererES3::ShaderDestroy(ShaderHandle& shader) {
    CollectionsES3::Shaders->Delete(shader.id);
    shader.id = UINT32_MAX;
}


// void RendererES3::ShaderUniformMatrix4(const char* name, float* data) {

// }
// void RendererES3::ShaderUniformMatrix4Array(const char* name, float* data, unsigned int count) {

// }
// void RendererES3::ShaderUniformVector4(const char* name, float x, float y, float z, float a) {

// }
// void RendererES3::ShaderUniformVector3(const char* name, float x, float y, float z) {

// }
// void RendererES3::ShaderUniformVector2(const char* name, float x, float y) {

// }
// void RendererES3::ShaderUniformIntArray(const char* name, int* array, int count) {

// }
// void RendererES3::ShaderUniformFloatArray(const char* name, float* array, int count) {

// }
// void RendererES3::ShaderUniformVector2Array(const char* name, glm::vec2* array, int count) {

// }
// void RendererES3::ShaderUniformFloat(const char* name, float x) {

// }
// void RendererES3::ShaderUniformInt(const char* name, int data) {

// }

#endif