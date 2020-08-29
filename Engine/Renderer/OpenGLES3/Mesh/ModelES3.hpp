#include "definitions.hpp"

#ifndef MODELES3_H
#define MODELES3_H

#ifdef OPENGLES3_SUPORTED

#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Renderer/Model.hpp"
#include "Renderer/Camera.hpp"

#include "MeshES3.hpp"

#include "DataStructures/Model.hpp"

class ModelES3 {
    public:

    const char* Name;

    glm::mat4 ModelMatrix;
    glm::vec3 boundingBox[2];

    std::vector<Identifier> Meshes;

    ModelES3();
    ModelES3(ModelData& data);

    void Draw();
    void SetMeshShader(unsigned int mesh_key, ShaderHandle shader);
    void SetMeshShaderPipeline(unsigned int mesh_key, const std::function<void(MeshES3* self, ShaderES3& shader)>& shaderPipeline);

    void Translate(glm::vec3 to);
    void Rotate(glm::vec3 axis, float angle);
    void Scale(glm::vec3 scale);

    ~ModelES3();
    void Destroy();
};


#endif
#endif