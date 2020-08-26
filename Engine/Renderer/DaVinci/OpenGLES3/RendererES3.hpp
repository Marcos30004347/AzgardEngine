#include "definitions.hpp"

#ifndef BOTTICELLIOPENGLES3_H
#ifdef OPENGLES3_API

#define BOTTICELLIOPENGLES3_H


#include "Renderer/Renderer.hpp"


#include "Mesh/ModelCollectionES3.hpp"
#include "Camera/CameraCollectionES3.hpp"

enum OpenGLES3SuportedFeatures {};

class RendererES3 : public Renderer {
    private:
    ModelCollectionES3 gModelCollectionES3;
    CameraCollectionES3 gCameraCollectionES3;

    CameraES3 activeCamera;

    public:
    RendererES3();
    ~RendererES3();

    void FrameBegin();
    void FrameEnd();
    void FrameSetCamera(CameraHandle camera);

    ModelHandle ModelCreate(ModelData data);
    void ModelDestroy(ModelHandle mesh);
    void ModelDraw(ModelHandle model);

    CameraHandle CameraCreate(Vec3 position, Vec3 forward, CameraProjection projection = PERSPECTIVE_PROJECTION);
    void CameraTranslate(CameraHandle camera, Vec3 to);
    void CameraRotate(CameraHandle camera, float angle, Vec3 axis);
    void CameraLookAt(CameraHandle camera, Vec3 position);
    void CameraDestroy(CameraHandle camera);


    std::vector<RendererFeature> GetFeatures();
    void EnableFeature(RendererFeature feat, void* feat_params = nullptr);
};

#endif

#endif