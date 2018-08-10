#pragma once

class EntityManager;
class PhysicsSystem;
class EventSystem;

class UpdateSystem
{
public:
	void update();

	UpdateSystem(EntityManager* mEntityManager, PhysicsSystem* mPhysicsSystem, EventSystem* mEventSystem);
private:
	void updateEntitiesWithTransformation();
	void updateEntitiesWithInput();
	void updateEntitiesWithPhysics();
	void updateEntitiesWithCameras();

	EntityManager* m_entityManager;
	PhysicsSystem* m_physicsSystem;
	EventSystem* m_eventSystem;
};