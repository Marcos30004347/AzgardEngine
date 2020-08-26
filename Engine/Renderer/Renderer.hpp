#ifndef RENDERER_H
#define RENDERER_H

#include "Model.hpp"
#include "Camera.hpp"

#include "DataStructures/Identifier.hpp"
#include "DataStructures/Model.hpp"
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
    virtual void FrameSetCamera(CameraHandle camera) = 0;


    virtual ModelHandle ModelCreate(ModelData data) = 0;
    virtual void ModelDraw(ModelHandle mesh) = 0;
    virtual void ModelDestroy(ModelHandle model) = 0;

    virtual CameraHandle CameraCreate(Vec3 position, Vec3 forward, CameraProjection projection) = 0;
    virtual void CameraTranslate(CameraHandle camera, Vec3 to) = 0;
    virtual void CameraRotate(CameraHandle camera, float angle, Vec3 axis) = 0;
    virtual void CameraLookAt(CameraHandle camera, Vec3 position) = 0;
    virtual void CameraDestroy(CameraHandle camera) = 0;


    virtual std::vector<RendererFeature> GetFeatures() = 0;
    virtual void EnableFeature(RendererFeature feat, void* feat_params = nullptr) = 0;
};


#endif