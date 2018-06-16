#pragma once

#include <glm\glm.hpp>

class Mesh;
class Model;
class Entity;
class StaticShader;

class Renderer3D
{
public:
	Renderer3D(StaticShader* shader);
	~Renderer3D();

	void Prepare();

	void Render(Entity entity, StaticShader* shader);
private:
	//TODO: Move to engine/camera
	void createProjectionMatrix();
private:
	glm::mat4 m_projectionMatrix;

	const float FOV = 70;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 1000.0f;
};

