#include "definitions.hpp"

#ifdef OPENGLES3_API
#include <GL/glew.h>
#include<iostream>
#include "MeshES3.hpp"

MeshES3::MeshES3() {};

MeshES3::MeshES3(MeshData data) {
    glGenBuffers(1, &this->VertexArrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VerticeData) * data.vertices.size(), &data.vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.indices.size(), &data.indices[0], GL_STATIC_DRAW);

    // std::vector<float> vao = std::vector<float>(data.vertices.size());

    // for(int i=0;i<data.vertices.size(); i++) {
    //     std::cout << data.vertices[i].posX << " " << data.vertices[i].posY << " " << data.vertices[i].posZ << std::endl;

    //     // vao.push_back(data.vertices[i].posX);
    //     // vao.push_back(data.vertices[i].posY);
    //     // vao.push_back(data.vertices[i].posZ);
    //     // vao.push_back(data.vertices[i].uvX);
    //     // vao.push_back(data.vertices[i].uvY);
    //     // vao.push_back(data.vertices[i].normX);
    //     // vao.push_back(data.vertices[i].normY);
    //     // vao.push_back(data.vertices[i].normZ);
    // }


    this->Name = data.name;
    this->NumIndices = data.indices.size();

    // for(int i=0; i<data.indices.size(); i++)
    //     printf("%i\n", data.indices[i]);
}

void MeshES3::Draw() {
    // printf("NOTHING %i\n", glGetError());
    // printf("NOTHING %i\n",  this->VertexArrayBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, this->VertexArrayBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IndexBuffer);
    // printf("BINDINGS %i\n", glGetError());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VerticeData), (void*)(0 * sizeof(float)));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VerticeData), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VerticeData), (void*)(5 * sizeof(float)));
   
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // printf("ENABLE ATTRIBS %i\n", glGetError());

    glDrawElements(GL_TRIANGLES, this->NumIndices, GL_UNSIGNED_INT, nullptr);

    // glDrawArrays(GL_TRIANGLES, 0, 10);


    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // printf("ahdhsadushdusahdashds %i\n", this->NumIndices);

}

MeshES3::~MeshES3() {}

void MeshES3::DestroyBuffers() {

    GLuint buffs[2];
    buffs[0] = this->VertexArrayBuffer;
    buffs[1] = this->IndexBuffer;
    glDeleteBuffers(2, buffs);
}

#endif