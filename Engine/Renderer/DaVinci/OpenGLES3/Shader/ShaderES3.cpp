#include "definitions.hpp"
#ifdef OPENGLES3_API

#include "ShaderES3.hpp"
#include <string>
#include <assert.h>

ShaderES3::ShaderES3() {}

ShaderES3::ShaderES3(ShaderData& data) {
    //TODO: dont know if vertex and fragment shaders can be destroyed here after the program compilation

    this->VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->VertexShader, 1, &data.vertexShaderSrc, NULL);
    glCompileShader(this->VertexShader);

    GLint vertex_shader_status;
    glGetShaderiv(this->VertexShader, GL_COMPILE_STATUS, &vertex_shader_status);

    char buff[512];

    if(!vertex_shader_status) {
        glGetShaderInfoLog(this->VertexShader, 512, nullptr, buff);
        printf("%s\n", buff);
    }

    char vertexLogBuffer[512];
    this->FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->FragmentShader, 1, &data.pixelShaderSrc, NULL);
    glCompileShader(this->FragmentShader);

    GLint fragment_shader_status;
    glGetShaderiv(this->FragmentShader, GL_COMPILE_STATUS, &fragment_shader_status);

    if(!fragment_shader_status) {
        glGetShaderInfoLog(this->FragmentShader, 512, nullptr, buff);
        printf("%s\n", buff);
    }
    char fragmentLogBuffer[512];
    glGetShaderInfoLog(this->FragmentShader, 512, NULL, fragmentLogBuffer);

    this->Shader = glCreateProgram();
    glAttachShader(this->Shader, this->VertexShader);
    glAttachShader(this->Shader, this->FragmentShader);
    glLinkProgram(this->Shader);

    GLint program_link_status;
    glGetProgramiv(this->Shader, GL_LINK_STATUS, &program_link_status);

    if(!program_link_status) {
        glGetProgramInfoLog(this->Shader, 512, nullptr, buff);
        printf("%s\n", buff);
    }

    if(this->Shader <= 0) {
        throw;
    }
}

void ShaderES3::UniformMatrix4(const char* name, glm::mat4& data) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    assert(location >= 0);
    glUniformMatrix4fv(location, 1, GL_FALSE, &data[0][0]);
}

void ShaderES3::UniformMatrix4Array(const char* name, std::vector<glm::mat4>& vec) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    assert(location >= 0);
    glUniformMatrix4fv(location, vec.size(), GL_FALSE, &vec[0][0][0]);
}

void ShaderES3::UniformVector4(const char* name, glm::vec4 vec) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    assert(location >= 0);
    glUniform4f(location, vec.x, vec.y, vec.z, vec.a);
}

void ShaderES3::UniformVector3(const char* name, glm::vec3 vec) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    assert(location >= 0);
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void ShaderES3::UniformVector2(const char* name, glm::vec2 vec) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    assert(location >= 0);
    glUniform2f(location, vec.x, vec.y);
}

void ShaderES3::UniformFloat(const char* name, float x) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    assert(location >= 0);
    glUniform1f(location, x);
}

void ShaderES3::UniformInt(const char* name, int x) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    assert(location >= 0);
    glUniform1i(location, x);
}

void ShaderES3::UniformIntArray(const char* name, std::vector<int>& values) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    assert(location >= 0);
    glUniform1iv(location, values.size(), values.data());
}
void ShaderES3::UniformFloatArray(const char* name, std::vector<float>& values) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    assert(location >= 0);
    glUniform1fv(location, values.size(), values.data());
}

void ShaderES3::UniformVector2Array(const char* name, std::vector<glm::vec2>& values) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    assert(location >= 0);
    glUniform2fv(location, values.size(), &values[0][0]);
}

void ShaderES3::Use() {
    glUseProgram(this->Shader);

}

ShaderES3::~ShaderES3() {}

void ShaderES3::Destroy() {
    // glDeleteShader(this->Shader);
    // glDeleteShader(this->VertexShader);
    // glDeleteShader(this->FragmentShader);
}

#endif