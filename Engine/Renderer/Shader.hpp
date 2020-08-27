#ifndef MATERIAL_RENDERER_H
#define MATERIAL_RENDERER_H

#include "DataStructures/Identifier.hpp"

struct ShaderData {
    const char* vertexShaderSrc;
    const char* pixelShaderSrc;
};

struct ShaderHandle {
    Identifier id;
};

#endif