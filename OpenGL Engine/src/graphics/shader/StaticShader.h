#pragma once

#include "Shader.h"

class Camera;

class StaticShader : public Shader
{
public:
	StaticShader();
	~StaticShader();

	void LoadTransformationMatrix(glm::mat4 matrix);
	void LoadProjectionMatrix(glm::mat4 matrix);
	void LoadViewMatrix(Camera& camera);
protected:
	void BindAttributes() override; 
	void GetAllUniformLocations() override;
private:
	static const char* VERTEX_FILE;
	static const char* FRAGMENT_FILE;

	int m_location_transformationMatrix;
	int m_location_projectionMatrix;
	int m_location_viewMatrix;
};

