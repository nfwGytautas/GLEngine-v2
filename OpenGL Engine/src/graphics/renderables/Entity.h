#pragma once

#include "Model.h"
#include <glm/glm.hpp>

class Entity
{
public:
	Entity(Model model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
	~Entity();

	void IncreasePosition(float x, float y, float z);
	void IncreaseRotation(float x, float y, float z);

	//TODO: Move rendering to this class
	Model GetModel()
	{
		return m_model;
	}
	glm::vec3 GetPosition()
	{
		return m_position;
	}
	glm::vec3 GetRotation()
	{
		return glm::vec3(m_rx, m_ry, m_rz);
	}
	float GetScale()
	{
		return m_scale;
	}
private:
	Model m_model;
	glm::vec3 m_position;
	float m_rx, m_ry, m_rz;
	float m_scale;
};

