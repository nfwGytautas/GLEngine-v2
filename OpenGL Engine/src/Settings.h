#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "components\Entity.h"
#include "components\PreDefinedComponents.h"

struct Settings
{
	static unsigned int width;
	static unsigned int height;
	static const char* title;
	static bool fullscreen;

	static glm::vec3 skyColor;
	static float gravity;
	static CCamera* camera;
	static float cameraSensetivity;
	static std::vector<float> guiQuad;

	static float FoV;
	static float nearRenderPlane;
	static float farRenderPlane;

	static std::string skyboxFiles[6];
};