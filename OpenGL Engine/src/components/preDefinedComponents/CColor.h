#pragma once
#include "..\Component.h"
//Dependencies
#include <glm\glm.hpp>

struct CColor : Component
{
	glm::vec3 value;

	CColor() = default;
	CColor(const glm::vec3& mColor) : value{ mColor } {}
};