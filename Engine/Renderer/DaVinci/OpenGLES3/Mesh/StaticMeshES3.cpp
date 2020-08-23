#include "definitions.hpp"
#ifdef OPENGLES3_API

#include "StaticMeshES3.hpp"
#include "DataStructures/Identifier.hpp"

StaticMeshES3::StaticMeshES3() {};

StaticMeshES3::StaticMeshES3(StaticVertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices) {
    this->ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));

    glGenBuffers(1, &this->VertexArrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(StaticVertice) * num_vertices, vertex_array_buffer, GL_STATIC_DRAW);


    glGenBuffers(1, &this->IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * num_vertices, index_buffer_buffer, GL_STATIC_DRAW);
}

StaticMeshES3::~StaticMeshES3() {
    this->Destroy();
}

void StaticMeshES3::Destroy() {
    GLuint buffs[2];
    buffs[0] = this->VertexArrayBuffer;
    buffs[1] = this->IndexBuffer;
    glDeleteBuffers(2, buffs);
}

#endif