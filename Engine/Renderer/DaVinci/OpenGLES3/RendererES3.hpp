#include "definitions.hpp"

#ifndef BOTTICELLIOPENGLES3_H
#ifdef OPENGLES3_API

#define BOTTICELLIOPENGLES3_H


#include "Renderer/Renderer.hpp"

#include "Renderer/Camera.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/Shader.hpp"

enum OpenGLES3SuportedFeatures {};

class RendererES3 : public Renderer {
    private:

    CameraHandle activeCamera;

    public:
    RendererES3();
    ~RendererES3();

    void FrameBegin();
    void FrameEnd();
    void FrameSetCamera(CameraHandle camera);

    ModelHandle ModelCreate(ModelData& data);
    void ModelDraw(ModelHandle model);
    void ModelSetMeshShader(ModelHandle model, unsigned int mesh_key, ShaderHandle shader);
    void ModelDestroy(ModelHandle& mesh);

    CameraHandle CameraCreate(Vec3 position, Vec3 forward, CameraProjection projection = PERSPECTIVE_PROJECTION);
    void CameraTranslate(CameraHandle camera, Vec3 to);
    void CameraRotate(CameraHandle camera, float angle, Vec3 axis);
    void CameraLookAt(CameraHandle camera, Vec3 position);
    void CameraDestroy(CameraHandle& camera);

    ShaderHandle ShaderCreate(ShaderData& shader);
    void ShaderDestroy(ShaderHandle& shader);
    // void ShaderUniformMatrix4(ShaderHandle shader, const char* name, float* data);
    // void ShaderUniformMatrix4Array(ShaderHandle shader, const char* name, float* data, unsigned int count);
    // void ShaderUniformVector4(ShaderHandle shader, const char* name, float x, float y, float z, float a);
    // void ShaderUniformVector3(ShaderHandle shader, const char* name, float x, float y, float z);
    // void ShaderUniformVector2(ShaderHandle shader, const char* name, float x, float y);
    // void ShaderUniformIntArray(ShaderHandle shader, const char* name, int* array, int count);
    // void ShaderUniformFloatArray(ShaderHandle shader, const char* name, float* array, int count);
    // void ShaderUniformVector2Array(ShaderHandle shader, const char* name, glm::vec2* array, int count);
    // void ShaderUniformFloat(ShaderHandle shader, const char* name, float x);
    // void ShaderUniformInt(ShaderHandle shader, const char* name, int data);

    std::vector<RendererFeature> GetFeatures();
    void EnableFeature(RendererFeature feat, void* feat_params = nullptr);
};

#endif

#endif