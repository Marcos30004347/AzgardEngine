#include "definitions.hpp"

#ifndef MESHES3_H
#define MESHES3_H

#ifdef OPENGLES3_SUPORTED

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <functional>

#include "Renderer/Shader.hpp"
#include "Renderer/OpenGLES3/Shader/ShaderES3.hpp"
#include "Renderer/Camera.hpp"

#include "DataStructures/Model.hpp"
#include "DataStructures/Identifier.hpp"

class MeshES3 {
    public:

    const char* Name;

    GLuint VertexArrayBuffer;
    GLuint IndexBuffer;

    glm::mat4 ModelMatrix;

    Identifier shaderId;
    std::function<void(MeshES3* self, ShaderES3& shader)> ShaderPipeline;

    unsigned int NumIndices;

    MeshES3();
    MeshES3(MeshData data);

    void Draw();
    void SetShader(ShaderHandle shader);
    void SetShaderPipeline(const std::function<void(MeshES3* self, ShaderES3& shader)>& shaderPipeline);

    void Translate(glm::vec3 to);
    void Rotate(glm::vec3 axis, float angle);
    void Scale(glm::vec3 scale);

    ~MeshES3();
    void DestroyBuffers();
};


#endif
#endif