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
	:m_vertexArray(VAO(0, 0)), m_material(Material()), m_width(0), m_height(0)
{
}

Mesh::Mesh(VAO& vao, Material& material)
	: m_vertexArray(vao), m_material(material), m_width(0), m_height(0)
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

void Mesh::setWidth(float width)
{
	m_width = width;
}

void Mesh::setHeight(float height)
{
	m_height = height;
}

VAO& Mesh::getVAO()
{
	return m_vertexArray;
}

Material& Mesh::getMaterial()
{
	return m_material;
}

float Mesh::getWidth()
{
	return m_width;
}

float Mesh::getHeight()
{
	return m_height;
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
	:m_width(0), m_height(0)
{
}

void Model::addMesh(Mesh mesh)
{
	if (std::find(m_meshes.begin(), m_meshes.end(), mesh) == m_meshes.end()) {
		m_meshes.push_back(mesh);
		if (m_width < mesh.getWidth())
		{
			m_width = mesh.getWidth();
		}
		if (m_height < mesh.getHeight())
		{
			m_height = mesh.getHeight();
		}
	}
}

float Model::getWidth() const
{
	return m_width;
}

float Model::getHeight() const
{
	return m_height;
}

std::vector<Mesh>& Model::getMeshes()
{
	return m_meshes;
}

Mesh Model::getMeshByVAO(VAO vao)
{
	for (Mesh mesh : m_meshes)
	{
		if (mesh.getVAO() == vao)
		{
			return mesh;
		}
	}
}
