#pragma once
#include "..\Component.h"
//Dependencies
#include <glm\glm.hpp>
#include "CPosition.h"

class UpdateSystem;
struct CCamera : Component
{
	glm::mat4 viewMatrix;
	CPosition* cPosition;

	void init() override;

	virtual CCamera* clone() { return new CCamera(*this); }
private:
	glm::vec3 m_direction;
	glm::vec3 m_right;

	float m_horizontalAngle = 180.0f;
	float m_verticalAngle = 0.0f;

	float m_moveSpeed = 3.0f;
	float m_lookSpeed = 0.005f;

	friend UpdateSystem;
};