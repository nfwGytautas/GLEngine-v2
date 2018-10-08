#include "Frustum.h"
#include "..\Settings.h"
#include "..\components\preDefinedComponents\CCamera.h"

Frustum::Frustum()
{
}

Frustum::~Frustum()
{
}

void Frustum::calculatePlanes(CCamera* camera)
{
	float AspectRatio = (float)Settings::width / (float)Settings::height;
	float nh = glm::tan(glm::radians(Settings::FoV / 2)) * Settings::nearRenderPlane;
	float nw = nh * AspectRatio;

	float fh = glm::tan(glm::radians(Settings::FoV / 2)) * Settings::farRenderPlane;
	float fw = fh * AspectRatio;

	glm::vec3 Z = camera->cTransformation->position - camera->viewPoint;
	Z = glm::normalize(Z);

	glm::vec3 X = glm::cross(camera->up, Z);
	X = glm::normalize(X);

	glm::vec3 Y = glm::cross(Z, X);

	glm::vec3 fc = camera->cTransformation->position - Z * Settings::farRenderPlane;
	glm::vec3 nc = camera->cTransformation->position - Z * Settings::nearRenderPlane;

	// compute the 4 corners of the frustum on the far plane
	m_ftl = fc + Y * fh - X * fw;
	m_ftr = fc + Y * fh + X * fw;
	m_fbl = fc - Y * fh - X * fw;
	m_fbr = fc - Y * fh + X * fw;

	// compute the 4 corners of the frustum on the near plane
	m_ntl = nc + Y * nh - X * nw;
	m_ntr = nc + Y * nh + X * nw;
	m_nbl = nc - Y * nh - X * nw;
	m_nbr = nc - Y * nh + X * nw;

	m_planes[TOP].set3Points(m_ntr, m_ntl, m_ftl);
	m_planes[BOTTOM].set3Points(m_nbl, m_nbr, m_fbr);
	m_planes[LEFT].set3Points(m_ntl, m_nbl, m_fbl);
	m_planes[RIGHT].set3Points(m_nbr, m_ntr, m_fbr);
	m_planes[NEARP].set3Points(m_ntl, m_ntr, m_nbr);
	m_planes[FARP].set3Points(m_ftr, m_ftl, m_fbl);
}

Frustum::CheckState Frustum::pointInFrustum(glm::vec3& point)
{
	CheckState result = CheckState::INSIDE;
	for (int i = 0; i < 6; i++) {

		if (m_planes[i].distance(point) < 0)
			return CheckState::OUTSIDE;
	}
	return result;
}

Frustum::CheckState Frustum::sphereInFrustum(glm::vec3& point, float radius)
{
	float distance;
	CheckState result = CheckState::INSIDE;

	for (int i = 0; i < 6; i++) {
		distance = m_planes[i].distance(point);
		if (distance < -radius)
			return OUTSIDE;
		else if (distance < radius)
			result = INTERSECT;
	}
	return result;
}

Frustum::CheckState Frustum::polygonInFrustum(std::vector<glm::vec3>& polygonPoints)
{
	int result = INSIDE;
	int out;
	int in;

	for (int i = 0; i < 6; i++)
	{
		out = 0; in = 0;
		for (int k = 0; k < polygonPoints.size() && (in == 0 || out == 0); k++) 
		{
			if (m_planes[i].distance(polygonPoints[k]) < 0)
			{
				out++;
			}
			else
			{
				in++;
			}
		}
		if (!in)
		{
			return (OUTSIDE);
		}
		else if (out)
		{
			result = INTERSECT;
		}
	}

	return CheckState(result);
}


void Plane::set3Points(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3)
{
	glm::vec3 aux1, aux2;

	aux1 = v1 - v2;
	aux2 = v3 - v2;

	normal = glm::cross(aux2 , aux1);

	normal = glm::normalize(normal);
	point = v2;
	d = -(glm::dot(normal,point));
}

void Plane::setCoefficients(float a, float b, float c, float d)
{
	normal = glm::vec3(a, b, c);
	float l = normal.length();
	normal = glm::vec3(a / l, b / l, c / l);
	d = d / l;
}

float Plane::distance(glm::vec3 & p)
{
	return (d + glm::dot(normal, p));
}

Plane::Plane(glm::vec3 & v1, glm::vec3 & v2, glm::vec3 & v3)
{
	set3Points(v1, v2, v3);
}

Plane::Plane()
{
}