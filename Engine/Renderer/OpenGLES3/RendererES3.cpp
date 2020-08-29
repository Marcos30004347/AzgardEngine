#include "definitions.hpp"

#ifdef OPENGLES3_SUPORTED
#include <GL/glew.h>

#include "RendererES3.hpp"

#include "Mesh/MeshManagerES3.hpp"
#include "Mesh/ModelManagerES3.hpp"
#include "Camera/CameraManagerES3.hpp"
#include "Shader/ShaderManagerES3.hpp"

std::vector<Identifier> usedShaders();
int getMax(int array[], int n) {
  int max = array[0];
  for (int i = 1; i < n; i++)
    if (array[i] > max)
      max = array[i];
  return max;
}


MeshManagerES3* gMeshManagerES3 = nullptr;
ModelManagerES3* gModelManagerES3 = nullptr;
CameraManagerES3* gCameraManagerES3 = nullptr;
ShaderManagerES3* gShaderManagerES3 = nullptr;

/*
    Constructors and DEstructors Functions
*/
RendererES3::RendererES3() {
    MeshManagerES3::StartUp();
    ModelManagerES3::StartUp();
    CameraManagerES3::StartUp();
    ShaderManagerES3::StartUp();

    gModelManagerES3 = ModelManagerES3::GetSingletonPtr();
    gMeshManagerES3 = MeshManagerES3::GetSingletonPtr();
    gCameraManagerES3 = CameraManagerES3::GetSingletonPtr();
    gShaderManagerES3 = ShaderManagerES3::GetSingletonPtr();

    glEnable(GL_BLEND);  
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);  
    glCullFace(GL_FRONT);  
    glFrontFace(GL_CW);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(1.f, 1.0f, 1.0f, 1.0f);


    this->batches = std::vector<RenderBatch>();
}

RendererES3::~RendererES3() {
    MeshManagerES3::ShutDown();
    CameraManagerES3::ShutDown();
    ShaderManagerES3::ShutDown();

    gMeshManagerES3 = nullptr;
    gCameraManagerES3 = nullptr;
    gShaderManagerES3 = nullptr;
}

void RendererES3::ModelSetVisiblity(ModelHandle model, bool isVisible) {
    for(Identifier meshId : gModelManagerES3->Get(model.id).Meshes) {
        MeshHandle meshH;
        meshH.id = meshId;

        this->MeshSetVisiblity(meshH, isVisible);
    }
}

void RendererES3::MeshSetVisiblity(MeshHandle mesh, bool isVisible) {
    
    MeshES3& mesh_instance = gMeshManagerES3->Get(mesh.id);

    RenderBatch* meshBatch = nullptr;

    int batchID = 0;

    for(RenderBatch batch : this->batches) {
        if(batch.shader == mesh_instance.shaderId) {
            meshBatch = &batch;
            break;
        }
        batchID++;
    }

    if(meshBatch) {
        if(isVisible == false) {

            for(int i=0; i<meshBatch->meshes.size(); i++) {
                if(meshBatch->meshes[i] == mesh.id) {

                    meshBatch->meshes.erase(meshBatch->meshes.begin() + i);
                    break;
                }
            }
        } else {
            meshBatch->meshes.push_back(mesh.id);
        }
        
        if(meshBatch->meshes.size() == 0) this->batches.erase(this->batches.begin() + batchID);
    } else {

        printf("adding %i\n", mesh.id);
        RenderBatch batch = {};
    
        batch.shader = mesh_instance.shaderId;
    
        this->batches.push_back(batch);
        this->batches[this->batches.size() - 1].meshes.push_back(mesh.id);
    }
}


/*
    Frame Functions
*/

void RendererES3::FrameBegin() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererES3::FrameRender() {
    for(RenderBatch batch: this->batches) {
        ShaderES3& shader_instance = gShaderManagerES3->Get(batch.shader);
        CameraES3& camera_instance = gCameraManagerES3->Get(this->activeCamera.id);

        shader_instance.Use();
        shader_instance.UniformVector3("eyeDir", camera_instance.GetForward());
        shader_instance.UniformVector3("lightDir", camera_instance.GetPosition() + camera_instance.GetForward());
        shader_instance.UniformMatrix4("projection", camera_instance.GetProjection());
        shader_instance.UniformMatrix4("view", camera_instance.GetView());
    
        for(Identifier id : batch.meshes) {
            gMeshManagerES3->Get(id).Draw();
            gMeshManagerES3->Get(id).Rotate(glm::vec3(0,1,0), glm::radians(1.5f));
        }
    }
}

void RendererES3::FrameEnd() {
}

void RendererES3::FrameSetCamera(CameraHandle camera) {
   this->activeCamera = camera; 
}



/*
    Model
*/
ModelHandle RendererES3::ModelCreate(ModelData& data) {
    ModelES3 model(data);

    ModelHandle sm;
    sm.id = gModelManagerES3->Insert(model);
    sm.name = data.name;

    return sm;
}

void RendererES3::ModelDestroy(ModelHandle& model) {
    gModelManagerES3->Delete(model.id);
    model.id = UINT32_MAX;
}

void RendererES3::ModelDraw(ModelHandle model) {
    gModelManagerES3->Get(model.id).Draw();
}

void RendererES3::ModelSetMeshShader(ModelHandle model, unsigned int mesh_key, ShaderHandle shader) {
    gModelManagerES3->Get(model.id).SetMeshShader(mesh_key, shader);
}


/*
    Camera
*/
CameraHandle RendererES3::CameraCreate(Vec3 position, Vec3 forward, CameraProjection projection){
    CameraES3 camera(glm::vec3(position.x, position.y, position.z), glm::vec3(forward.x, forward.y, forward.z), projection);

    CameraHandle cam;
    cam.id = gCameraManagerES3->Insert(camera);
    return cam;
}


void RendererES3::CameraDestroy(CameraHandle& camera) {
    gCameraManagerES3->Delete(camera.id);
    camera.id = UINT32_MAX;
}

void RendererES3::CameraTranslate(CameraHandle camera, Vec3 to) {
    gCameraManagerES3->Get(camera.id).Translate(glm::vec3(to.x, to.y, to.z));
}

void RendererES3::CameraRotate(CameraHandle camera, float angle, Vec3 axis) {
    gCameraManagerES3->Get(camera.id).Rotate(angle, glm::vec3(axis.x, axis.y, axis.z));
}

void RendererES3::CameraLookAt(CameraHandle camera, Vec3 position) {
    gCameraManagerES3->Get(camera.id).LookAt(glm::vec3(position.x, position.y, position.z));
}


/*
    Shader
*/
ShaderHandle RendererES3::ShaderCreate(ShaderData& shader) {
    ShaderES3 shaderes3(shader);

    ShaderHandle shaderHandle = {};
    shaderHandle.id = gShaderManagerES3->Insert(shaderes3);
    return shaderHandle;
}

void RendererES3::ShaderDestroy(ShaderHandle& shader) {
    gShaderManagerES3->Delete(shader.id);
    shader.id = UINT32_MAX;
}



#endif