#include "Shader.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\FrameworkAssert.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader(std::string vertexFile, std::string fragmentFile)
{
	m_programID = loadShaders(vertexFile, fragmentFile);
}
Shader::~Shader()
{
}

void Shader::bindAttribute(unsigned int attribute, std::string variableName)
{
	GLCall(glBindAttribLocation(m_programID, attribute, variableName.c_str()));
}

unsigned int Shader::loadShaders(std::string vertexPath, std::string fragmentPath)
{
	unsigned int ProgramID;

	std::string fragmentSource;
	std::string vertexSource;

	std::ifstream vertexFile(vertexPath);
	if (vertexFile.is_open()) {
		vertexSource.assign((std::istreambuf_iterator<char>(vertexFile)),
			(std::istreambuf_iterator<char>()));
	}
	else {
		std::cout << "[Engine][Shader] Impossible to read " << vertexPath << std::endl;
		return 0;
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
		return 0;
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
	ProgramID = (unsigned int)glCreateProgram();
	GLCall(glAttachShader(ProgramID, VertexShaderID));
	GLCall(glAttachShader(ProgramID, FragmentShaderID));
	BindAttributes();
	GLCall(glLinkProgram(ProgramID));

	// Check the program
	GLCall(glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result));
	GLCall(glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength));
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		GLCall(glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]));
		std::cout << "[Engine][Shader] " << &ProgramErrorMessage[0] << std::endl;
	}


	GLCall(glDetachShader(ProgramID, VertexShaderID));
	GLCall(glDetachShader(ProgramID, FragmentShaderID));

	GLCall(glDeleteShader(VertexShaderID));
	GLCall(glDeleteShader(FragmentShaderID));

	return ProgramID;
}

void Shader::Bind()
{
	GLCall(glUseProgram(m_programID));
}
void Shader::Unbind()
{
	GLCall(glUseProgram(0));
}
