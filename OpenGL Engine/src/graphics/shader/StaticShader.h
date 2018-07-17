#pragma once
#include "Shader.h"
class Entity;
class StaticShader : public Shader
{
public:
	StaticShader();
	~StaticShader();

	void loadTransformationMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewMatrix(const Entity& mEntity);
	void loadLight(Entity& mLight);
	void loadShineVariables(float damper, float reflectivity);
	void loadTileCount(unsigned int tilecount);
protected:
	void getAllUniformLocations() override;
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
	int m_location_cRenderer_tileCount;
};