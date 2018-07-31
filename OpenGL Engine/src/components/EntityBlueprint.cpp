#include "EntityBlueprint.h"
#include "EntityManager.h"
#include "Entity.h"

EntityBlueprint::EntityBlueprint(EntityManager& mManager)
	: m_manager(mManager)
{
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		m_componentArray[i] = nullptr;
	}
}
EntityBlueprint::~EntityBlueprint()
{
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		if(m_componentArray[i] != nullptr)
		{
			delete m_componentArray[i];
		}
	}
}