#pragma once

#include <string>

//TODO: Create my own math library
#include <glm\glm.hpp>

class Shader
{
protected:
	Shader();
	virtual ~Shader();

	//If a shader is dynamic just leave this function empty
	virtual void BindAttributes() {};
	//If a shader is dynamic just leave this function empty
	virtual void GetAllUniformLocations() {};

	void bindAttribute(unsigned int attribute, std::string variableName);
	int getUniformLocation(std::string uniformName);
protected:
	void loadShaders(std::string vertexPath, std::string fragmentPath);
public:
	void Bind();
	void Unbind();

	void SetFloatUniform(int location, float value);
	void SetVec3Uniform(int location, glm::vec3 vector);
	void SetBooleanUniform(int location, bool value);
	void SetMatrix4fUniform(int location, glm::mat4 matrix);
private:
	unsigned int m_programID;
};

