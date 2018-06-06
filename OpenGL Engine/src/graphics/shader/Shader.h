#pragma once

#include <string>

class Shader
{
protected:
	Shader(std::string vertexFile, std::string fragmentFile);
	virtual ~Shader();

	//If a shader is dynamic just leave this function empty
	virtual void BindAttributes() {};
	void bindAttribute(unsigned int attribute, std::string variableName);
private:
	unsigned int loadShaders(std::string vertexPath, std::string fragmentPath);
public:
	void Bind();
	void Unbind();
private:
	unsigned int m_programID;
};

