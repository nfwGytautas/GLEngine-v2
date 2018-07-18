#include "CCamera.h"
#include <iostream>
#include "..\Entity.h"
#include "CTransformation.h"

void CCamera::init()
{
	if (!entity->hasComponent<CPosition>())
	{
		entity->addComponent<CPosition>(glm::vec3(0, 0, 0));
	}
	cPosition = &entity->getComponent<CPosition>();
	entity->addGroup(EntityGroups::Camera);
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
