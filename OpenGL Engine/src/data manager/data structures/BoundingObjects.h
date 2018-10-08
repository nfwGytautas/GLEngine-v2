#pragma once
#include <glm/glm.hpp>
#include "Model.h"

class Frustum;

class BoundingObject
{
public:
	virtual bool insideFrustum() { return false; }
};

class BoundingSphere : BoundingObject
{
public:
	BoundingSphere();

	bool insideFrustum() override;
private:
	glm::vec3 m_center;
	float m_radius;
};

class BoundingBox : BoundingObject
{
public:
	BoundingBox();
	
	bool insideFrustum() override;
private:
	glm::vec3 m_coordinate1;
	glm::vec3 m_coordinate2;
	glm::vec3 m_coordinate3;
	glm::vec3 m_coordinate4;
	glm::vec3 m_coordinate5;
	glm::vec3 m_coordinate6;
	glm::vec3 m_coordinate7;
	glm::vec3 m_coordinate8;
};