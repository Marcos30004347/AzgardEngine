#include "definitions.hpp"

#ifndef MESHES3_H
#define MeshES3_H

#ifdef OPENGLES3_API

#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Renderer/Mesh.hpp"

#include "DataStructures/Vertice.hpp"

class MeshES3 {
    public:

    GLuint VertexArrayBuffer;
    GLuint IndexBuffer;
    glm::mat4 ModelMatrix;
    size_t num_indices;

    MeshES3();
    MeshES3(Vertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices);

    ~MeshES3();
    void Destroy();
};


#endif
#endif