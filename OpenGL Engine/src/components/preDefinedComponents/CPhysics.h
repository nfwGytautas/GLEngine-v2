#pragma once
#include "..\Component.h"
//Dependencies
#include <glm\glm.hpp>

struct CPhysics : Component
{
	CPhysics();
	~CPhysics();

	void init() override;

	bool affectedByGravity;

	glm::vec3 velocity;
};

