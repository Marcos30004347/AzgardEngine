#include <vector>

#include "DataStructures/Vertice.hpp"

using ObjVertices = std::vector<Vertice>;
using ObjIndices = std::vector<unsigned int>;


struct ObjMesh {
    const char* name;
    ObjIndices indices;
    ObjVertices vertices;
};

using ObjMeshes = std::vector<ObjMesh>;

struct ObjModel {
    const char* name;
    ObjMeshes meshes;
};

ObjModel ParseObj(const char* src);

