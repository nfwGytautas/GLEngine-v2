#pragma once
#include "..\Component.h"
//Dependencies
#include <glm\glm.hpp>

struct CTransformation : Component
{
	void init() override;
	void update(float frameTime) override;

	glm::mat4 transformationMatrix;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	CTransformation();
	CTransformation(glm::vec3 mPosition, glm::vec3 mRotation, glm::vec3 mScale);

	virtual CTransformation* clone() { return new CTransformation(*this); }
};