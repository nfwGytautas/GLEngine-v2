#pragma once
#include "..\Component.h"
//Dependencies
#include <glm\glm.hpp>
#include "CPosition.h"

struct CTransformation : Component
{
	void init() override;
	void update(float frameTime) override;

	glm::mat4 transformationMatrix;
	CPosition* cPosition;
	//Could be seperate componenets
	float rotationX, rotationY, rotationZ;
	float scale;

	CTransformation(float mXRotation, float mYRotation, float mZRotation, float mScale);

	virtual CTransformation* clone() { return new CTransformation(*this); }
};