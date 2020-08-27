#include "definitions.hpp"

#ifdef OPENGLES3_API
#include <iostream>

#include "MeshES3.hpp"
#include "Renderer/DaVinci/OpenGLES3/CollectionsES3.hpp"

MeshES3::MeshES3() {};

MeshES3::MeshES3(MeshData data) {
    glGenBuffers(1, &this->VertexArrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VerticeData) * data.vertices.size(), &data.vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &this->IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.indices.size(), &data.indices[0], GL_STATIC_DRAW);

    this->Name = data.name;
    this->NumIndices = data.indices.size();
}
void MeshES3::Draw(CameraHandle camera, glm::mat4 model) {

    glBindBuffer(GL_ARRAY_BUFFER, this->VertexArrayBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IndexBuffer);
 
    ShaderES3 shader = CollectionsES3::Shaders->Get(this->hShader.id);
    CameraES3 _camera = CollectionsES3::Cameras->Get(camera.id);

    shader.Use();

    shader.UniformMatrix4("model", model);
    shader.UniformMatrix4("view", _camera.GetView());
    shader.UniformMatrix4("projection", _camera.GetProjection());
    shader.UniformMatrix4("projection", _camera.GetProjection());
    shader.UniformMatrix4("projection", _camera.GetProjection());


    shader.UniformVector3("eyeDir", _camera.GetForward());
    shader.UniformVector3("lightDir", _camera.GetPosition() + _camera.GetForward());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VerticeData), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VerticeData), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VerticeData), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glDrawElements(GL_TRIANGLES, this->NumIndices, GL_UNSIGNED_INT, nullptr);
}

MeshES3::~MeshES3() {}

void MeshES3::DestroyBuffers() {

    GLuint buffs[2];
    buffs[0] = this->VertexArrayBuffer;
    buffs[1] = this->IndexBuffer;
    glDeleteBuffers(2, buffs);
}

void MeshES3::SetShader(ShaderHandle shader) {
    this->hShader = shader;
}


#endif