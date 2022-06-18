#include "OGLProgram.h"
#include <glad/glad.h>
#include <vector>
#include <fstream>

static std::string ReadFile(const std::string& InFilePath)
{
    std::ifstream InputStream(InFilePath, std::ios::ate);
    if (!InputStream.is_open()) {
        DIE("Impossible to open file");
    }

    size_t Size = InputStream.tellg();
    if (Size == -1) {
        DIE("Impossible read file size");
    }

    std::string Result;
    Result.resize(Size);

    InputStream.seekg(0, std::ios::beg);
    InputStream.read(&Result[0], Size);

    InputStream.close();
    return Result;
}

static GLuint CreateShader(const std::string& InFilePath, GLenum InShaderType)
{
    std::string ShaderStr = ReadFile(InFilePath);
    const char* ShaderSource = ShaderStr.c_str();
    
    GLuint ShaderId = glCreateShader(InShaderType);
    glShaderSource(ShaderId, 1, &ShaderSource, NULL);
    glCompileShader(ShaderId);

    GLint Success;
    glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &Success);
    if (!Success)
    {   
        GLint MaxLogLength;
        glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &MaxLogLength);

        std::vector<GLchar> InfoLog(MaxLogLength);
        glGetShaderInfoLog(ShaderId, MaxLogLength, NULL, InfoLog.data());
        std::string LogStr(InfoLog.begin(), InfoLog.end());
        DIE(LogStr);
    }
    return ShaderId;
}

static GLuint CreateProgram(GLuint InVertId, GLuint InFragId)
{
    GLuint ProgramId = glCreateProgram();
    glAttachShader(ProgramId, InVertId);
    glAttachShader(ProgramId, InFragId);
    glLinkProgram(ProgramId);

    GLint Success;
    glGetProgramiv(ProgramId, GL_LINK_STATUS, &Success);
    if (!Success)
    {   
        GLint MaxLogLength;
        glGetProgramiv(ProgramId, GL_INFO_LOG_LENGTH, &MaxLogLength);

        std::vector<GLchar> InfoLog(MaxLogLength);
        glGetProgramInfoLog(ProgramId, MaxLogLength, NULL, InfoLog.data());
        std::string LogStr(InfoLog.begin(), InfoLog.end());
        DIE(LogStr);
    }

    glDeleteShader(InVertId);
    glDeleteShader(InFragId);
    return ProgramId;
}


OGLProgram::OGLProgram(const std::string& InVertShaderPath, const std::string& InFragShaderPath)
{
    GLuint VertexShaderId = CreateShader(InVertShaderPath, GL_VERTEX_SHADER);
    GLuint FragmeShaderId = CreateShader(InFragShaderPath, GL_FRAGMENT_SHADER);
    Id = CreateProgram(VertexShaderId, FragmeShaderId);
}

OGLProgram::~OGLProgram()
{
    glDeleteProgram(Id);
}

void OGLProgram::Bind()
{
    glUseProgram(Id);
}

void OGLProgram::SetUniform(const std::string& InName, float InValue)
{
    glUniform1f(glGetUniformLocation(Id, InName.c_str()), InValue);
}

void OGLProgram::SetUniform(const std::string& InName, const Color& InValue)
{
    GLint BaseColorLocation = glGetUniformLocation(Id, InName.c_str());
    const GLfloat* ColorPtr = (GLfloat*)&InValue;
    glUniform4fv(BaseColorLocation, 1, ColorPtr);
}

void OGLProgram::SetUniform(const std::string& InName, const glm::mat4& InValue)
{
    GLint Loc = glGetUniformLocation(Id, InName.c_str());
    glUniformMatrix4fv(Loc, 1, GL_FALSE, &InValue[0][0]);
}

void OGLProgram::SetUniform(const std::string& InName, const glm::vec3& InValue)
{
    GLint Loc = glGetUniformLocation(Id, InName.c_str());
    glUniform3fv(Loc, 1, &InValue[0]);
}