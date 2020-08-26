#ifndef MODEL_H
#define MODEL_H

#include<vector>

struct VerticeData {
    float posX, posY, posZ;
    float uvX, uvY;
    float normX, normY, normZ;
};

struct MeshData {
    const char* name;

    std::vector<unsigned int> indices;
    std::vector<VerticeData> vertices;
};

struct ModelData {
    const char* name;
    std::vector<MeshData> meshes;
};

#endif