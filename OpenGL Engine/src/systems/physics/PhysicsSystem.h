#pragma once

class EntityManager;
class PhysicsSystem
{
public:
	void update(float delta);

	PhysicsSystem(EntityManager* mEntityManager);
private:
	EntityManager* m_entityManager;
};

