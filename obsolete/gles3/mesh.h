#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class GLES3_Mesh {
    private:
    GLuint _vao;
    GLuint _ibo;
    GLuint _shader_id;

    glm::mat4 _model;
    glm::mat4 _view;
    glm::mat4 _projection;

    public:
    GLES3_Mesh(const char* path);
    ~GLES3_Mesh();

    void draw();

    glm::mat4 getModelMatrix () { return this->_model; }
    glm::mat4 getViewMatrix () { return this->_view; }
    glm::mat4 getProjectionMatrix () { return this->_projection; }

    void setModelMatrix (glm::mat4 model) { this->_model = model; }
    void setViewMatrix (glm::mat4 view) { this->_view = view; }
    void setProjectionMatrix (glm::mat4 projection) { this->_projection = projection; }
};