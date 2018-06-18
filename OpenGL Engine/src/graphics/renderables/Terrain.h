#pragma once

#include "..\mesh\Mesh.h"
#include "..\material\Material.h"

class Terrain
{
public:
	Terrain(int xPosition, int zPosition, Material texture);
	~Terrain();

	float GetX() const
	{
		return m_x;
	}
	float GetZ() const
	{
		return m_z;
	}
	Mesh GetMesh()
	{
		return m_mesh;
	}
	Material GetMaterial()
	{
		return m_texture;
	}

private:
	const float size = 800;
	const int vertexCount = 128;

	float m_x;
	float m_z;

	Mesh m_mesh;
	Material m_texture;

private:
	void GenerateTerrain();
};

