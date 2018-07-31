#pragma once

#include <string>

#include <glm\glm.hpp>

class Shader
{
protected:
	Shader();
	virtual ~Shader();

	void bindAttributes();
	//If a shader is dynamic just leave this function empty
	virtual void getAllUniformLocations() {};

	void bindAttribute(unsigned int attribute, std::string variableName);
	int getUniformLocation(std::string uniformName);
protected:
	void loadShaders(std::string vertexPath, std::string fragmentPath);
public:
	void bind();
	void unbind();

	void setIntUniform(int location, int value);
	void setFloatUniform(int location, float value);
	void setVec2Uniform(int location, glm::vec2 vector);
	void setVec3Uniform(int location, glm::vec3 vector);
	void setBooleanUniform(int location, bool value);
	void setMatrix4fUniform(int location, glm::mat4 matrix);
protected:
	unsigned int m_programID;
};

