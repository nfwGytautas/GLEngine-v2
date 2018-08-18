#pragma once
#include <string>
#include <unordered_map>
#include <utility>

struct CMaterial;
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

	std::pair<unsigned int, unsigned int> m_GUIQuad;
	std::tuple<unsigned int, unsigned int, unsigned int> m_skybox;
	CMaterial* m_currentMaterial;
	bool m_usingDefaults;
	bool m_firstTime;
};