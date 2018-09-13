#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include "..\..\data manager\data structures\Model.h"

class Entity;
class DynamicShader;
class RenderSystem
{
public:
	void render();

	RenderSystem();
private:
	void prepare();
	void loadViewport(DynamicShader* shader);
	void loadLights(DynamicShader* shader);
	void renderEntities();
	void renderEntity(VAO vao);
	void renderInstancedEntities(VAO vao, unsigned int count);
	void renderGUI(DynamicShader* shader);
	void renderSkybox(DynamicShader* shader);
	void loadRenderSettings(DynamicShader* shader, Entity* entity);
	void loadDefaultRenderSettings(DynamicShader* shader);
	void loadMaterial(DynamicShader* shader, Material* material);
	void setupShader(DynamicShader* shader);

	VAO m_GUIQuad;
	std::tuple<unsigned int, unsigned int, unsigned int> m_skybox;
	bool m_usingDefaults;
	bool m_firstTime;

	unsigned int m_instanceVBO;

	const unsigned int max_instances = 10000;
	const unsigned int instance_data_length = 16;
};