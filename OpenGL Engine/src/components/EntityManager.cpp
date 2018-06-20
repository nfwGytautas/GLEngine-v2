#include "EntityManager.h"
#include <algorithm>

void EntityManager::refresh()
{
	for (auto i(0u); i < maxGroups; ++i)
	{
		auto& v(m_groupedEntities[i]);

		v.erase
		(
			std::remove_if(std::begin(v), std::end(v),
				[i](Entity* mEntity)
				{
					return !mEntity->isAlive() || !mEntity->hasGroup(i);
				}),
			std::end(v)
		);
	}

	m_entities.erase
	(
		std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isAlive();
			}),
		std::end(m_entities)
	);
}

void EntityManager::update(float frameTime)
{
	for (auto& e : m_entities)
	{
		e->update(frameTime);
	}
}

void EntityManager::draw()
{
	for (auto& e : m_entities)
	{
		e->draw();
	}
}

Entity& EntityManager::addEntity()
{
	Entity* e(new Entity(*this));
	std::unique_ptr<Entity> uPtr{ e };
	m_entities.emplace_back(std::move(uPtr));
	return *e;
}

void EntityManager::addToGroup(Entity * mEntity, Group mGroup)
{
	m_groupedEntities[mGroup].emplace_back(mEntity);
}

std::vector<Entity*>& EntityManager::getEntitiesByGroup(Group mGroup)
{
	return m_groupedEntities[mGroup];
}

EntityManager::EntityManager()
{}
EntityManager::~EntityManager()
{
	m_entities.clear();
}

bool Entity::hasGroup(Group mGroup) const noexcept
{
	return m_groupBitset[mGroup];
}

void Entity::addGroup(Group mGroup) noexcept
{
	m_groupBitset[mGroup] = true;
	m_manager.addToGroup(this, mGroup);
}

void Entity::delGroup(Group mGroup) noexcept
{
	m_groupBitset[mGroup] = false;
}

Entity::Entity(EntityManager & mManager)
	:m_manager(mManager)
{}
