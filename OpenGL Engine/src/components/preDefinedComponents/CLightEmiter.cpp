#include "CLightEmiter.h"
#include "..\Entity.h"

void CLightEmiter::init()
{
	if (!entity->hasComponent<CTransformation>())
	{
		entity->addComponent<CTransformation>(glm::vec3(100, 100, 100), glm::vec3(0,0,0), glm::vec3(1,1,1));
	}
	if (!entity->hasComponent<CColor>())
	{
		entity->addComponent<CColor>(glm::vec3(1, 1, 1));
	}
	cTransform = &entity->getComponent<CTransformation>();
	cColor = &entity->getComponent<CColor>();
	entity->addGroup(EntityGroups::LightEmittingEntity);
}