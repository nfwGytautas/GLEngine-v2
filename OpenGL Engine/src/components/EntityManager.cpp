#include "EntityManager.h"
#include <algorithm>
#include "..\data manager\BatchManager.h"
#include "EntityBlueprint.h"

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

	m_bManager->updateEntityBatch(m_entities);
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

Entity & EntityManager::addEntity(EntityBlueprint& mBlueprint)
{
	Entity* e(new Entity(*this, mBlueprint));
	std::unique_ptr<Entity> uPtr{ e };
	m_entities.emplace_back(std::move(uPtr));
	return *e;
}

EntityBlueprint& EntityManager::addBlueprint()
{
	EntityBlueprint* e(new EntityBlueprint(*this));
	std::unique_ptr<EntityBlueprint> uPtr{ e };
	m_blueprints.emplace_back(std::move(uPtr));
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

EntityManager::EntityManager(BatchManager* pManager)
	:m_bManager(pManager)
{}
EntityManager::~EntityManager()
{
	m_entities.clear();
	m_blueprints.clear();
}