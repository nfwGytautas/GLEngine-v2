#include "CMesh.h"
#include <functional>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\..\graphics\FrameworkAssert.h"
#include "..\..\data manager\BatchManager.h"

void CMesh::use()
{
	GLCall(glBindVertexArray(m_vaoID));
}

CMesh::CMesh(unsigned int mVaoID, unsigned int mVertexCount)
	: m_vaoID{ mVaoID }, vertexCount{ mVertexCount }
{}

CMesh::CMesh(std::pair<unsigned int, unsigned int> mLoaderResult)
	: m_vaoID{ mLoaderResult.first }, vertexCount{ mLoaderResult.second }
{}

size_t CMesh::hash() const
{
	size_t res = 17;
	res = res * 31 + std::hash<unsigned int>()(vertexCount);
	res = res * 31 + std::hash<unsigned int>()(m_vaoID);
	return res;
}