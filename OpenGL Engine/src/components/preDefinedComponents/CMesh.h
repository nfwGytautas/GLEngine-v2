#pragma once
#include "..\Component.h"
//Dependencies
#include <utility>
class BatchManager;

struct CMesh : Component
{
	void use();

	unsigned int vertexCount;

	CMesh(unsigned int mVaoID, unsigned int mVertexCount);
	CMesh(std::pair<unsigned int, unsigned int> mLoaderResult);

	size_t hash() const;
	bool operator==(const CMesh& mesh) const
	{
		if (hash() == mesh.hash())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	unsigned int m_vaoID;
	friend BatchManager;
};