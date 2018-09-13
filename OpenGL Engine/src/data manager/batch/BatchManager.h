#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include "..\..\components\PreDefinedComponents.h"

class GUI;
class UpdateSystem;
class BatchManager
{
public:

	BatchManager();
	~BatchManager();

	//Meshes & Materials & GUIs
	void addEntityToVAOBatch(Entity* entity, VAO vao);
	void addVAO(VAO vao);
	void acknowledgeGUI(GUI* gui);

	//void addEntity(Entity* entity);
	//void updateEntityBatch(const std::vector<Entity*>& pEntities);

	//std::vector<Entity*>& getEntityBatch(unsigned int materialID);
	//std::vector<unsigned int>& allKnownMaterials();
	std::vector<VAO>& allKnownVAOS();
	std::vector<Entity*>& getSameVAOEntities(unsigned int vaoID);
	std::vector<GUI*>& allKnownGUIs();

	void cleanUp();
private:
	void clearEntityBatch();
private:
	bool m_newVAOData;

	std::unordered_map<unsigned int, std::vector<Entity*>> m_entityBatch;

	/*std::vector<unsigned int> m_knownMaterials;
	std::vector<unsigned int> m_knownMeshes;*/
	std::vector<VAO> m_knownVertexArrays;
	std::vector<GUI*> m_knownGUIs;

	friend UpdateSystem;
};