#ifndef GLES3_SHADER_H
#define GLES3_SHADER_H

#include <GL/glew.h>
#include "glm/glm.hpp"

class GLES3_Shader {
    private:
    GLuint _vertex_shader;
    GLuint _fragment_shader;
    GLuint _shader_program;

    public:
    GLES3_Shader(const char* vertexShaderSrc, const char* fragmentShaderSrc);
    ~GLES3_Shader();

    void use();
    unsigned int get_id();

    void set_uniform_matrix4(const char* name, float* data);
    void set_uniform_matrix4_array(const char* name, float* data, unsigned int count);
    void set_uniform_vector4(const char* name, float x, float y, float z, float a);
    void set_uniform_vector3(const char* name, float x, float y, float z);
    void set_uniform_vector2(const char* name, float x, float y);
    void set_uniform_int_array(const char* name, int* array, int count);
    void set_uniform_float_array(const char* name, float* array, int count);
    void set_uniform_vector2_array(const char* name, glm::vec2* array, int count);
    
    void set_uniform_float(const char* name, float x);
    void set_uniform_int(const char* name, int data);
};

#endif