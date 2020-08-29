#ifndef RENDERER_H
#define RENDERER_H

#include "Model.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include "DataStructures/Identifier.hpp"
#include "DataStructures/Model.hpp"
#include "DataStructures/Vec3.hpp"


enum GraphicAPI {
    NO_GRAPHIC_API = 0,
    OPENGLES3,
};


class Renderer {
    public:
    virtual void FrameBegin() = 0;
    virtual void FrameRender() = 0;
    virtual void FrameEnd() = 0;
    virtual void FrameSetCamera(CameraHandle camera) = 0;

    virtual void ModelSetVisiblity(ModelHandle model, bool isVisible = true) = 0;
    virtual void MeshSetVisiblity(MeshHandle model, bool isVisible = true) = 0;

    
    virtual ModelHandle ModelCreate(ModelData& data) = 0;
    virtual void ModelDraw(ModelHandle model) = 0;
    virtual void ModelSetMeshShader(ModelHandle model, unsigned int mesh_key, ShaderHandle shader) = 0;
    virtual void ModelDestroy(ModelHandle& model) = 0;

    virtual CameraHandle CameraCreate(Vec3 position, Vec3 forward, CameraProjection projection) = 0;
    virtual void CameraTranslate(CameraHandle camera, Vec3 to) = 0;
    virtual void CameraRotate(CameraHandle camera, float angle, Vec3 axis) = 0;
    virtual void CameraLookAt(CameraHandle camera, Vec3 position) = 0;
    virtual void CameraDestroy(CameraHandle& camera) = 0;

    virtual ShaderHandle ShaderCreate(ShaderData& shader) = 0;
    virtual void ShaderDestroy(ShaderHandle& shader) = 0;
};


// template<typename Implementation>
// class RendererObj {
//     Implementation* iRenderer;

//     public:
//     inline void FrameBegin() { Implementation.FrameBegin(); }
//     inline void FrameEnd() { Implementation.FrameEnd(); }
//     inline void FrameSetCamera(CameraHandle camera) { Implementation.FrameSetCamera(camera); }

//     inline ModelHandle ModelCreate(ModelData& data) { Implementation.ModelCreate(data); }
//     inline void ModelDraw(ModelHandle mesh) { Implementation.ModelDraw(mesh) }
//     inline void ModelSetMeshShader(ModelHandle model, unsigned int mesh_key, ShaderHandle shader) { Implementation.ModelSetMeshShader(model, mesh_key, shader); }
//     inline void ModelDestroy(ModelHandle& model) { Implementation.ModelDestroy(model) }

//     inline CameraHandle CameraCreate(Vec3 position, Vec3 forward, CameraProjection projection) { Implementation.CameraCreate(position, forward, projection); }
//     inline void CameraTranslate(CameraHandle camera, Vec3 to) { Implementation.CameraTranslate(camera, to) }
//     inline void CameraRotate(CameraHandle camera, float angle, Vec3 axis) { Implementation.CameraRotate(camera, angle, axis); }
//     inline void CameraLookAt(CameraHandle camera, Vec3 position) { Implementation.CameraLookAt(camera, position); }
//     inline void CameraDestroy(CameraHandle& camera) { Implementation.CameraDestroy(camera); }

//     inline ShaderHandle ShaderCreate(ShaderData& shader) { Implementation.ShaderCreate(shader); }
//     inline void ShaderDestroy(ShaderHandle& shader) { Implementation.ShaderDestroy(shader); }
// };

#endif