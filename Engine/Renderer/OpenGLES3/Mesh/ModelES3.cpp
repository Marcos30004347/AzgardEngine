#include "definitions.hpp"
#ifdef OPENGLES3_SUPORTED
#include<iostream>
#include "ModelES3.hpp"
#include "MeshManagerES3.hpp"


ModelES3::ModelES3() {};

ModelES3::ModelES3(ModelData& data) {
    this->ModelMatrix = glm::mat4(1.0f);

    this->boundingBox[0] = glm::vec3(data.boundings.p0x, data.boundings.p0y, data.boundings.p0z);
    this->boundingBox[1] = glm::vec3(data.boundings.p1x, data.boundings.p1y, data.boundings.p1z);
    MeshManagerES3* gMeshManagerES3 = MeshManagerES3::GetSingletonPtr();

    this->Meshes = std::vector<Identifier>(data.meshes.size());
    for(int m=0; m<data.meshes.size(); m++) {
        MeshES3 mesh = MeshES3(data.meshes[m]);
        mesh.ModelMatrix = this->ModelMatrix;
        this->Meshes[m] = gMeshManagerES3->Insert(mesh);
    }

    this->Name = data.name;
}

ModelES3::~ModelES3() {}

void ModelES3::Destroy() {
    MeshManagerES3* gMeshManagerES3 = MeshManagerES3::GetSingletonPtr();

    for(int m=0; m<this->Meshes.size(); m++) {
        gMeshManagerES3->Delete(m);
    }
}

void ModelES3::Draw() {
    MeshManagerES3* gMeshManagerES3 = MeshManagerES3::GetSingletonPtr();

    for(int m=0; m<this->Meshes.size(); m++) {
        gMeshManagerES3->Get(m).Draw();
    }
}

void ModelES3::SetMeshShader(unsigned int mesh_key, ShaderHandle shader) {
    MeshManagerES3* gMeshManagerES3 = MeshManagerES3::GetSingletonPtr();
    gMeshManagerES3->Get(this->Meshes[mesh_key]).shaderId = shader.id;
}


void ModelES3::Translate(glm::vec3 to) {
    MeshManagerES3* gMeshManagerES3 = MeshManagerES3::GetSingletonPtr();
    for(int m=0; m<this->Meshes.size(); m++) {
        gMeshManagerES3->Get(this->Meshes[m]).Translate(to);
    }
    this->ModelMatrix = glm::translate(this->ModelMatrix, to);

}

void ModelES3::Rotate(glm::vec3 axis, float angle) {
    MeshManagerES3* gMeshManagerES3 = MeshManagerES3::GetSingletonPtr();
    for(int m=0; m<this->Meshes.size(); m++) {
        gMeshManagerES3->Get(this->Meshes[m]).Rotate(axis, angle);
    }

    this->ModelMatrix = glm::rotate(this->ModelMatrix, angle, axis);

}

void ModelES3::Scale(glm::vec3 scale) {
    MeshManagerES3* gMeshManagerES3 = MeshManagerES3::GetSingletonPtr();
    for(int m=0; m<this->Meshes.size(); m++) {
        gMeshManagerES3->Get(this->Meshes[m]).Scale(scale);
    }

    this->ModelMatrix = glm::scale(this->ModelMatrix, scale);
}

void ModelES3::SetMeshShaderPipeline(unsigned int mesh_key, const std::function<void(MeshES3* self, ShaderES3& shader)>& shaderPipeline) {
    MeshManagerES3* gMeshManagerES3 = MeshManagerES3::GetSingletonPtr();
    gMeshManagerES3->Get(this->Meshes[mesh_key]).SetShaderPipeline(shaderPipeline);
}


#endif