#include "CPosition.h"
#include "..\Entity.h"

void CPosition::init()
{
	entity->addGroup(EntityGroups::StaticEntity);
}

CPosition::CPosition(const glm::vec3 & mPosition)
	: value{ mPosition }
{}