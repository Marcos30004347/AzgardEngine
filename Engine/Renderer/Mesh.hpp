#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "DataStructures/Identifier.hpp"

struct StaticVertice {
    float x, y, z;
    float uv_x, uv_y;
    float norm_x, norm_y, norm_z;
};


struct StaticMesh {
    Identifier id;
};




#endif