#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "DataStructures/Identifier.hpp"
#include "DataStructures/Model.hpp"


struct MeshHandle {
    Identifier id;
    const char* name;
};

struct ModelHandle {
    Identifier id;
    const char* name;

    std::vector<MeshHandle> meshes;
};




#endif