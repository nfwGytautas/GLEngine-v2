#include "UpdateSystem.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\..\Settings.h"
#include "..\..\graphics\display\Display.h"
#include "..\..\components\Entity.h"
#include "..\..\components\PreDefinedComponents.h"
#include "..\..\components\EntityManager.h"
#include "..\..\input\InputManager.h"
#include "..\physics\PhysicsSystem.h"

void UpdateSystem::update()
{
	Display::updateDisplay();
	m_entityManager->refresh();

	updateEntitiesWithInput();
	updateEntitiesWithPhysics();
	updateEntitiesWithCameras();

	//Kinda redundant now
	m_entityManager->update(Display::getDelta());
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

void UpdateSystem::updateEntitiesWithCameras()
{
	auto cameraEntities = m_entityManager->getEntitiesByGroup(EntityGroups::Camera);
	for (Entity* e : cameraEntities)
	{
		CCamera& cameraComponent = e->getComponent<CCamera>();

		cameraComponent.m_direction = glm::vec3(
			cos(cameraComponent.m_verticalAngle) * sin(cameraComponent.m_horizontalAngle),
			sin(cameraComponent.m_verticalAngle),
			cos(cameraComponent.m_verticalAngle) * cos(cameraComponent.m_horizontalAngle)
		);

		cameraComponent.m_right = glm::vec3(
			sin(cameraComponent.m_horizontalAngle - 3.14f / 2.0f),
			0,
			cos(cameraComponent.m_horizontalAngle - 3.14f / 2.0f)
		);

		glm::vec3 up = glm::cross(cameraComponent.m_right, cameraComponent.m_direction);

		glm::mat4 ViewMatrix = glm::lookAt(
			cameraComponent.cPosition->value,
			cameraComponent.cPosition->value + cameraComponent.m_direction,
			up
		);

		cameraComponent.viewMatrix = ViewMatrix;

		double xpos, ypos;
		InputManager::Mouse::getCursorPosition(xpos, ypos);
		InputManager::Mouse::centerCursorPosition();

		cameraComponent.m_horizontalAngle += 0.005f * /*deltaTime */ float(1280 / 2 - xpos);
		cameraComponent.m_verticalAngle += 0.005f * /*deltaTime */ float(720 / 2 - ypos);
	}
}
