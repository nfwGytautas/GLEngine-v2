#pragma once

#include <glm\glm.hpp>

//TODO: Multiple light types e.g Static, Free, Point
class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	~Light();

	//TODO: Change the class so that geters would not be needed
	glm::vec3 GetPosition()
	{
		return m_position;
	}
	glm::vec3 GetColor()
	{
		return m_color;
	}
private:
	glm::vec3 m_position;
	glm::vec3 m_color;
};

