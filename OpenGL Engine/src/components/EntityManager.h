#pragma once
#include "Entity.h"

class EntityManager
{
public:
	void update(float frameTime);
	void draw();
	Entity& addEntity();

	EntityManager();
	~EntityManager();
private:
	std::vector<std::unique_ptr<Entity>> m_entities;
};