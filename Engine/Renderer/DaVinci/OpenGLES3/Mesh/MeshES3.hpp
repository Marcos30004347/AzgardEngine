#include "definitions.hpp"

#ifndef MESHES3_H
#define MESHES3_H

#ifdef OPENGLES3_API

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Renderer/Shader.hpp"
#include "Renderer/Camera.hpp"

#include "DataStructures/Model.hpp"
#include "DataStructures/Identifier.hpp"

class MeshES3 {
    public:

    const char* Name;

    GLuint VertexArrayBuffer;
    GLuint IndexBuffer;

    ShaderHandle hShader;

    unsigned int NumIndices;

    MeshES3();
    MeshES3(MeshData data);

    void Draw(CameraHandle camera, glm::mat4 model);
    void SetShader(ShaderHandle shader);

    ~MeshES3();
    void DestroyBuffers();
};


#endif
#endif