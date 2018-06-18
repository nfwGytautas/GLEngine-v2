#pragma once
#include "HashImplementations.h"
#include <unordered_map>
#include <vector>

#include <glm\glm.hpp>

class StaticShader;
class Renderer3D;
class TerrainShader;
class TerrainRenderer;

class Entity;
class Terrain;
class Light;
class Camera;

class MasterRenderer
{
public:
	MasterRenderer(StaticShader& shader, TerrainShader& terrainShader);
	~MasterRenderer();

	void Prepare();

	void ProcessEntity(Entity& entity);
	void ProcessTerrain(Terrain& terrain);
	void Render(Light& sun, Camera& camera);

private:
	void createProjectionMatrix();
private:
	StaticShader& m_shader;
	Renderer3D* m_renderer;
	TerrainShader& m_terrainShader;
	TerrainRenderer* m_terrainRenderer;

	std::unordered_map<Model, std::vector<Entity>, KeyHasher> m_entitiesHashMap;
	std::vector<Terrain> m_terrains;

	glm::mat4 m_projectionMatrix;

	//TODO: Allow these to change on runtime
	const float FOV = 70;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 1000.0f;
};

