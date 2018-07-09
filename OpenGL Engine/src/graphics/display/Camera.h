#pragma once

#include <glm\glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void Move();
	glm::mat4 viewMatrix();

	//TODO: Move this to the engine
	glm::vec3 GetPosition()
	{
		return m_position;
	}
	glm::vec3 GetDirection()
	{
		return m_direction;
	}
private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_right;

	float m_horizontalAngle = 180.0f;
	float m_verticalAngle = 0.0f;

	float m_moveSpeed = 3.0f;
	float m_lookSpeed = 0.005f;
};

