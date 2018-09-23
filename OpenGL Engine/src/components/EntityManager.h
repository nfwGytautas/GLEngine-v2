#pragma once
#include <vector>
#include <memory>
#include <array>

#include "Entity.h"
#include "EntityBlueprint.h"

class EntityManager
{
public:
	void update(float frameTime);
	void preRender();
	void render();
	void postRender();
public:
	void refresh();
	void registerEntity(Entity* entity);
	void registerBlueprint(EntityBlueprint* blueprint);

	void addToGroup(Entity* mEntity, Group mGroup);
	std::vector<Entity*>& getEntitiesByGroup(Group mGroup);

	EntityManager();
	~EntityManager();
private:
	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_activeEntities;
	std::vector<EntityBlueprint*> m_blueprints;
	std::array<std::vector<Entity*>, maxGroups> m_groupedEntities;
};