#pragma once
#include "Common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Ex12ArcZoom
{
public:
    void Start();
    void Update(float InDeltaTime, float left, float up);
    void Destroy();
private:
    OGLProgram* Program;
    GLuint Vao;
    GLuint Vbo;
    GLuint Ebo;

    float Zoom;
};