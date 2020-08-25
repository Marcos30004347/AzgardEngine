#include "mesh.h"
#include <stdio.h>

float vertices[] = {
    -0.8f, -0.8f, 0.0f, 0.0f, 1.0f,
    -0.8f, 0.8f, 0.0f, 0.0f, 0.0f,
    0.8f, 0.8f, 0.0f, 1.0f, 0.0f,
    0.8f, -0.8f, 0.0f, 1.0f, 1.0f
};

unsigned int indices[] = {0, 1, 2, 2, 3, 0};

GLES3_Mesh::GLES3_Mesh(const char* filepath) {

    this->_projection = glm::perspective(70.0f, 1.0f, 0.1f, 1000.0f);

    this->_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));

    this->_view = glm::lookAt(glm::vec3(0,0,2), glm::vec3(0,0,0), glm::vec3(0,1,0));

    glGenBuffers(1, &this->_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, vertices, GL_STATIC_DRAW);


    glGenBuffers(1, &this->_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6 , indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void GLES3_Mesh::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, this->_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo);

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, 1);
}



GLES3_Mesh::~GLES3_Mesh() {
    GLuint buffers[2] = {this->_vao, this->_ibo};
    glDeleteBuffers(2, buffers);
}