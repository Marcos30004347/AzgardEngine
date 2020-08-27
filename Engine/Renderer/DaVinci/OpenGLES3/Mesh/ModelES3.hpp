#include "definitions.hpp"

#ifndef MODELES3_H
#define MODELES3_H

#ifdef OPENGLES3_API

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

    std::vector<MeshES3> Meshes;

    ModelES3();
    ModelES3(ModelData data);

    void Draw(CameraHandle camera);
    void SetMeshShader(unsigned int mesh_key, ShaderHandle shader);

    ~ModelES3();
    void Destroy();
};


#endif
#endif