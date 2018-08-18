#include "DynamicShader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "..\GraphicsAssert.h"

#include <GL\glew.h>
#include <glm\glm.hpp>


DynamicShader::DynamicShader(const char* vertexFilepath, const char* fragmentFilepath)
	:Shader()
{
	loadShaders(vertexFilepath, fragmentFilepath);
}

DynamicShader::~DynamicShader()
{
}

void DynamicShader::setBooleanUniform(const std::string& name, bool v0)
{
	setFloatUniform(name, (float)v0);
}

void DynamicShader::setIntUniform(const std::string& name, int v0)
{
	GLCall(glUniform1i(getUniformLocation(name), v0));
}
void DynamicShader::setFloatUniform(const std::string& name, float v0)
{
	GLCall(glUniform1f(getUniformLocation(name), v0));
}
void DynamicShader::setVec2Uniform(const std::string & name, const glm::vec2 & vec0)
{
	GLCall(glUniform2f(getUniformLocation(name), vec0.x, vec0.y));
}
void DynamicShader::setVec3Uniform(const std::string& name, const glm::vec3& vec0)
{
	GLCall(glUniform3f(getUniformLocation(name), vec0.x, vec0.y, vec0.z));
}
void DynamicShader::setMatrix4fUniform(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int DynamicShader::getUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_programID, name.c_str()));
	if (location == -1)
	{
		std::cout << "[SGE][Shader][Dynamic] Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}

	m_UniformLocationCache[name] = location;
	return location;
}