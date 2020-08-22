
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


struct StaticVertice {
    float x, y, z;
    float uv_x, uv_y;
    float norm_x, norm_y, norm_z;
};

class StaticMeshES3 {
    public:

    GLuint VertexArrayBuffer;
    GLuint IndexBuffer;
    glm::mat4 ModelMatrix;

    StaticMeshES3(StaticVertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices);
    ~StaticMeshES3();
};

class UnindexedStaticMeshES3 {
    public:

    GLuint VertexArrayBuffer;
    glm::mat4 ModelMatrix;

    UnindexedStaticMeshES3(StaticVertice* vertex_array_buffer, size_t num_vertices);
    ~UnindexedStaticMeshES3();
};