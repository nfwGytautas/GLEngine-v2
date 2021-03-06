#include "Entity.h"
#include "..\SGEDefs.h"
#include "EntityManager.h"

void Entity::init()
{
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		if(m_componentArray[i] != nullptr) 
		{
			m_componentArray[i]->init();
		}
	}
}
void Entity::update(float frameTime)
{
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		if (m_componentArray[i] != nullptr)
		{
			m_componentArray[i]->update(frameTime);
		}
	}
}
void Entity::preRender()
{
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		if (m_componentArray[i] != nullptr)
		{
			m_componentArray[i]->preRender();
		}
	}
}
void Entity::render()
{
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		if (m_componentArray[i] != nullptr)
		{
			m_componentArray[i]->render();
		}
	}
}
void Entity::postRender()
{
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		if (m_componentArray[i] != nullptr)
		{
			m_componentArray[i]->postRender();
		}
	}
}

bool Entity::isActive() const
{
	return m_active;
}

void Entity::deactivate()
{
	m_active = false;
}

void Entity::activate()
{
	m_active = true;
}

bool Entity::isAlive() const
{
	return m_alive;
}
void Entity::destroy()
{
	m_alive = false;
}

bool Entity::hasGroup(Group mGroup) const noexcept
{
	return m_groupBitset[mGroup];
}
void Entity::delGroup(Group mGroup) noexcept
{
	m_groupBitset[mGroup] = false;
}
void Entity::addGroup(Group mGroup) noexcept
{
	m_groupBitset[mGroup] = true;
	SGE::Instances::instances->entityManagerInstance->addToGroup(this, mGroup);
}

Entity::Entity()
{
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		m_componentArray[i] = nullptr;
	}
	SGE::Instances::instances->entityManagerInstance->registerEntity(this);
}
Entity::Entity(EntityBlueprint& mBlueprint)
{
	m_componentBitset = mBlueprint.m_componentBitset;

	for (unsigned int i = 0; i < maxComponents; i++)
	{
		m_componentArray[i] = nullptr;
		if (mBlueprint.m_componentArray[i] != nullptr)
		{		
			Component* comp = mBlueprint.m_componentArray[i]->clone();
			comp->entity = this;
			comp->init();
			m_componentArray[i] = comp;
		}
	}
	SGE::Instances::instances->entityManagerInstance->registerEntity(this);
}
Entity::~Entity()
{
	releaseMemory();
}

void Entity::releaseMemory()
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
