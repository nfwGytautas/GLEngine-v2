#pragma once

class Camera;
class EntityManager;
class PhysicsSystem;
class UpdateSystem
{
public:
	void update();
	void selectViewport(Camera* mCamera);

	UpdateSystem(EntityManager* mEntityManager, PhysicsSystem* mPhysicsSystem);
private:
	void updateEntitiesWithInput();
	void updateEntitiesWithPhysics();

	Camera* m_camera;
	EntityManager* m_entityManager;
	PhysicsSystem* m_physicsSystem;
};