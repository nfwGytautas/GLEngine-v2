#pragma once
#include "Shader.h"

#include <string>
#include <unordered_map>

//Unlike a static shader this shader doesn't store uniform locations, rather it uses a caching method thus making it a lot more versitile
class DynamicShader : public Shader
{
public:
	DynamicShader(const char* vertexFilepath, const char* fragmentFilepath);
	~DynamicShader();

public:
	void setBooleanUniform(const std::string& name, bool v0);
	void setIntUniform(const std::string& name, int v0);
	void setFloatUniform(const std::string& name, float v0);
	void setVec3Uniform(const std::string& name, const glm::vec3& vec0);
	void setMatrix4fUniform(const std::string& name, const glm::mat4& m0);
private:
	std::unordered_map<std::string, int> m_UniformLocationCache;
private:
	int getUniformLocation(const std::string& name);
};