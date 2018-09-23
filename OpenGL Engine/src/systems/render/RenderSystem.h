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
	void renderEntities(DynamicShader* shader);
	void renderGUI(DynamicShader* shader);
	void renderSkybox(DynamicShader* shader);
	void loadRenderSettings(DynamicShader* shader, Entity* entity);
	void loadDefaultRenderSettings(DynamicShader* shader);

	VAO m_GUIQuad;
	std::tuple<unsigned int, unsigned int, unsigned int> m_skybox;
	bool m_usingDefaults;
	bool m_firstTime;
};