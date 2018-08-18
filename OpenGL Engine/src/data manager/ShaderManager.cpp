#include "ShaderManager.h"
#include <iostream>

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	for (auto it : m_shaders)
	{
		delete it.second;
	}
}

DynamicShader* ShaderManager::getShader(std::string shaderName)
{
	if (m_shaders.find(shaderName) != m_shaders.end())
	{
		return m_shaders[shaderName];
	}
	std::cout << "[SGE] Returning nullptr! " << shaderName << std::endl;
	return nullptr;
}

void ShaderManager::addShader(std::string shaderName, std::string vertexShaderPath, std::string fragmentShaderPath)
{
	if (m_shaders.find(shaderName) == m_shaders.end())
	{
		m_shaders[shaderName] = new DynamicShader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
	}
}