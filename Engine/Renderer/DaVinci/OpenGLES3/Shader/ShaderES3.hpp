#include "definitions.hpp"

#ifndef SHADERES3_H
#ifdef OPENGLES3_API

#define SHADERES3_H

#include "Renderer/Shader.hpp"
#include <GL/glew.h>
#include "glm/glm.hpp"

class ShaderES3 {
    private:
    GLuint VertexShader;
    GLuint FragmentShader;
    GLuint Shader;

    public:
    ShaderES3();
    ShaderES3(ShaderData& data);

    void Destroy();
    ~ShaderES3();

    void Use();
    inline unsigned int GetProgram() { return this->Shader; }

    void UniformMatrix4(const char* name, glm::mat4& data);
    void UniformMatrix4Array(const char* name, std::vector<glm::mat4>& values);
    void UniformVector4(const char* name, glm::vec4 vec);
    void UniformVector3(const char* name, glm::vec3 vec);
    void UniformVector2(const char* name, glm::vec2 vec);
    void UniformIntArray(const char* name, std::vector<int>& values);
    void UniformFloatArray(const char* name, std::vector<float>& values);
    void UniformVector2Array(const char* name, std::vector<glm::vec2>& array);
    void UniformFloat(const char* name, float x);
    void UniformInt(const char* name, int data);
};

#endif
#endif