#pragma once
#include "HashImplementations.h"
#include <unordered_map>

class StaticShader;
class Renderer3D;

class Entity;
class Light;
class Camera;

class MasterRenderer
{
public:
	MasterRenderer(StaticShader& shader);
	~MasterRenderer();

	void ProcessEntity(Entity& entity);
	void Render(Light& sun, Camera& camera);
private:
	StaticShader& m_shader;
	Renderer3D* m_renderer;

	std::unordered_map<Model, std::vector<Entity>, KeyHasher> m_entitiesHashMap;
};

