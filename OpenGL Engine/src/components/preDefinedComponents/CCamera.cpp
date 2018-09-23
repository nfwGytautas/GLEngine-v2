#include "CCamera.h"
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Entity.h"
#include "..\..\algorithm\Algorithm.h"
#include "CTransformation.h"

void CCamera::init()
{
	if (!entity->hasComponent<CTransformation>())
	{
		entity->addComponent<CTransformation>();
	}
	cTransformation = &entity->getComponent<CTransformation>();
	entity->addGroup(EntityGroups::Camera);
}

void CCamera::update(float frameTime)
{
	glm::vec3 target = cTransformation->position;
	clamp(pitch, 89.0f, -89.0f);

	if (entity->hasGroup(EntityGroups::HasHook))
	{
		float horizontalDistance = distanceToHook * cos(glm::radians(pitch));
		float verticalDistance = distanceToHook * sin(glm::radians(pitch));

		float fullAngle = m_hookedTo->getComponent<CTransformation>().rotation.y + angleAroundHook;
		float offsetX = (float)horizontalDistance * sin(glm::radians(fullAngle));
		float offsetZ = (float)horizontalDistance * cos(glm::radians(fullAngle));

		cTransformation->position.x = m_hookedTo->getComponent<CTransformation>().position.x - offsetX;
		cTransformation->position.z = m_hookedTo->getComponent<CTransformation>().position.z - offsetZ;
		cTransformation->position.y = m_hookedTo->getComponent<CTransformation>().position.y + verticalDistance;

		yaw = 180 - (fullAngle);

		target = m_hookedTo->getComponent<CTransformation>().position;
	}

	viewDirection = glm::vec3(
		cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
		sin(glm::radians(pitch)),
		cos(glm::radians(pitch)) * sin(glm::radians(yaw))
	);

	viewDirection = glm::normalize(viewDirection);
	viewPoint = target + viewDirection;
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 ViewMatrix = glm::lookAt(
		cTransformation->position,
		viewPoint,
		up
	);

	viewMatrix = ViewMatrix;

}

void CCamera::hookTo(Entity* mEntity, float mDistanceToHook, float mAngleAroundHook)
{
	if(mEntity->hasComponent<CTransformation>())
	{
		m_hookedTo = mEntity;
		distanceToHook = mDistanceToHook;
		angleAroundHook = mAngleAroundHook;
		entity->addGroup(EntityGroups::HasHook);
	}
	else
	{
		std::cout << "[Engine][Component][Camera] Error: A hook is imbossible!" << std::endl;
	}
}
