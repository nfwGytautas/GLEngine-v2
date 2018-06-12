#include "Maths.h"

#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>

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
