#pragma once
#include <glm\glm.hpp>
#include "components\Entity.h"
#include "components\PreDefinedComponents.h"

struct Settings
{
	static glm::vec3 skyColor;
	static float gravity;
	static CCamera* camera;
	static float cameraSensetivity;
};