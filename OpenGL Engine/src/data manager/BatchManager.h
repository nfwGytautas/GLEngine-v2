#pragma once
#include "..\components\PreDefinedComponents.h"
#include <unordered_map>
#include <vector>
#include <memory>

class GUI;
class BatchManager
{
public:

	BatchManager();
	~BatchManager();

	//Meshes & Materials & GUIs
	void acknowledgeMaterial(unsigned int id);
	void acknowledgeMesh(unsigned int id);
	void acknowledgeGUI(GUI& gui);

	void addEntity(Entity* entity);
	void updateEntityBatch(const std::vector<std::unique_ptr<Entity>>& pEntities);

	std::vector<Entity*>& getEntityBatch(unsigned int materialID);
	std::vector<unsigned int>& allKnownMaterials();
	std::vector<unsigned int>& allKnownMeshes();
	std::vector<GUI>& allKnownGUIs();


	void cleanUp();
private:
	void clearEntityBatch();
private:
	std::unordered_map<unsigned int, std::vector<Entity*>> m_entityBatch;

	std::vector<unsigned int> m_knownMaterials;
	std::vector<unsigned int> m_knownMeshes;
	std::vector<GUI> m_knownGUIs;
};