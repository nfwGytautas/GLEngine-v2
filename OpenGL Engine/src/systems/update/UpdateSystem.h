#pragma once

class EntityManager;
class PhysicsSystem;
class UpdateSystem
{
public:
	void update();

	UpdateSystem(EntityManager* mEntityManager, PhysicsSystem* mPhysicsSystem);
private:
	void updateEntitiesWithInput();
	void updateEntitiesWithPhysics();
	void updateEntitiesWithCameras();

	EntityManager* m_entityManager;
	PhysicsSystem* m_physicsSystem;
};