#include "Maths.h"
#include <iostream>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\Settings.h"


glm::mat4 Maths::createTransformationMatrix(glm::vec2 translation, float rotation, glm::vec2 scale)
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(translation, 0));
	glm::mat4 scaleMatrix = glm::scale(glm::vec3(scale.x, scale.y  * (Settings::width / Settings::height), 1.0f));
	glm::mat4 rotationMatrix = glm::rotate(glm::radians(rotation), glm::vec3(0, 0, 1));
	glm::mat4 returnMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	return returnMatrix;
}

glm::mat4 Maths::createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);
	glm::mat4 scaleMatrix = glm::scale(glm::vec3(scale.x, scale.y, scale.z));
	glm::mat4 xRotation = glm::rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0));
	glm::mat4 yRotation = glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0));
	glm::mat4 zRotation = glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
	glm::mat4 rotationMatrix = xRotation * yRotation * zRotation;

	glm::mat4 returnMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	return returnMatrix;
}

double Maths::DegreesToRadians(double degrees)
{
	return ((degrees * 3.14159265359) / 180.0);
}

float Maths::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
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