#include "definitions.hpp"

#ifdef OPENGLES3_SUPORTED
#include <iostream>

#include "MeshES3.hpp"
#include "Renderer/OpenGLES3/Shader/ShaderManagerES3.hpp"
#include "Renderer/OpenGLES3/Camera/CameraManagerES3.hpp"

void defaultShaderPipeline(MeshES3* mesh, ShaderES3& shader) {
    shader.UniformMatrix4("model", mesh->ModelMatrix);
}

MeshES3::MeshES3() {};

MeshES3::MeshES3(MeshData data) {
    this->ModelMatrix = glm::mat4(1.0f);

    this->ShaderPipeline = defaultShaderPipeline;

    glGenBuffers(1, &this->VertexArrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VerticeData) * data.vertices.size(), &data.vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &this->IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.indices.size(), &data.indices[0], GL_STATIC_DRAW);

    this->Name = data.name;
    this->NumIndices = data.indices.size();
}
void MeshES3::Draw() {
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexArrayBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IndexBuffer);

    this->ShaderPipeline(this, ShaderManagerES3::GetSingletonPtr()->Get(this->shaderId));

    // CameraES3& _camera = CameraManagerES3::GetSingletonPtr()->Get(camera.id);

    // shader.Use();

    // shader.UniformMatrix4("model", this->ModelMatrix * model_matrix);
    // shader.UniformMatrix4("view", _camera.GetView());
    // shader.UniformMatrix4("projection", _camera.GetProjection());


    // shader.UniformVector3("eyeDir", _camera.GetForward());
    // shader.UniformVector3("lightDir", _camera.GetPosition() + _camera.GetForward());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VerticeData), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VerticeData), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VerticeData), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glDrawElements(GL_TRIANGLES, this->NumIndices, GL_UNSIGNED_INT, nullptr);
}

MeshES3::~MeshES3() {
}

void MeshES3::DestroyBuffers() {

    GLuint buffs[2];
    buffs[0] = this->VertexArrayBuffer;
    buffs[1] = this->IndexBuffer;
    glDeleteBuffers(2, buffs);
}

void MeshES3::SetShader(ShaderHandle shader) {
    this->shaderId = shader.id;
}

void MeshES3::Translate(glm::vec3 to) {
    this->ModelMatrix = glm::translate(this->ModelMatrix, to);
}

void MeshES3::Rotate(glm::vec3 axis, float angle) {
    this->ModelMatrix = glm::rotate(this->ModelMatrix, angle, axis);
}

void MeshES3::Scale(glm::vec3 scale) {
    this->ModelMatrix = glm::scale(this->ModelMatrix, scale);
}

void MeshES3::SetShaderPipeline(const std::function<void(MeshES3* self, ShaderES3& shader)>& shaderPipeline) {
    this->ShaderPipeline = shaderPipeline;
}


#endif