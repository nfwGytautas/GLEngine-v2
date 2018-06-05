#pragma once


class Mesh
{
public:
	Mesh(unsigned int vertexArray, unsigned int vertexCount);
	~Mesh();

	unsigned int GetRenderID()
	{
		return m_vaoID;
	}
	unsigned int GetVertexCount()
	{
		return m_vertexCount;
	}

private:
	unsigned int m_vaoID;
	unsigned int m_vertexCount;
};

