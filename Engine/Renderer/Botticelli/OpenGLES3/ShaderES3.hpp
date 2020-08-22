#ifndef GLES3_SHADER_H
#define GLES3_SHADER_H

#include <GL/glew.h>
#include "glm/glm.hpp"

class ShaderES3 {
    private:
    GLuint VertexShader;
    GLuint FragmentShader;
    GLuint Shader;

    public:
    ShaderES3(const char* vertexShaderCode, const char* fragmentShaderCode);
    ~ShaderES3();

    void Use();
    inline unsigned int GetProgram() { return this->Shader; }

    void UniformMatrix4(const char* name, float* data);
    void UniformMatrix4Array(const char* name, float* data, unsigned int count);
    void UniformVector4(const char* name, float x, float y, float z, float a);
    void UniformVector3(const char* name, float x, float y, float z);
    void UniformVector2(const char* name, float x, float y);
    void UniformIntArray(const char* name, int* array, int count);
    void UniformFloatArray(const char* name, float* array, int count);
    void UniformVector2Array(const char* name, glm::vec2* array, int count);
    void UniformFloat(const char* name, float x);
    void UniformInt(const char* name, int data);
};

#endif