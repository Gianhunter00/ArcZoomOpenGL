#pragma once
#include <string>
#include "Common.h"
#include <glm/glm.hpp>
class OGLProgram 
{
public:
    OGLProgram(const std::string& InVertShaderPath, const std::string& InFragShaderPath);
    ~OGLProgram();
    void Bind();
    void SetUniform(const std::string& InName, float InValue);
    void SetUniform(const std::string& InName, const Color& InValue);
    void SetUniform(const std::string& InName, const glm::mat4& InValue);
    void SetUniform(const std::string& InName, const glm::vec3& InValue);
//private:
public:
    GLuint Id;
};