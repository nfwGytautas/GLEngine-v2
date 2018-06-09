#pragma once

#ifdef NFW_DLL_EXPORT
#	define NFW_API __declspec(dllexport)
#else
#	define NFW_API __declspec(dllimport)
#endif

class NFW_API Mesh
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

