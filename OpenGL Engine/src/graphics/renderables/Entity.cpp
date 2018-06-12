#include "Entity.h"



Entity::Entity(Model model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
	:m_model(model), m_position(position), m_rx(rotX), m_ry(rotY), m_rz(rotZ), m_scale(scale)
{
}
Entity::~Entity()
{
}

void Entity::IncreasePosition(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
}
void Entity::IncreaseRotation(float x, float y, float z)
{
	m_rx += x;
	m_ry += y;
	m_rz += z;
}