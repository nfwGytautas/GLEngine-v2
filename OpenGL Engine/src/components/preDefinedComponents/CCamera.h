#pragma once
#include "..\Component.h"
//Dependencies
#include <glm\glm.hpp>
#include "CTransformation.h"

class UpdateSystem;
struct CCamera : Component
{
	glm::mat4 viewMatrix;
	CTransformation* cTransformation;

	void init() override;
	void hookTo(Entity* mEntity, float mDistanceToHook, float mAngleAroundHook);

	glm::vec3 viewDirection;
	float distanceToHook;
	float angleAroundHook;
	float pitch = 0.0f;
	float yaw = 0.0f;

	virtual CCamera* clone() { return new CCamera(*this); }
private:

	float m_moveSpeed = 3.0f;
	float m_lookSpeed = 0.005f;

	Entity* m_hookedTo;

	friend UpdateSystem;
};