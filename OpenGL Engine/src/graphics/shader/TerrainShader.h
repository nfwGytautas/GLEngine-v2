#pragma once

#include "Shader.h"

class Camera;
class Light;

class TerrainShader : public Shader
{
public:
	TerrainShader();
	~TerrainShader();

	void LoadTransformationMatrix(glm::mat4 matrix);
	void LoadProjectionMatrix(glm::mat4 matrix);
	void LoadViewMatrix(Camera& camera);
	void LoadLight(Light& light);
	void LoadShineVariables(float damper, float reflectivity);
protected:
	void BindAttributes() override;
	void GetAllUniformLocations() override;
private:
	static const char* VERTEX_FILE;
	static const char* FRAGMENT_FILE;

	int m_location_transformationMatrix;
	int m_location_projectionMatrix;
	int m_location_viewMatrix;
	int m_location_lightPosition;
	int m_location_lightColor;
	int m_location_shineDamper;
	int m_location_reflectivity;
};

