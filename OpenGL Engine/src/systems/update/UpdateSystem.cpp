#include "UpdateSystem.h"
#include "..\..\SGEDefs.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\..\Settings.h"
#include "..\..\graphics\display\Display.h"
#include "..\..\data manager\input\InputManager.h"
#include "..\physics\PhysicsSystem.h"
#include "..\event\EventSystem.h"
#include "..\..\algorithm\Algorithm.h"
#include "..\..\components\Entity.h"
#include "..\..\components\EntityManager.h"
#include "..\..\components\preDefinedComponents\CInput.h"
#include "..\..\components\preDefinedComponents\CCamera.h"
#include "..\..\maths\Maths.h"

void UpdateSystem::update()
{
	Display::updateDisplay();
	InputManager::update();
	SGE::Instances::instances->entityManagerInstance->refresh();

	updateEntitiesWithTransformation();
	updateEntitiesWithInput();
	updateEntitiesWithPhysics();
	updateEntitiesWithCameras();

	//Kinda redundant now
	SGE::Instances::instances->entityManagerInstance->update(Display::getDelta());
}
UpdateSystem::UpdateSystem()
{
}
void UpdateSystem::updateEntitiesWithTransformation()
{
	auto transformations = SGE::Instances::instances->entityManagerInstance->getEntitiesByGroup(EntityGroups::StaticEntity);
	for (Entity* entity : transformations)
	{
		CTransformation& cTransform = entity->getComponent<CTransformation>();
		cTransform.transformationMatrix = Maths::createTransformationMatrix
		(
			cTransform.position,
			cTransform.rotation,
			cTransform.scale
		);
	}
}
void UpdateSystem::updateEntitiesWithInput()
{
	auto downKeys = InputManager::getKeyDown();
	for (Key key : downKeys)
	{
		SGE::Instances::instances->eventSystemInstance->post(KeyDownEvent(key));
	}
	auto upKeys = InputManager::getKeyUp();
	for (Key key : upKeys)
	{
		SGE::Instances::instances->eventSystemInstance->post(KeyUpEvent(key));
	}
	auto mDownKeys = InputManager::getMKeyDown();
	for (MouseKey key : mDownKeys)
	{
		SGE::Instances::instances->eventSystemInstance->post(MouseKeyDownEvent(key));
	}
	auto mUpKeys = InputManager::getMKeyUp();
	for (MouseKey key : mUpKeys)
	{
		SGE::Instances::instances->eventSystemInstance->post(MouseKeyUpEvent(key));
	}
	SGE::Instances::instances->eventSystemInstance->post(MouseMovedEvent(InputManager::Mouse::getXOffset(), InputManager::Mouse::getYOffset()));
	SGE::Instances::instances->eventSystemInstance->post(MouseScrollEvent(InputManager::Mouse::getScrollAmountX(), InputManager::Mouse::getScrollAmountY()));
}
void UpdateSystem::updateEntitiesWithPhysics()
{
	SGE::Instances::instances->physicsSystemInstance->update(Display::getDelta());
}

void UpdateSystem::updateEntitiesWithCameras()
{
	auto cameraEntities = SGE::Instances::instances->entityManagerInstance->getEntitiesByGroup(EntityGroups::Camera);
	for (Entity* e : cameraEntities)
	{
		CCamera& cameraComponent = e->getComponent<CCamera>();
		glm::vec3 target = cameraComponent.cTransformation->position;
		clamp(cameraComponent.pitch, 89.0f, -89.0f);

		if (e->hasGroup(EntityGroups::HasHook))
		{
			float horizontalDistance = cameraComponent.distanceToHook * cos(glm::radians(cameraComponent.pitch));
			float verticalDistance = cameraComponent.distanceToHook * sin(glm::radians(cameraComponent.pitch));

			float fullAngle = cameraComponent.m_hookedTo->getComponent<CTransformation>().rotation.y + cameraComponent.angleAroundHook;
			float offsetX = (float)horizontalDistance * sin(glm::radians(fullAngle));
			float offsetZ = (float)horizontalDistance * cos(glm::radians(fullAngle));

			cameraComponent.cTransformation->position.x = cameraComponent.m_hookedTo->getComponent<CTransformation>().position.x - offsetX;
			cameraComponent.cTransformation->position.z = cameraComponent.m_hookedTo->getComponent<CTransformation>().position.z - offsetZ;
			cameraComponent.cTransformation->position.y = cameraComponent.m_hookedTo->getComponent<CTransformation>().position.y + verticalDistance;

			cameraComponent.yaw = 180 - (fullAngle);

			target = cameraComponent.m_hookedTo->getComponent<CTransformation>().position;
		}

		cameraComponent.m_direction = glm::vec3(
			cos(glm::radians(cameraComponent.pitch)) * cos(glm::radians(cameraComponent.yaw)),
			sin(glm::radians(cameraComponent.pitch)),
			cos(glm::radians(cameraComponent.pitch)) * sin(glm::radians(cameraComponent.yaw))
		);

		glm::mat4 ViewMatrix = glm::lookAt(
			cameraComponent.cTransformation->position,
			target + cameraComponent.m_direction,
			glm::vec3(0.0, 1.0, 0.0)
		);

		cameraComponent.viewMatrix = ViewMatrix;
	}
}