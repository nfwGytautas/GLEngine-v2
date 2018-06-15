#pragma once

//TODO: Create my own math library
#include <glm\glm.hpp>

#include <vector>

class Camera;

class Maths
{
public:
	static glm::mat4 CreateTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale);
	static glm::mat4 CreateViewMatrix(Camera* camera);
	static double DegreesToRadians(double degrees);

	static std::vector<float> Vec3ToFloatVector(const std::vector<glm::vec3>& vecVector);
	static std::vector<float> Vec2ToFloatVector(const std::vector<glm::vec2>& vecVector);
};

