#pragma once
#include <vector>
#include <memory>
#include <array>

#include "Entity.h"
#include "EntityBlueprint.h"

class BatchManager;
class EntityManager
{
public:
	void refresh();
	void update(float frameTime);
	void draw();
	Entity& addEntity();
	Entity& addEntity(EntityBlueprint& mBlueprint);
	EntityBlueprint& addBlueprint();

	void addToGroup(Entity* mEntity, Group mGroup);
	std::vector<Entity*>& getEntitiesByGroup(Group mGroup);

	EntityManager(BatchManager* pManager);
	~EntityManager();
private:
	std::vector<std::unique_ptr<Entity>> m_entities;
	std::vector<std::unique_ptr<EntityBlueprint>> m_blueprints;
	std::array<std::vector<Entity*>, maxGroups> m_groupedEntities;
	BatchManager* m_bManager;
};