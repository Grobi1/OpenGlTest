#include <Windows.h>
#include <fstream>
#include <sstream>
#include "ShaderProgram.h"
#include <vector>
#include <iostream>
#include "OpenGl.h"

//--------------------------------------------------------------
ShaderProgram::ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    _id = 0;
    Load(vertexShaderPath, fragmentShaderPath);
}

//--------------------------------------------------------------
ShaderProgram::~ShaderProgram()
{
    GL_CALL(glDeleteProgram(_id));
}

//--------------------------------------------------------------
void ShaderProgram::Load(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    //Shaders
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.open(vertexShaderPath);
    fShaderFile.open(fragmentShaderPath);
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();
    std::string vertexCode = vShaderStream.str();
    std::string fragmentCode = fShaderStream.str();
    const char* vertexCodeC = vertexCode.c_str();
    const char* fragmentCodeC = fragmentCode.c_str();


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GL_CALL(glShaderSource(vertexShader, 1, &vertexCodeC, NULL));
    GL_CALL(glCompileShader(vertexShader));
    PrintShaderError(vertexShader, "Vertex");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GL_CALL(glShaderSource(fragmentShader, 1, &fragmentCodeC, NULL));
    GL_CALL(glCompileShader(fragmentShader));
    PrintShaderError(fragmentShader, "Fragment");

    _id = glCreateProgram();

    GL_CALL(glAttachShader(_id, vertexShader));
    GL_CALL(glAttachShader(_id, fragmentShader));
    GL_CALL(glLinkProgram(_id));

    GL_CALL(glDeleteShader(vertexShader));
    GL_CALL(glDeleteShader(fragmentShader));
}

//--------------------------------------------------------------
void ShaderProgram::SetUniformMat4(std::string name, Mat4 mat)
{
    GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, mat.Data()));
}

//--------------------------------------------------------------
int32_t ShaderProgram::GetUniformLocation(std::string name)
{
    int location = glGetUniformLocation(_id, name.c_str());
    if (location < 0)
        std::cout << "Error: Uniform (name=" << name << ") does not exists" << std::endl;
    return location;
}

//--------------------------------------------------------------
void ShaderProgram::Bind()
{
    GL_CALL(glUseProgram(_id));
}


//--------------------------------------------------------------
void ShaderProgram::Unbind()
{
    GL_CALL(glUseProgram(0));
}

//--------------------------------------------------------------
void ShaderProgram::PrintShaderError(uint32_t id, std::string name)
{
    GLint isCompiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

        glDeleteShader(id);

        std::cout << "Error:  Shader (name=" << name << ", id=" << id << ")" << std::endl;
        for (GLchar i : errorLog)
            std::cout << i;
        return;
    }
}


