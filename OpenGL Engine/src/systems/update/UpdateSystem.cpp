#include "UpdateSystem.h"
#include "..\..\Settings.h"
#include "..\..\graphics\display\Display.h"
#include "..\..\graphics\display\Camera.h"
#include "..\..\components\Entity.h"
#include "..\..\components\PreDefinedComponents.h"
#include "..\..\components\EntityManager.h"
#include "..\..\input\InputManager.h"
#include "..\physics\PhysicsSystem.h"

void UpdateSystem::update()
{
	Display::updateDisplay();
	m_entityManager->refresh();

	//Change to another component
	m_camera->Move();

	updateEntitiesWithInput();
	updateEntitiesWithPhysics();

	//Kinda redundant now
	m_entityManager->update(Display::getDelta());
}
void UpdateSystem::selectViewport(Camera * mCamera)
{
	m_camera = mCamera;
}
UpdateSystem::UpdateSystem(EntityManager* mEntityManager, PhysicsSystem* mPhysicsSystem)
	: m_entityManager(mEntityManager), m_physicsSystem(mPhysicsSystem)
{
}
void UpdateSystem::updateEntitiesWithInput()
{
	auto inputEntities = m_entityManager->getEntitiesByGroup(EntityGroups::HasInput);
	for (Entity* e : inputEntities)
	{
		e->getComponent<CInput>().react(InputManager::getKey());
	}
}
void UpdateSystem::updateEntitiesWithPhysics()
{
	m_physicsSystem->update(Display::getDelta());
}