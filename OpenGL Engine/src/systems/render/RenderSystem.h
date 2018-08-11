#pragma once
#include <string>
#include <unordered_map>
#include <utility>

struct CMaterial;
class DynamicShader;
class BatchManager;
class Entity;
class EntityManager;

class RenderSystem
{
public:
	void render();

	RenderSystem(std::unordered_map<std::string, DynamicShader*>* mShaders, EntityManager* mEntityManager, BatchManager* mBatchManager, std::pair<unsigned int, unsigned int> mGUIQuad, std::tuple<unsigned int, unsigned int, unsigned int> mSkybox);
private:
	void prepare();
	void loadViewport(std::string mShader);
	void loadLights(std::string mShader);
	void renderEntities();
	void renderGUI();
	void renderSkybox();
	void loadRenderSettings(std::string mShader, Entity* entity);
	void loadDefaultRenderSettings(std::string mShader);
	
	std::pair<unsigned int, unsigned int> m_GUIQuad;
	std::tuple<unsigned int, unsigned int, unsigned int> m_skybox;
	CMaterial* m_currentMaterial;
	bool m_usingDefaults;

	std::unordered_map<std::string, DynamicShader*>* m_shaders;
	EntityManager* m_entityManager;
	BatchManager* m_batchManager;
};