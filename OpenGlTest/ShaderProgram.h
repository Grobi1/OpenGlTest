#pragma once
#include <gl/GL.h>
#include <gl/glext.h>
#include "Mat4.h"

class ShaderProgram
{
public:
	ShaderProgram();
	void Load(std::string vertexShaderPath, std::string fragmentShaderPath);
	void Use();
	void SetMatrix(std::string name, Mat4 mat);
private:
	void PrintShaderError(GLuint id);
	GLuint _id;
};

