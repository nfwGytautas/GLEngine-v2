#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "..\FrameworkAssert.h"
#include "..\gtypes\gTypes.h"

Shader::Shader()
{
}
Shader::~Shader()
{
	GLCall(glDeleteProgram(m_programID));
}

void Shader::bindAttributes()
{
	bindAttribute(AttributeLocation::Position, "position");
	bindAttribute(AttributeLocation::UVs, "textureCoords");
	bindAttribute(AttributeLocation::Normal, "normal");
}

void Shader::bindAttribute(unsigned int attribute, std::string variableName)
{
	GLCall(glBindAttribLocation(m_programID, attribute, variableName.c_str()));
}

int Shader::getUniformLocation(std::string uniformName)
{
	GLCall(int location = glGetUniformLocation(m_programID, uniformName.c_str()));
	if (location == -1)
		std::cout << "[Engine][Shader] Warning: uniform '" << uniformName << "' doesn't exist!" << std::endl;
	return location;
}

void Shader::loadShaders(std::string vertexPath, std::string fragmentPath)
{
	std::string fragmentSource;
	std::string vertexSource;

	std::ifstream vertexFile(vertexPath);
	if (vertexFile.is_open()) {
		vertexSource.assign((std::istreambuf_iterator<char>(vertexFile)),
			(std::istreambuf_iterator<char>()));
	}
	else {
		std::cout << "[Engine][Shader] Impossible to read " << vertexPath << std::endl;
		return;
	}
	vertexFile.close();
	// Read the Fragment Shader code from the file
	std::ifstream fragmentFile(fragmentPath);
	if (fragmentFile.is_open()) {
		fragmentSource.assign((std::istreambuf_iterator<char>(fragmentFile)),
			(std::istreambuf_iterator<char>()));
	}
	else {
		std::cout << "[Engine][Shader] Impossible to read " << fragmentPath << std::endl;
		return;
	}
	fragmentFile.close();


	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	std::cout << "[Engine][Shader] Compiling [VERTEX] shader \n";

	char const * VertexSourcePointer = vertexSource.c_str();
	GLCall(glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL));
	GLCall(glCompileShader(VertexShaderID));

	// Check Vertex Shader
	GLCall(glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result));
	GLCall(glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength));
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		GLCall(glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]));
		std::cout << "[Engine][Shader] " << &VertexShaderErrorMessage[0] << std::endl;
	}



	// Compile Fragment Shader
	std::cout << "[Engine][Shader] Compiling [FRAGMENT] shader \n";

	char const * FragmentSourcePointer = fragmentSource.c_str();
	GLCall(glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL));
	GLCall(glCompileShader(FragmentShaderID));

	// Check Fragment Shader
	GLCall(glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result));
	GLCall(glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength));
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		GLCall(glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]));
		std::cout << "[Engine][Shader] " << &FragmentShaderErrorMessage[0] << std::endl;
	}



	// Link the program
	std::cout << "[Engine][Shader] Linking program \n";
	m_programID = (unsigned int)glCreateProgram();
	GLCall(glAttachShader(m_programID, VertexShaderID));
	GLCall(glAttachShader(m_programID, FragmentShaderID));
	bindAttributes();
	GLCall(glLinkProgram(m_programID));
	GLCall(glValidateProgram(m_programID));
	getAllUniformLocations();

	// Check the program
	GLCall(glGetProgramiv(m_programID, GL_LINK_STATUS, &Result));
	GLCall(glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &InfoLogLength));
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		GLCall(glGetProgramInfoLog(m_programID, InfoLogLength, NULL, &ProgramErrorMessage[0]));
		std::cout << "[Engine][Shader] " << &ProgramErrorMessage[0] << std::endl;
	}


	GLCall(glDetachShader(m_programID, VertexShaderID));
	GLCall(glDetachShader(m_programID, FragmentShaderID));

	GLCall(glDeleteShader(VertexShaderID));
	GLCall(glDeleteShader(FragmentShaderID));

}

void Shader::bind()
{
	GLCall(glUseProgram(m_programID));
}
void Shader::unbind()
{
	GLCall(glUseProgram(0));
}

void Shader::setIntUniform(int location, int value)
{
	GLCall(glUniform1i(location, value));
}
void Shader::setFloatUniform(int location, float value)
{
	GLCall(glUniform1f(location, value));
}
void Shader::setVec3Uniform(int location, glm::vec3 vector)
{
	GLCall(glUniform3f(location, vector.x, vector.y, vector.z));
}
void Shader::setBooleanUniform(int location, bool value)
{
	float result = 0;
	if (value)
	{
		result = 1;
	}	
	setFloatUniform(location, value);
}
void Shader::setMatrix4fUniform(int location, glm::mat4 matrix)
{
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}