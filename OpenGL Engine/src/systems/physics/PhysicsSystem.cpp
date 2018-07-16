#include "PhysicsSystem.h"
#include "..\..\Settings.h"
#include "..\..\components\Entity.h"
#include "..\..\components\PreDefinedComponents.h"
#include "..\..\components\EntityManager.h"

PhysicsSystem::PhysicsSystem(EntityManager* mEntityManager)
	: m_entityManager(mEntityManager)
{
}

void PhysicsSystem::update(float delta)
{
	auto physicsEntities = m_entityManager->getEntitiesByGroup(EntityGroups::HasPhysics);
	for (Entity* e : physicsEntities)
	{
		CPhysics& currentEntityPhysics = e->getComponent<CPhysics>();
		CPosition& currentEntityPosition = e->getComponent<CPosition>();

		currentEntityPhysics.velocity.y += Settings::gravity * delta;
		currentEntityPosition.value += currentEntityPhysics.velocity * delta;

		if (currentEntityPhysics.affectedByGravity)
		{
			if (currentEntityPosition.value.y < 0)
			{
				currentEntityPhysics.velocity.y = 0;
				currentEntityPosition.value.y = 0;
			}
		}
	}
}