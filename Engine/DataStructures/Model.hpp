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

struct BoundingBox {
    float p0x, p0y, p0z;
    float p1x, p1y, p1z;
};

struct ModelData {
    const char* name;
    std::vector<MeshData> meshes;
    BoundingBox boundings;
    float centerX, centerY, centerZ;
};

#endif