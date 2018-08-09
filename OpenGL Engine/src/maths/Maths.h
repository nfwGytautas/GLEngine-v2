#pragma once

//TODO: Create my own math library
#include <glm\glm.hpp>

#include <vector>

class Maths
{
public:
	static glm::mat4 createTransformationMatrix(glm::vec2 translation, float rotation, glm::vec2 scale);
	static glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale);
	static double DegreesToRadians(double degrees);
	static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

	static std::vector<float> Vec3ToFloatVector(const std::vector<glm::vec3>& vecVector);
	static std::vector<float> Vec2ToFloatVector(const std::vector<glm::vec2>& vecVector);
};

