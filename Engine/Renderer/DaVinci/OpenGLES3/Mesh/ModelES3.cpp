#include "definitions.hpp"
#ifdef OPENGLES3_API
#include<iostream>
#include "ModelES3.hpp"

ModelES3::ModelES3() {};

ModelES3::ModelES3(ModelData data) {
    this->ModelMatrix = glm::mat4(1.0f);

    this->Meshes = std::vector<MeshES3>(data.meshes.size());

    for(int m=0; m<data.meshes.size(); m++)
        this->Meshes[m] = MeshES3(data.meshes[m]);

    this->Name = data.name;
}

ModelES3::~ModelES3() {}

void ModelES3::Destroy() {
    // for(MeshES3 mesh : this->Meshes)
    //     mesh.Destroy();
}

void ModelES3::Draw() {
    for(int m=0; m<this->Meshes.size(); m++) {
        this->Meshes[m].Draw();

    }
}


#endif