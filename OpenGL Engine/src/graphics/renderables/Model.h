#pragma once

#ifdef NFW_DLL_EXPORT
#	define NFW_API __declspec(dllexport)
#else
#	define NFW_API __declspec(dllimport)
#endif

#include "..\mesh\Mesh.h"
#include "..\material\Material.h"

class NFW_API Model
{
public:
	Model(Mesh mesh, Material material);
	~Model();

	Mesh GetMesh()
	{
		return m_mesh;
	}

	Material GetMaterial()
	{
		return m_material;
	}

private:
	Mesh m_mesh;
	Material m_material;
};

