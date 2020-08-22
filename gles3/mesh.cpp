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
    
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
    // glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // this->model = glm::rotate(this->model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // angle+=bias;
    // printf("%f\n", angle);
    // printf("%f\n", bias);
    // if(angle>=10 || angle<=0.01f) {
    //     bias*=-1.0f;
    // }

    // unsigned int modelLoc = glGetUniformLocation(this->_shader_id, "model");
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &this->_model[0][0]);
    // unsigned int viewLoc = glGetUniformLocation(this->_shader_id, "view");
    // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &this->_view[0][0]);
    // unsigned int projectionLoc = glGetUniformLocation(this->_shader_id, "projection");
    // glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &this->_projection[0][0]);

    // unsigned int textureLayerLoc = glGetUniformLocation(this->_shader_id, "textureLayer");
    // glUniform1i(textureLayerLoc, 1);

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, 1);
}



GLES3_Mesh::~GLES3_Mesh() {
    GLuint buffers[2] = {this->_vao, this->_ibo};
    glDeleteBuffers(2, buffers);
}