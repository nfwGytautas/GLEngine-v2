#include "UpdateSystem.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\..\Settings.h"
#include "..\..\graphics\display\Display.h"
#include "..\..\input\InputManager.h"
#include "..\physics\PhysicsSystem.h"
#include "..\event\EventSystem.h"
#include "..\..\algorithm\Algorithm.h"
#include "..\..\components\Entity.h"
#include "..\..\components\EntityManager.h"
#include "..\..\components\preDefinedComponents\CInput.h"
#include "..\..\components\preDefinedComponents\CCamera.h"

void UpdateSystem::update()
{
	Display::updateDisplay();
	InputManager::update();
	m_entityManager->refresh();

	updateEntitiesWithInput();
	updateEntitiesWithPhysics();
	updateEntitiesWithCameras();

	//Kinda redundant now
	m_entityManager->update(Display::getDelta());
}
UpdateSystem::UpdateSystem(EntityManager* mEntityManager, PhysicsSystem* mPhysicsSystem, EventSystem* mEventSystem)
	: m_entityManager(mEntityManager), m_physicsSystem(mPhysicsSystem), m_eventSystem(mEventSystem)
{
}
void UpdateSystem::updateEntitiesWithInput()
{
	auto downKeys = InputManager::getKeyDown();
	for (Key key : downKeys)
	{
		m_eventSystem->post(KeyDownEvent(key));
	}
	auto upKeys = InputManager::getKeyUp();
	for (Key key : upKeys)
	{
		m_eventSystem->post(KeyUpEvent(key));
	}
	auto mDownKeys = InputManager::getMKeyDown();
	for (MouseKey key : mDownKeys)
	{
		m_eventSystem->post(MouseKeyDownEvent(key));
	}
	auto mUpKeys = InputManager::getMKeyUp();
	for (MouseKey key : mUpKeys)
	{
		m_eventSystem->post(MouseKeyUpEvent(key));
	}	
	m_eventSystem->post(MouseMovedEvent(InputManager::Mouse::getXOffset(), InputManager::Mouse::getYOffset()));
	m_eventSystem->post(MouseScrollEvent(InputManager::Mouse::getScrollAmountX(), InputManager::Mouse::getScrollAmountY()));
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
		glm::vec3 target = cameraComponent.cPosition->value;
		clamp(cameraComponent.pitch, 89.0f, -89.0f);

		if (e->hasGroup(EntityGroups::HasHook))
		{
			float horizontalDistance = cameraComponent.distanceToHook * cos(glm::radians(cameraComponent.pitch));
			float verticalDistance = cameraComponent.distanceToHook * sin(glm::radians(cameraComponent.pitch));

			float fullAngle = cameraComponent.m_hookedTo->getComponent<CTransformation>().rotationY + cameraComponent.angleAroundHook;
			float offsetX = (float) horizontalDistance * sin(glm::radians(fullAngle));
			float offsetZ = (float) horizontalDistance * cos(glm::radians(fullAngle));

			cameraComponent.cPosition->value.x = cameraComponent.m_hookedTo->getComponent<CPosition>().value.x - offsetX;
			cameraComponent.cPosition->value.z = cameraComponent.m_hookedTo->getComponent<CPosition>().value.z - offsetZ;
			cameraComponent.cPosition->value.y = cameraComponent.m_hookedTo->getComponent<CPosition>().value.y + verticalDistance;

			cameraComponent.yaw = 180 - (fullAngle);

			target = cameraComponent.m_hookedTo->getComponent<CPosition>().value;
		}

		cameraComponent.m_direction = glm::vec3(
			cos(glm::radians(cameraComponent.pitch)) * cos(glm::radians(cameraComponent.yaw)),
			sin(glm::radians(cameraComponent.pitch)),
			cos(glm::radians(cameraComponent.pitch)) * sin(glm::radians(cameraComponent.yaw))
		);

		glm::mat4 ViewMatrix = glm::lookAt(
			cameraComponent.cPosition->value,
			target + cameraComponent.m_direction,
			glm::vec3(0.0, 1.0, 0.0)
		);

		cameraComponent.viewMatrix = ViewMatrix;
	}
}
