#pragma once

#include <vector>

#include <glm/glm.hpp>

class TerrainShader;
class Terrain;
class Model;

class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader& shader, glm::mat4 projectionMatrix);
	~TerrainRenderer();

	void Render(std::vector<Terrain> terrains);
private:
	void prepareTerrain(Terrain& model);
	void unbindTerrain();
	void loadModelMatrix(Terrain& terrain);
private:
	TerrainShader& m_shader;
};

