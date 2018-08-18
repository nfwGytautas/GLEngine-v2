#include "EntityManager.h"
#include <algorithm>
#include "..\SGEDefs.h"

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
			[](const Entity* mEntity)
	{
		return !mEntity->isAlive();
	}),
		std::end(m_entities)
		);

	SGE::Instances::instances->batchManagerInstance->updateEntityBatch(m_entities);
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

void EntityManager::registerEntity(Entity* entity)
{
	m_entities.push_back(entity);
}

void EntityManager::registerBlueprint(EntityBlueprint* blueprint)
{
	m_blueprints.push_back(blueprint);
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
	m_blueprints.clear();
}