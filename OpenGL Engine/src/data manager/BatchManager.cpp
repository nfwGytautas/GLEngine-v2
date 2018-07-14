#include "BatchManager.h"
#include <algorithm>
#include "..\components\Entity.h"

BatchManager::BatchManager()
{
}
BatchManager::~BatchManager()
{
}

//============================================================================================================================
//MESHES & MATERIALS
//============================================================================================================================
void BatchManager::acknowledgeMaterial(unsigned int id)
{
	if(std::find(m_knownMaterials.begin(), m_knownMaterials.end(), id) == m_knownMaterials.end())
	{
		m_knownMaterials.push_back(id);
	}
}
void BatchManager::acknowledgeMesh(unsigned int id)
{
	if (std::find(m_knownMeshes.begin(), m_knownMeshes.end(), id) == m_knownMeshes.end())
	{
		m_knownMeshes.push_back(id);
	}
}

void BatchManager::addEntity(Entity* entity)
{
	if(entity->hasComponent<CMesh>())
	{
		auto mesh = entity->getComponent<CMesh>().m_vaoID;
		if (m_entityBatch.find(mesh) != m_entityBatch.end())
		{
			m_entityBatch[mesh].push_back(entity);
		}
		else
		{
			std::vector<Entity*> newBatch;
			newBatch.push_back(entity);
			m_entityBatch[mesh] = newBatch;
		}
	}
}
void BatchManager::updateEntityBatch(const std::vector<std::unique_ptr<Entity>>& pEntities)
{
	clearEntityBatch();
	for (auto& e : pEntities)
	{
		addEntity(e.get());
	}
}
void BatchManager::clearEntityBatch()
{
	m_entityBatch.clear();
}

std::vector<Entity*>& BatchManager::getEntityBatch(unsigned int materialID)
{
	return m_entityBatch[materialID];
}
std::vector<unsigned int>& BatchManager::allKnownMaterials()
{
	return m_knownMaterials;
}
std::vector<unsigned int>& BatchManager::allKnownMeshes()
{
	return m_knownMeshes;
}

void BatchManager::cleanUp()
{
	clearEntityBatch();
	m_knownMaterials.clear();
	m_knownMeshes.clear();
}