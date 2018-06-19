#include "EntityManager.h"
#include <algorithm>

void EntityManager::update(float frameTime)
{
	m_entities.erase
	(
		std::remove_if(std::begin(m_entities), std::end(m_entities), 
		[](const std::unique_ptr<Entity>& mEntity)
		{
			return !mEntity->isAlive();
		}),
		std::end(m_entities)
	);

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
	Entity* e{ new Entity{} };
	std::unique_ptr<Entity> uPtr{ e };
	m_entities.emplace_back(std::move(uPtr));
	return *e;
}

EntityManager::EntityManager()
{}
EntityManager::~EntityManager()
{}
