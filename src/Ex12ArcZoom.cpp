#pragma once
#include "Ex12ArcZoom.h"
#include <string>
#include <fstream>
#include "Common.h"
#include <iostream>
#include <glad/glad.h>
#include <vector>
#include <math.h>
#include "OGLProgram.h"
#define NUMBER_OF_VERTICES 16
#define M_PI 3.14159265358979323846

void Ex12ArcZoom::Start() 
{
    Program = new OGLProgram("resources/shaders/arczoomperspective.vert", 
                             "resources/shaders/arczoomperspective.frag");
    
    float radius = 0.5;
    std::vector<float> Vertices;
    for(double i = 0; i < 2 * M_PI; i += 2 * M_PI / NUMBER_OF_VERTICES){
    Vertices.push_back(cos(i) * radius);    //X coordinate
    Vertices.push_back(sin(i) * radius);    //Y coordinate
    Vertices.push_back(0.0);                //Z coordinate
    }
    float right = 0.5;
    float bottom = -0.5;
    float left = -0.5;
    float top = 0.5;
    std::vector<float> quad = 
    {
        //first triangle (upper right)
        right, bottom, 0,     1.0, -1.0,
        right, top,    0,     1.0,  1.0,
        left,  top,    0,    -1.0,  1.0,
        //second triangle (bottom left)
        //it can be made with only one triangle (see shader comment)
        left,  bottom, 0,    -1.0, -1.0,
        right, bottom, 0,     1.0, -1.0,
        left,  top,    0,    -1.0,  1.0
    };

    unsigned int glBuffer;

    //1. Create VAO
    glGenVertexArrays(1, &Vao);
    glBindVertexArray(Vao);

    //2. Create VBO to load data
    glGenBuffers(1, &Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, Vbo);

    //int DataSize = Vertices.size() * sizeof(float);
    int DataSize = quad.size() * sizeof(float);
    //glBufferData(GL_ARRAY_BUFFER, DataSize, Vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, DataSize, quad.data(), GL_STATIC_DRAW);
    //3. Link to Vertex Shader
    GLuint Location_0 = 0;
    glEnableVertexAttribArray(Location_0);
    glVertexAttribPointer(Location_0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    GLuint Location_1 = 1;
    glEnableVertexAttribArray(Location_1);
    glVertexAttribPointer(Location_1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    //4. Set Viewport
    glViewport(0, 0, 800, 800);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    Program->Bind();
    Zoom = 1;
}

void Ex12ArcZoom::Update(float InDeltaTime,float left, float up)
{
    glClear(GL_COLOR_BUFFER_BIT);
    Zoom += InDeltaTime * 0.25f;
    if (Zoom >= 10)
        Zoom = 1;

    Program->SetUniform("zoom", InDeltaTime);
    Program->SetUniform("side", left);
    Program->SetUniform("updown", up);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Ex12ArcZoom::Destroy()
{   
    glDeleteVertexArrays(1, &Vao);
    glDeleteBuffers(1, &Vbo);
    delete Program;
}
