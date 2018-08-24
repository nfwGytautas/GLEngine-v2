#pragma once
#include <unordered_map>
#include <string>
#include "..\..\graphics\shader\DynamicShader.h"
#include "..\..\graphics\gtypes\gTypes.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	DynamicShader* getShader(std::string shaderName);
	void addShader(std::string shaderName, std::string vertexShaderPath, std::string fragmentShaderPath);

private:
	std::unordered_map<std::string, DynamicShader*> m_shaders;
};