#pragma once
#include "..\Component.h"
//Dependencies
#include <glm\glm.hpp>
#include "CTransformation.h"

class UpdateSystem;
struct CCamera : Component
{
	void init() override;
	void update(float frameTime) override;

	void hookTo(Entity* mEntity, float mDistanceToHook, float mAngleAroundHook);

	CTransformation* cTransformation;
	glm::mat4 viewMatrix;
	glm::vec3 viewDirection;
	glm::vec3 viewPoint;
	glm::vec3 up;
	glm::vec3 right;
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