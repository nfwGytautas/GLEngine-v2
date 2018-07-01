#include "CLightEmiter.h"
#include "..\Entity.h"

void CLightEmiter::init()
{
	if (!entity->hasComponent<CPosition>())
	{
		entity->addComponent<CPosition>(glm::vec3(100, 100, 100));
	}
	if (!entity->hasComponent<CColor>())
	{
		entity->addComponent<CColor>(glm::vec3(1, 1, 1));
	}
	cPosition = &entity->getComponent<CPosition>();
	cColor = &entity->getComponent<CColor>();
	entity->addGroup(EntityGroups::LightEmittingEntity);
}