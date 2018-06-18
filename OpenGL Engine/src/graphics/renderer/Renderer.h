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
	Renderer3D(StaticShader& shader, glm::mat4 projectionMatrix);
	~Renderer3D();

	void Render(std::unordered_map<Model, std::vector<Entity>, KeyHasher> renderList);
private:
	void prepareModel(Model& model);
	void unbindModel();
	void prepareInstance(Entity& entity);
private:
	glm::mat4 m_projectionMatrix;
	StaticShader& m_shader;
};

