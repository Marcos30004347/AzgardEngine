#include "definitions.hpp"

#ifndef BOTTICELLIOPENGLES3_H
#ifdef OPENGLES3_SUPORTED

#define BOTTICELLIOPENGLES3_H

#include<vector>

#include "Renderer/Renderer.hpp"

#include "Renderer/Camera.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/Shader.hpp"

enum OpenGLES3SuportedFeatures {};

struct RenderBatch{
    Identifier shader;
    std::vector<Identifier> meshes;
};

class RendererES3 : public Renderer {
    private:
    CameraHandle activeCamera;
    std::vector<RenderBatch> batches;
    
    public:
    RendererES3();
    ~RendererES3();

    void FrameBegin();
    void FrameRender();
    void FrameEnd();

    void FrameSetCamera(CameraHandle camera);

    void MeshSetVisiblity(MeshHandle model, bool isVisible = true);
    void ModelSetVisiblity(ModelHandle model, bool isVisible = true);
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
};

#endif

#endif