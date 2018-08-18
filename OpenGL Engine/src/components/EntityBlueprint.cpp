#include "EntityBlueprint.h"
#include "..\SGEDefs.h"
#include "EntityManager.h"
#include "Entity.h"

EntityBlueprint::EntityBlueprint()
{
	SGE::Instances::instances->entityManagerInstance->registerBlueprint(this);
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		m_componentArray[i] = nullptr;
	}
}
EntityBlueprint::~EntityBlueprint()
{
	releaseMemory();
}

void EntityBlueprint::releaseMemory()
{
	if(!m_memoryReleased)
	{
		for (unsigned int i = 0; i < maxComponents; i++)
		{
			if (m_componentArray[i] != nullptr)
			{
				delete m_componentArray[i];
			}
		}
		m_memoryReleased = true;
	}
}