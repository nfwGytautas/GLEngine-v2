#include "DataManager.h"
#include <iostream>
#include <boost\filesystem.hpp>
#include <SOIL\SOIL\SOIL.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "OBJLoader.h"
#include "..\gtypes\gTypes.h"
#include "..\FrameworkAssert.h"
#include "..\..\components\Entity.h"
#include "..\..\components\PreDefinedComponents.h"
#include "..\..\maths\Maths.h"

void DataManager::loadMesh(Entity& mTarget, std::string mFilePath)
{
	OBJLoader::LoadOBJ(mFilePath);

	unsigned int vaoID = createVAO();
	bindIndiceBuffer(OBJLoader::loadedIndices);
	storeDataInAttributes(AttributeLocation::Position, 3, Maths::Vec3ToFloatVector(OBJLoader::loadedVertices));
	storeDataInAttributes(AttributeLocation::UVs, 2, Maths::Vec2ToFloatVector(OBJLoader::loadedUVs));
	storeDataInAttributes(AttributeLocation::Normal, 3, Maths::Vec3ToFloatVector(OBJLoader::loadedNormals));
	unbindVAO();

	mTarget.addComponent<CMesh>(vaoID, OBJLoader::loadedIndices.size());
}

unsigned int DataManager::loadMaterial(std::string mFilePath)
{
	auto boostFilePath = boost::filesystem::path(mFilePath);
	unsigned int textureID = 0;

	unsigned int formatFlag = 0;
	if (boostFilePath.extension() == ".bmp" || boostFilePath.extension() == ".png")
	{
		formatFlag = SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT;
	}
	else if (boostFilePath.extension() == ".dds")
	{
		formatFlag = SOIL_FLAG_DDS_LOAD_DIRECT;
	}

	textureID = SOIL_load_OGL_texture
	(
		boostFilePath.string().c_str(),
		SOIL_LOAD_AUTO,
		textureID,
		formatFlag
	);
	if (textureID == 0)
	{
		std::cout << "[Engine][Resource manager] SOIL loading error: " << SOIL_last_result() << std::endl;
		return 0;
	}
	else
	{
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	}
	m_textures.push_back(textureID);
	return textureID;
}

void DataManager::cleanUp()
{
	for (unsigned int x : m_vaos)
	{
		GLCall(glDeleteVertexArrays(1, &x));
	}
	for (unsigned int x : m_vbos)
	{
		GLCall(glDeleteBuffers(1, &x));
	}
	for (unsigned int x : m_textures)
	{
		GLCall(glDeleteBuffers(1, &x));
	}

	m_vaos.clear();
	m_vbos.clear();
	m_textures.clear();
}

unsigned int DataManager::createVAO()
{
	unsigned int vaoID;

	GLCall(glGenVertexArrays(1, &vaoID));
	m_vaos.push_back(vaoID);

	GLCall(glBindVertexArray(vaoID));

	return vaoID;
}
void DataManager::storeDataInAttributes(unsigned int location, unsigned int dataSize, std::vector<float> data)
{
	unsigned int vboID;

	GLCall(glGenBuffers(1, &vboID));
	m_vbos.push_back(vboID);

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW));

	GLCall(glVertexAttribPointer(
		location,
		dataSize,
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