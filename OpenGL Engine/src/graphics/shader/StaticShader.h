#pragma once

#include "Shader.h"

class StaticShader : public Shader
{
public:
	StaticShader();
	~StaticShader();

	void LoadTransformationMatrix(glm::mat4 matrix);
protected:
	void BindAttributes() override; 
	void GetAllUniformLocations() override;
private:
	static const char* VERTEX_FILE;
	static const char* FRAGMENT_FILE;

	int m_location_transformationMatrix;
};

