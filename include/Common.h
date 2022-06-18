#pragma once

#pragma region EXCEPTIONAL FLOW
#include <stdexcept>
#include <iostream>

#define DIE_ON_ERROR(VALUE, MSG) if(VALUE == 0) { std::cout << MSG << "\n"; throw std::runtime_error(MSG); }
//#define DIE_ON_ERROR(VALUE, MSG) if(VALUE == 0) { std::cout << MSG << "\n"; exit(VALUE); }
#define DIE_ON_NULL(VALUE, MSG) if(VALUE == NULL) { std::cout << MSG << "\n"; throw std::runtime_error(MSG); }
#define DIE(MSG) { std::cout << MSG << "\n"; throw std::runtime_error(MSG); }
#pragma endregion

#pragma region OGL
typedef unsigned int GLuint;
typedef unsigned int GLenum;
class OGLTexture;
class OGLProgram;
#pragma endregion

struct Color {
    float R;
    float G;
    float B;
    float A;
};