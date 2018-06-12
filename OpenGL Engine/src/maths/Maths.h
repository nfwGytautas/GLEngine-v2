#pragma once

//TODO: Create my own math library
#include <glm\glm.hpp>

class Maths
{
public:
	static glm::mat4 CreateTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale);
};

