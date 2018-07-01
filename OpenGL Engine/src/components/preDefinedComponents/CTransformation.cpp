#include "CTransformation.h"
#include "..\Entity.h"
#include "..\..\maths\Maths.h"

void CTransformation::init()
{
	if (!entity->hasComponent<CPosition>())
	{
		entity->addComponent<CPosition>(glm::vec3(0, 0, 0));
	}
	cPosition = &entity->getComponent<CPosition>();
}

void CTransformation::update(float frameTime)
{
	transformationMatrix = Maths::CreateTransformationMatrix(cPosition->value, glm::vec3(rotationX, rotationY, rotationZ), scale);
}

CTransformation::CTransformation(float mXRotation, float mYRotation, float mZRotation, float mScale)
	: rotationX{ mXRotation }, rotationY{ mYRotation }, rotationZ{ mZRotation }, scale{ mScale }
{}