#pragma once
#include "HashImplementations.h"
#include <unordered_map>

#include <glm\glm.hpp>

class Material;
class Model;
class Entity;
class StaticShader;

class Renderer3D
{
public:
	Renderer3D(StaticShader& shader);
	~Renderer3D();

	void Prepare();

	void Render(std::unordered_map<Model, std::vector<Entity>, KeyHasher> renderList);
private:
	//TODO: Move to engine/camera
	void createProjectionMatrix();

	void prepareModel(Model& model);
	void unbindModel();
	void prepareInstance(Entity& entity);
private:
	glm::mat4 m_projectionMatrix;
	StaticShader& m_shader;

	const float FOV = 70;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 1000.0f;
};

