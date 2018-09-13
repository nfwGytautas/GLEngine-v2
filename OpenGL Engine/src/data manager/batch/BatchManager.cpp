#include "BatchManager.h"
#include <algorithm>
#include "..\..\components\Entity.h"
#include "..\..\graphics\gui\GUI.h"


BatchManager::BatchManager()
	: m_newVAOData(false)
{
}
BatchManager::~BatchManager()
{
}

//============================================================================================================================
//MESHES & MATERIALS
//============================================================================================================================
/*void BatchManager::acknowledgeMaterial(unsigned int id)
{
	if (std::find(m_knownMaterials.begin(), m_knownMaterials.end(), id) == m_knownMaterials.end())
	{
		m_knownMaterials.push_back(id);
	}
}*/

void BatchManager::addEntityToVAOBatch(Entity* entity, VAO vao)
{
	m_entityBatch[vao.ID].push_back(entity);
}

void BatchManager::addVAO(VAO vao)
{
	if (std::find(m_knownVertexArrays.begin(), m_knownVertexArrays.end(), vao) == m_knownVertexArrays.end())
	{
		m_knownVertexArrays.push_back(vao);
		m_newVAOData = true;
	}
}

void BatchManager::acknowledgeGUI(GUI* gui)
{
	if (std::find(m_knownGUIs.begin(), m_knownGUIs.end(), gui) == m_knownGUIs.end())
	{
		m_knownGUIs.push_back(gui);
	}
}

void BatchManager::clearEntityBatch()
{
	m_knownVertexArrays.clear();
}

/*std::vector<Entity*>& BatchManager::getEntityBatch(unsigned int materialID)
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
}*/

std::vector<VAO>& BatchManager::allKnownVAOS()
{
	return m_knownVertexArrays;
}

std::vector<Entity*>& BatchManager::getSameVAOEntities(unsigned int vaoID)
{
	return m_entityBatch[vaoID];
}

std::vector<GUI*>& BatchManager::allKnownGUIs()
{
	return m_knownGUIs;
}

void BatchManager::cleanUp()
{
	clearEntityBatch();
	m_knownGUIs.clear();
	m_knownVertexArrays.clear();
}