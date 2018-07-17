#include "CCamera.h"
#include "..\Entity.h"

void CCamera::init()
{
	if (!entity->hasComponent<CPosition>())
	{
		entity->addComponent<CPosition>(glm::vec3(0, 0, 0));
	}
	cPosition = &entity->getComponent<CPosition>();
	entity->addGroup(EntityGroups::Camera);
}
