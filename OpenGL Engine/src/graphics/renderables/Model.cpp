#include "Model.h"

#include <boost/functional/hash.hpp>

Model::Model(Mesh mesh, Material material)
	:m_mesh(mesh), m_material(material)
{
}


Model::~Model()
{
}

size_t Model::GetHash() const
{
	std::size_t seed = 0;

	//Mesh
	boost::hash_combine(seed, boost::hash_value(m_mesh.GetRenderID()));
	boost::hash_combine(seed, boost::hash_value(m_mesh.GetVertexCount()));
												
	//Material									
	boost::hash_combine(seed, boost::hash_value(m_material.GetTextureID()));
	boost::hash_combine(seed, boost::hash_value(m_material.GetShineDamper()));
	boost::hash_combine(seed, boost::hash_value(m_material.GetReflectivity()));

	return seed;
}

bool Model::operator==(const Model & mod) const
{
	if (mod.GetHash() == GetHash())
	{
		return true;
	}
	else
	{
		return false;
	}
}
