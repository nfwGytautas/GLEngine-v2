#pragma once
#include "..\Component.h"
//Dependencies
#include <glm\glm.hpp>
#include "CTransformation.h"
#include "CColor.h"

struct CLightEmiter : Component
{
	void init() override;

	glm::vec3 attenuation;
	glm::vec3 lightOffset;

	CTransformation* cTransform;
	CColor* cColor;
	CLightEmiter() : attenuation(1,0,0), lightOffset(0,0,0) {};

	virtual CLightEmiter* clone() { return new CLightEmiter(*this); }
};