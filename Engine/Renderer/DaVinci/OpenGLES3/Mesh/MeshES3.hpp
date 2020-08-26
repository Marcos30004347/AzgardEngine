#include "definitions.hpp"

#ifndef MESHES3_H
#define MeshES3_H

#ifdef OPENGLES3_API

#include <GL/glew.h>

#include "Renderer/Model.hpp"

#include "DataStructures/Model.hpp"

class MeshES3 {
    public:

    const char* Name;

    GLuint VertexArrayBuffer;
    GLuint IndexBuffer;

    size_t NumIndices;

    MeshES3();
    MeshES3(MeshData data);

    void Draw();

    ~MeshES3();
    void DestroyBuffers();
};


#endif
#endif