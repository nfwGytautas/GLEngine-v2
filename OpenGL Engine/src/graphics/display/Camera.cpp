#include "Camera.h"

#include "..\..\input\InputManager.h"

#include <iostream>

//TODO: This really should not be here
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>

Camera::Camera()
	:m_position(glm::vec3(0,0,5))
{
}
Camera::~Camera()
{
}

void Camera::Move()
{
	double xpos, ypos;
	InputManager::Mouse::GetCursorPosition(xpos, ypos);
	InputManager::Mouse::CenterCursorPosition();

	m_horizontalAngle += 0.005f * /*deltaTime */ float(1280 / 2 - xpos);
	m_verticalAngle += 0.005f * /*deltaTime */ float(720 / 2 - ypos);

	if (InputManager::Keyboard::IsKeyDown(Key::KEY_S))
	{
		m_position.z += 0.02f;
	}
	if (InputManager::Keyboard::IsKeyDown(Key::KEY_W))
	{
		m_position.z -= 0.02f;
	}
	if (InputManager::Keyboard::IsKeyDown(Key::KEY_D))
	{
		m_position.x += 0.02f;
	}
	if (InputManager::Keyboard::IsKeyDown(Key::KEY_A))
	{
		m_position.x -= 0.02f;
	}
}

glm::mat4 Camera::ViewMatrix()
{
	//TODO: This method probably should be done elsewhere later

	m_direction = glm::vec3(
		cos(m_verticalAngle) * sin(m_horizontalAngle),
		sin(m_verticalAngle),
		cos(m_verticalAngle) * cos(m_horizontalAngle)
	);

	m_right = glm::vec3(
		sin(m_horizontalAngle - 3.14f / 2.0f),
		0,
		cos(m_horizontalAngle - 3.14f / 2.0f)
	);

	glm::vec3 up = glm::cross(m_right, m_direction);

	glm::mat4 ViewMatrix = glm::lookAt(
		m_position,
		m_position + m_direction,
		up
	);

	return ViewMatrix;
}
