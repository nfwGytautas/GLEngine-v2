#include "EntityBlueprint.h"
#include "EntityManager.h"
#include "Entity.h"

EntityBlueprint::EntityBlueprint(EntityManager& mManager)
	: m_manager(mManager)
{
}
EntityBlueprint::~EntityBlueprint()
{
	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		delete m_components[i];
	}

	m_components.clear();
}