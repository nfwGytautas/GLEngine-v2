#include "Entity.h"
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
void Entity::draw()
{
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		if (m_componentArray[i] != nullptr)
		{
			m_componentArray[i]->draw();
		}
	}
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
	m_manager.addToGroup(this, mGroup);
}

Entity::Entity(EntityManager& mManager)
	: m_manager(mManager)
{
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		m_componentArray[i] = nullptr;
	}
}
Entity::Entity(EntityManager& mManager, EntityBlueprint& mBlueprint)
	: m_manager(mManager)
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
}
Entity::~Entity()
{
	for (unsigned int i = 0; i < maxComponents; i++)
	{
		if (m_componentArray[i] != nullptr)
		{
			delete m_componentArray[i];
		}
	}
}