#include "CTransformation.h"
#include "..\Entity.h"
#include "..\..\maths\Maths.h"

void CTransformation::init()
{
	entity->addGroup(EntityGroups::StaticEntity);
}

void CTransformation::update(float frameTime)
{
	transformationMatrix = Maths::createTransformationMatrix
	(
		position,
		rotation,
		scale
	);
}

CTransformation::CTransformation()
	: position(0,0,0), rotation(0,0,0), scale(1,1,1)
{}

CTransformation::CTransformation(glm::vec3 mPosition, glm::vec3 mRotation, glm::vec3 mScale)
	: position(mPosition), rotation(mRotation), scale(mScale)
{}