#ifndef RENDERER_H
#define RENDERER_H

#include "Model.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

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


    virtual ModelHandle ModelCreate(ModelData& data) = 0;
    virtual void ModelDraw(ModelHandle mesh) = 0;
    virtual void ModelSetMeshShader(ModelHandle model, unsigned int mesh_key, ShaderHandle shader) = 0;
    virtual void ModelDestroy(ModelHandle& model) = 0;

    virtual CameraHandle CameraCreate(Vec3 position, Vec3 forward, CameraProjection projection) = 0;
    virtual void CameraTranslate(CameraHandle camera, Vec3 to) = 0;
    virtual void CameraRotate(CameraHandle camera, float angle, Vec3 axis) = 0;
    virtual void CameraLookAt(CameraHandle camera, Vec3 position) = 0;
    virtual void CameraDestroy(CameraHandle& camera) = 0;

    virtual ShaderHandle ShaderCreate(ShaderData& shader) = 0;
    virtual void ShaderDestroy(ShaderHandle& shader) = 0;
    // virtual void Shader(ShaderHandle shader) = 0;
    // virtual void ShaderUniformMatrix4(const char* name, float* data);
    // virtual void ShaderUniformMatrix4Array(const char* name, float* data, unsigned int count) = 0;
    // virtual void ShaderUniformVector4(const char* name, float x, float y, float z, float a) = 0;
    // virtual void ShaderUniformVector3(const char* name, float x, float y, float z) = 0;
    // virtual void ShaderUniformVector2(const char* name, float x, float y) = 0;
    // virtual void ShaderUniformIntArray(const char* name, int* array, int count) = 0;
    // virtual void ShaderUniformFloatArray(const char* name, float* array, int count) = 0;
    // virtual void ShaderUniformVector2Array(const char* name, glm::vec2* array, int count) = 0;
    // virtual void ShaderUniformFloat(const char* name, float x) = 0;
    // virtual void ShaderUniformInt(const char* name, int data) = 0;

    virtual std::vector<RendererFeature> GetFeatures() = 0;
    virtual void EnableFeature(RendererFeature feat, void* feat_params = nullptr) = 0;
};


#endif