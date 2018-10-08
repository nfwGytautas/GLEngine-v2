#pragma once
#include <vector>
#include <glm/glm.hpp>

struct CCamera;
class Plane
{
public:
	glm::vec3 normal;
	glm::vec3 point;
	float d;

	void set3Points(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3);
	void setCoefficients(float a, float b, float c, float d);
	float distance(glm::vec3& p);

	Plane(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3);
	Plane();
};

class Frustum
{
public:
	enum CheckState {OUTSIDE, INTERSECT, INSIDE};

	void calculatePlanes(CCamera* camera);

	CheckState pointInFrustum(glm::vec3& point);
	CheckState sphereInFrustum(glm::vec3& point, float radius);
	CheckState polygonInFrustum(std::vector<glm::vec3>& polygonPoints);

	Frustum();
	~Frustum();
private:
	Plane m_planes[6];

	glm::vec3 m_ntl, m_ntr, m_nbl, m_nbr, m_ftl, m_ftr, m_fbl, m_fbr;

	enum
	{
		TOP = 0,
		BOTTOM = 1,
		LEFT = 2,
		RIGHT = 3,
		NEARP = 4,
		FARP = 5
	};
};

