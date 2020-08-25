#include "definitions.hpp"
#ifdef OPENGLES3_API

#include "MeshES3.hpp"
#include "DataStructures/Identifier.hpp"

MeshES3::MeshES3() {};

MeshES3::MeshES3(Vertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices) {
    this->ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));

    glGenBuffers(1, &this->VertexArrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * num_vertices, vertex_array_buffer, GL_STATIC_DRAW);


    glGenBuffers(1, &this->IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * num_vertices, index_buffer_buffer, GL_STATIC_DRAW);

    this->num_indices = num_vertices;
}

MeshES3::~MeshES3() {
    this->Destroy();
}

void MeshES3::Destroy() {
    GLuint buffs[2];
    buffs[0] = this->VertexArrayBuffer;
    buffs[1] = this->IndexBuffer;
    glDeleteBuffers(2, buffs);
}

#endif