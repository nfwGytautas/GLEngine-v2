#include "Camera.h"

#include "..\..\input\InputManager.h"

#include <iostream>

//TODO: This really should not be here
#include "Display.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>

Camera::Camera()
	:m_position(glm::vec3(0,10,5))
{
}
Camera::~Camera()
{
}

void Camera::Move()
{
	double xpos, ypos;
	InputManager::Mouse::getCursorPosition(xpos, ypos);
	InputManager::Mouse::centerCursorPosition();

	m_horizontalAngle += 0.005f * /*deltaTime */ float(1280 / 2 - xpos);
	m_verticalAngle += 0.005f * /*deltaTime */ float(720 / 2 - ypos);

	/*if (InputManager::Keyboard::isKeyDown(Key::KEY_W))
	{
		m_position += m_direction * Display::getDelta() * 20.0f;
	}
	else if (InputManager::Keyboard::isKeyDown(Key::KEY_S))
	{
		m_position -= m_direction * Display::getDelta() * 20.0f;
	}
	else if (InputManager::Keyboard::isKeyDown(Key::KEY_D))
	{
		m_position += m_right * Display::getDelta() * 20.0f;
	}
	else if (InputManager::Keyboard::isKeyDown(Key::KEY_A))
	{
		m_position -= m_right * Display::getDelta() * 20.0f;
	}*/
}

glm::mat4 Camera::viewMatrix()
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
