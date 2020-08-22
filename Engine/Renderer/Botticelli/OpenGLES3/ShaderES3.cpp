#include "ShaderES3.hpp"
#include <string>

ShaderES3::ShaderES3(const char* vertexShaderSrc, const char* fragmentShaderSrc) {
    //TODO: dont know if vertex and fragment shaders can be destroyed here after the program compilation

    this->VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->VertexShader, 1, &vertexShaderSrc, NULL);
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
    glShaderSource(this->FragmentShader, 1, &fragmentShaderSrc, NULL);
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
}

void ShaderES3::UniformMatrix4(const char* name, float* data) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, data);
}

void ShaderES3::UniformMatrix4Array(const char* name, float* data, unsigned int  count) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    glUniformMatrix4fv(location, count, GL_FALSE, data);
}

void ShaderES3::UniformVector4(const char* name, float x, float y, float z, float a) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    glUniform4f(location, x, y, z, a); 
}

void ShaderES3::UniformVector3(const char* name, float x, float y, float z) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    glUniform3f(location, x, y, z); 
}

void ShaderES3::UniformVector2(const char* name, float x, float y) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    glUniform2f(location, x, y); 
}

void ShaderES3::UniformFloat(const char* name, float x) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    glUniform1f(location, x);   
}

void ShaderES3::UniformInt(const char* name, int x) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    glUniform1i(location, x);    
}

void ShaderES3::UniformIntArray(const char* name, int* array, int count) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    glUniform1iv(location, count, array);  
}
void ShaderES3::UniformFloatArray(const char* name, float* array, int count) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    glUniform1fv(location, count, array);  
}

void ShaderES3::UniformVector2Array(const char* name, glm::vec2* array, int count) {
    unsigned int location = glGetUniformLocation(this->Shader, name);
    glUniform2fv(location, count, &array[0][0]);  
}

void ShaderES3::Use() {
    glUseProgram(this->Shader);
}

ShaderES3::~ShaderES3() {
    glDeleteShader(this->Shader);
    glDeleteShader(this->VertexShader);
    glDeleteShader(this->FragmentShader);
}