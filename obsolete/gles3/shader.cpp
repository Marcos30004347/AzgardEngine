#include "shader.h"
#include "stdio.h"
#include "fstream"
#include "sstream"
#include<iostream>

GLES3_Shader::GLES3_Shader(const char* vertexShaderSrc, const char* fragmentShaderSrc) {
    const char* vertexSource;
    const char* fragmentSource;
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.open(vertexShaderSrc);
    fShaderFile.open(fragmentShaderSrc);

    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();		
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();

    vertexCode   = vShaderStream.str();
    fragmentCode = fShaderStream.str();
    // printf("%s\n", vertexCode.c_str());
    // printf("%s\n", fragmentCode.c_str());
    vertexSource = vertexCode.c_str();
    fragmentSource = fragmentCode.c_str();

    this->_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->_vertex_shader, 1, &vertexSource, NULL);
    glCompileShader(this->_vertex_shader);

    GLint vertex_shader_status;
    glGetShaderiv(this->_vertex_shader, GL_COMPILE_STATUS, &vertex_shader_status);

    char buff[512];

    if(!vertex_shader_status) {
        glGetShaderInfoLog(this->_vertex_shader, 512, nullptr, buff);
        printf("%s\n", buff);
    }

    char vertexLogBuffer[512];
    this->_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->_fragment_shader, 1, &fragmentSource, NULL);
    glCompileShader(this->_fragment_shader);
    GLint fragment_shader_status;
    glGetShaderiv(this->_fragment_shader, GL_COMPILE_STATUS, &fragment_shader_status);

    if(!fragment_shader_status) {
        glGetShaderInfoLog(this->_fragment_shader, 512, nullptr, buff);
        printf("%s\n", buff);
    }
    char fragmentLogBuffer[512];
    glGetShaderInfoLog(this->_fragment_shader, 512, NULL, fragmentLogBuffer);

    this->_shader_program = glCreateProgram();
    glAttachShader(this->_shader_program, this->_vertex_shader);
    glAttachShader(this->_shader_program, this->_fragment_shader);
    glLinkProgram(this->_shader_program);
    GLint program_link_status;
    glGetProgramiv(this->_shader_program, GL_LINK_STATUS, &program_link_status);

    if(!program_link_status) {
        glGetProgramInfoLog(this->_shader_program, 512, nullptr, buff);
        printf("%s\n", buff);
    }
}

void GLES3_Shader::set_uniform_matrix4(const char* name, float* data) {
    unsigned int location = glGetUniformLocation(this->_shader_program, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, data);
}

void GLES3_Shader::set_uniform_matrix4_array(const char* name, float* data, unsigned int  count) {
    unsigned int location = glGetUniformLocation(this->_shader_program, name);
    glUniformMatrix4fv(location, count, GL_FALSE, data);
}

void GLES3_Shader::set_uniform_vector4(const char* name, float x, float y, float z, float a) {
    unsigned int location = glGetUniformLocation(this->_shader_program, name);
    glUniform4f(location, x, y, z, a); 
}

void GLES3_Shader::set_uniform_vector3(const char* name, float x, float y, float z) {
    unsigned int location = glGetUniformLocation(this->_shader_program, name);
    glUniform3f(location, x, y, z); 
}

void GLES3_Shader::set_uniform_vector2(const char* name, float x, float y) {
    unsigned int location = glGetUniformLocation(this->_shader_program, name);
    glUniform2f(location, x, y); 
}

void GLES3_Shader::set_uniform_float(const char* name, float x) {
    unsigned int location = glGetUniformLocation(this->_shader_program, name);
    glUniform1f(location, x);   
}

void GLES3_Shader::set_uniform_int(const char* name, int x) {
    unsigned int location = glGetUniformLocation(this->_shader_program, name);
    glUniform1i(location, x);    
}

void GLES3_Shader::set_uniform_int_array(const char* name, int* array, int count) {
    unsigned int location = glGetUniformLocation(this->_shader_program, name);
    glUniform1iv(location, count, array);  
}
void GLES3_Shader::set_uniform_float_array(const char* name, float* array, int count) {
    unsigned int location = glGetUniformLocation(this->_shader_program, name);
    glUniform1fv(location, count, array);  
}

void GLES3_Shader::set_uniform_vector2_array(const char* name, glm::vec2* array, int count) {
    unsigned int location = glGetUniformLocation(this->_shader_program, name);
    glUniform2fv(location, count, &array[0][0]);  
}

void GLES3_Shader::use() {
    glUseProgram(this->_shader_program);
}

unsigned int GLES3_Shader::get_id() {
    return this->_shader_program;
}

GLES3_Shader::~GLES3_Shader() {

}