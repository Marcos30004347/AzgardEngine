#include "definitions.hpp"

#ifndef STATICMESHES3_H
#ifdef OPENGLES3_API

#define STATICMESHES3_H

#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Renderer/Mesh.hpp"


class StaticMeshES3 {
    public:

    GLuint VertexArrayBuffer;
    GLuint IndexBuffer;
    glm::mat4 ModelMatrix;

    StaticMeshES3();
    StaticMeshES3(StaticVertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices);

    ~StaticMeshES3();
    void Destroy();
};


#endif
#endif