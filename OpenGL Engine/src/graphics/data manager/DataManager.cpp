#include "DataManager.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\gtypes\gTypes.h"

#include "..\FrameworkAssert.h"
#include "..\mesh\Mesh.h"

Mesh DataManager::LoadToVAO(std::vector<float> positions, std::vector<unsigned int> indices)
{
	unsigned int vaoID = createVAO();
	bindIndiceBuffer(indices);
	storeDataInAttributes(AttributeLocation::Position, positions);
	unbindVAO();
	return Mesh(vaoID, indices.size());
}

void DataManager::CleanUp()
{
	for (unsigned int x : m_vaos)
	{
		GLCall(glDeleteVertexArrays(1, &x));
	}
	for (unsigned int x : m_vbos)
	{
		GLCall(glDeleteBuffers(1, &x));
	}

	m_vaos.clear();
	m_vbos.clear();
}

unsigned int DataManager::createVAO()
{
	unsigned int vaoID;

	GLCall(glGenVertexArrays(1, &vaoID));
	m_vaos.push_back(vaoID);

	GLCall(glBindVertexArray(vaoID));

	return vaoID;
}
void DataManager::storeDataInAttributes(unsigned int location, std::vector<float> data)
{
	unsigned int vboID;

	GLCall(glGenBuffers(1, &vboID));
	m_vbos.push_back(vboID);

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW));

	GLCall(glVertexAttribPointer(
		location,
		3,
		GL_FLOAT,
		false,
		0,
		(const void*)0
	));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void DataManager::bindIndiceBuffer(std::vector<unsigned int> indices)
{
	unsigned int vboID;
	GLCall(glGenBuffers(1, &vboID));
	m_vbos.push_back(vboID);

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));
}

void DataManager::unbindVAO()
{
	GLCall(glBindVertexArray(0));
}











DataManager::DataManager()
{
}
DataManager::~DataManager()
{
}
