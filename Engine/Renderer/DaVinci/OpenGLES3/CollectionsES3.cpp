#include "definitions.hpp"

#ifdef OPENGLES3_API

#include "CollectionsES3.hpp"

Collection<ModelES3> * CollectionsES3::Models = nullptr;
Collection<ShaderES3> * CollectionsES3::Shaders = nullptr;
Collection<CameraES3> * CollectionsES3::Cameras = nullptr;

CollectionsES3::CollectionsES3() {}

CollectionsES3::~CollectionsES3() {}

void CollectionsES3::StartUp() {
    CollectionsES3::instance = new CollectionsES3();

    CameraCollectionES3::StartUp();
    ModelCollectionES3::StartUp();
    ShaderCollectionES3::StartUp();

    CollectionsES3::instance->Cameras = CameraCollectionES3::GetSingletonPtr();
    CollectionsES3::instance->Models = ModelCollectionES3::GetSingletonPtr();
    CollectionsES3::instance->Shaders = ShaderCollectionES3::GetSingletonPtr();
}


void CollectionsES3::ShutDown() {
    CameraCollectionES3::ShutDown();
    ModelCollectionES3::ShutDown();
    ShaderCollectionES3::ShutDown();

    CollectionsES3::instance = nullptr;
}

#endif