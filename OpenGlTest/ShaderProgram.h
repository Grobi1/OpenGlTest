#pragma once
#include <gl/GL.h>
#include <gl/glext.h>


class ShaderProgram
{
public:
	ShaderProgram();
	void Load(std::string vertexShaderPath, std::string fragmentShaderPath);
	void Use();
private:
	GLuint _id;
};

