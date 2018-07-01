#pragma once
#include "..\Component.h"
//Dependencies
#include <glm\glm.hpp>

struct CPosition : Component
{
	void init() override;

	glm::vec3 value;

	CPosition() = default;
	CPosition(const glm::vec3& mPosition);
};