#pragma once
#include "Entity.h"

class EntityManager
{
public:
	void refresh();
	void update(float frameTime);
	void draw();
	Entity& addEntity();

	void addToGroup(Entity* mEntity, Group mGroup);
	std::vector<Entity*>& getEntitiesByGroup(Group mGroup);

	EntityManager();
	~EntityManager();
private:
	std::vector<std::unique_ptr<Entity>> m_entities;

	std::array<std::vector<Entity*>, maxGroups> m_groupedEntities;
};