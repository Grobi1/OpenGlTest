#pragma once
#include "Mat4.h"

class ShaderProgram
{
public:
	ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
	~ShaderProgram();
	void Bind();
	void Unbind();
	void SetUniformMat4(std::string name, Mat4 mat);
private:
	int32_t GetUniformLocation(std::string name);
	void Load(std::string vertexShaderPath, std::string fragmentShaderPath);
	void CreateProgram();
	void PrintShaderError(uint32_t id, std::string name);
	uint32_t _id;
};
