#include "Model.h"
#include <iostream>
#include <tuple>

VAO::VAO()
	:ID(0), elementCount(0)
{
}

VAO::VAO(unsigned int ID, unsigned int elementCount)
	: ID(ID), elementCount(elementCount)
{
}

bool VAO::operator==(const VAO& rhs) const
{
	if (ID == rhs.ID && elementCount == rhs.elementCount)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ShadingMap::ShadingMap()
	:textureID(0), type(ShadingMapType::UNSPECIFIED)
{
}

ShadingMap::ShadingMap(unsigned int textureID, ShadingMapType type)
	:textureID(textureID), type(type)
{
}

bool ShadingMap::operator==(const ShadingMap& rhs)
{
	if (textureID == rhs.textureID && type == rhs.type)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Material::Material()
{}

void Material::addShadingMap(ShadingMap map)
{
	m_shaderMaps[(size_t)map.type] = map;
}

void Material::changeSpecularShininess(float value)
{
	m_shininess = value;
}

bool Material::operator==(const Material& rhs)
{
	for (int i = 0; i < (int)ShadingMapType::SIZE; i++)
	{
		if (m_shaderMaps[i] != rhs.m_shaderMaps[i])
		{
			return false;
		}
	}
	if (m_shininess == rhs.m_shininess)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Mesh::Mesh()
	:m_vertexArray(VAO(0, 0)), m_material(Material())
{
}

Mesh::Mesh(VAO& vao, Material& material)
	: m_vertexArray(vao), m_material(material)
{
}

void Mesh::setVAO(VAO vao)
{
	if (m_vertexArray != vao)
	{
		m_vertexArray = vao;
	}
}

void Mesh::setMaterial(Material material)
{
	if (m_material != material)
	{
		m_material = material;
	}
}

VAO& Mesh::getVAO()
{
	return m_vertexArray;
}

Material& Mesh::getMaterial()
{
	return m_material;
}

bool Mesh::operator==(const Mesh& rhs)
{
	if (m_vertexArray == rhs.m_vertexArray && m_material == rhs.m_material)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Model::Model()
{
}

void Model::addMesh(Mesh mesh)
{
	if (std::find(m_meshes.begin(), m_meshes.end(), mesh) == m_meshes.end()) {
		m_meshes.push_back(mesh);
	}
}

std::vector<Mesh>& Model::getMeshes()
{
	return m_meshes;
}
