#pragma once
#include "Mat4.h"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void Load(std::string vertexShaderPath, std::string fragmentShaderPath);
	void Use();
	void SetMatrix(std::string name, Mat4 mat);
private:
	void PrintShaderError(uint32_t id);
	uint32_t _id;
};

