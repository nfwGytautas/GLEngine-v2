#pragma once

struct CMaterial;
class DynamicShader;
class BatchManager;
class Entity;
class EntityManager;

class RenderSystem
{
public:
	void render();

	RenderSystem(DynamicShader* mShader, EntityManager* mEntityManager, BatchManager* mBatchManager);
private:
	void prepare();
	void loadLights();
	void renderEntities();
	void loadRenderSettings(Entity* entity);
	void loadDefaultRenderSettings();
	
	CMaterial* m_currentMaterial;
	bool m_usingDefaults;

	DynamicShader* m_shader;
	EntityManager* m_entityManager;
	BatchManager* m_batchManager;
};