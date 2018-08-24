#pragma once
#include "..\Component.h"
//Dependencies
#include <glm\glm.hpp>
#include "CTransformation.h"

struct CLightEmiter : Component
{
	void init() override;

	glm::vec3 attenuation;
	glm::vec3 lightOffset;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	CTransformation* cTransform;
	CLightEmiter() : attenuation(1,0,0), lightOffset(0,0,0), ambient(0.2f, 0.2f, 0.2f), diffuse(0.5f, 0.5f, 0.5f), specular(1.0f, 1.0f, 1.0f) {};

	virtual CLightEmiter* clone() { return new CLightEmiter(*this); }
};