#include "BoundingObjects.h"
#include "..\..\Settings.h"

BoundingSphere::BoundingSphere()
{
}

bool BoundingSphere::insideFrustum()
{
	Frustum::CheckState state = Settings::frustum->sphereInFrustum(m_center, m_radius);
	if (state != Frustum::CheckState::OUTSIDE)
	{
		return false;
	}
	else
	{
		return true;
	}
}

BoundingBox::BoundingBox()
{
}

bool BoundingBox::insideFrustum()
{
	std::vector<glm::vec3> points;
	points.resize(8);
	points[0] = m_coordinate1;
	points[1] = m_coordinate2;
	points[2] = m_coordinate3;
	points[3] = m_coordinate4;
	points[4] = m_coordinate5;
	points[5] = m_coordinate6;
	points[6] = m_coordinate7;
	points[7] = m_coordinate8;
	Frustum::CheckState state = Settings::frustum->polygonInFrustum(points);
	if (state != Frustum::CheckState::OUTSIDE)
	{
		return false;
	}
	else
	{
		return true;
	}
}