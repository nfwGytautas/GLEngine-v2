#include "Maths.h"

#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "..\graphics\display\Camera.h"

glm::mat4 Maths::CreateTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale)
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);
	glm::mat4 scaleMatrix = glm::scale(glm::vec3(scale, scale, scale));
	glm::mat4 xRotation = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 yRotation = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 zRotation = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
	glm::mat4 rotationMatrix = xRotation * yRotation * zRotation;

	glm::mat4 returnMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	return returnMatrix;
}

glm::mat4 Maths::CreateViewMatrix(Camera* camera)
{	
	//TODO: Clean this up, unnecesary indirection
	return camera->viewMatrix();
}

double Maths::DegreesToRadians(double degrees)
{
	return (degrees * (3.14159265359 / 180.0));
}

//TODO: Make this automatic in my own math library
//Creates a float vector from vec3
std::vector<float> Maths::Vec3ToFloatVector(const std::vector<glm::vec3>& vecVector)
{
	std::vector<float> returnVector;
	returnVector.reserve(vecVector.size() * 3);
	for (glm::vec3 x : vecVector)
	{
		returnVector.push_back(x.x);
		returnVector.push_back(x.y);
		returnVector.push_back(x.z);
	}
	return returnVector;
}
//Creates a float vector from vec2
std::vector<float> Maths::Vec2ToFloatVector(const std::vector<glm::vec2>& vecVector)
{
	std::vector<float> returnVector;
	returnVector.reserve(vecVector.size() * 2);
	for (glm::vec2 x : vecVector)
	{
		returnVector.push_back(x.x);
		returnVector.push_back(x.y);
	}
	return returnVector;
}