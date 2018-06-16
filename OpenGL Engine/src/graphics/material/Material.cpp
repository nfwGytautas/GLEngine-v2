#include "Material.h"


Material::Material(unsigned int id)
	:m_textureID(id), m_shineDamper(1), m_reflectivity(0)
{
}

Material::Material(unsigned int id, float shineDamper, float reflectivity)
	: m_textureID(id), m_shineDamper(shineDamper), m_reflectivity(reflectivity)
{
}

Material::~Material()
{
}
