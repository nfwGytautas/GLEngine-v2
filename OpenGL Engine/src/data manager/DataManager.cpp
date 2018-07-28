#include "DataManager.h"
#include <iostream>
#include <boost\filesystem.hpp>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "OBJLoader.h"
#include "ImageLoader.h"
#include "..\graphics\gtypes\gTypes.h"
#include "..\graphics\FrameworkAssert.h"
#include "..\components\Entity.h"
#include "..\components\PreDefinedComponents.h"

std::pair<unsigned int, unsigned int> DataManager::loadMesh(std::string mFilePath)
{
	if(m_meshCache.find(mFilePath) == m_meshCache.end())
	{
		if(OBJLoader::LoadOBJ(mFilePath))
		{
			unsigned int vaoID = createVAO();
			bindIndiceBuffer(OBJLoader::loadedIndices);
			storeDataInAttributes(AttributeLocation::Position, 3, OBJLoader::loadedVertices);
			storeDataInAttributes(AttributeLocation::UVs, 2, OBJLoader::loadedUVs);
			storeDataInAttributes(AttributeLocation::Normal, 3, OBJLoader::loadedNormals);
			unbindVAO();

			std::pair<unsigned int, unsigned int> result = std::make_pair(vaoID, OBJLoader::loadedIndices.size());
			m_meshCache[mFilePath] = result;
			return result;
		}
		else
		{
			std::pair<unsigned int, unsigned int> result = std::make_pair(m_fallbackMeshID, m_fallbackMeshVertexCount);
			m_meshCache[mFilePath] = result;
			return result;
		}
	}
	else
	{
		return m_meshCache[mFilePath];
	}
}

std::pair<unsigned int, unsigned int> DataManager::createMesh(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& textureCoords, std::vector<unsigned int>& indices)
{
	unsigned int vaoID = createVAO();
	bindIndiceBuffer(indices);
	storeDataInAttributes(AttributeLocation::Position, 3, vertices);
	storeDataInAttributes(AttributeLocation::UVs, 2, textureCoords);
	storeDataInAttributes(AttributeLocation::Normal, 3, normals);
	unbindVAO();

	std::pair<unsigned int, unsigned int> result = std::make_pair(vaoID, indices.size());
	return result;
}

unsigned int DataManager::loadImage(std::string mFilePath)
{
	auto boostFilePath = boost::filesystem::path(mFilePath);
	if (m_imageCache.find(mFilePath) == m_imageCache.end())
	{
		if (ImageLoader::loadImage(boostFilePath.string(), boostFilePath.extension().string()))
		{
			unsigned int textureID = 0;
			GLCall(glGenTextures(1, &textureID));
			GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, ImageLoader::width, ImageLoader::height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageLoader::imageBuffer));
			textureSetup();
			m_textures.push_back(textureID);
			m_imageCache[mFilePath] = textureID;
			if (ImageLoader::imageBuffer)
			{
				ImageLoader::freeData();
			}
			return textureID;
		}
		else
		{
			m_imageCache[mFilePath] = m_fallbackTexture;
			return m_fallbackTexture;
		}
	}
	else
	{
		return m_imageCache[mFilePath];
	}
}

unsigned int DataManager::loadMaterial(std::string mFilePath)
{
	auto boostFilePath = boost::filesystem::path(mFilePath);
	if (m_materialCache.find(mFilePath) == m_materialCache.end())
	{
		if (ImageLoader::loadImage(boostFilePath.string(), boostFilePath.extension().string()))
		{
			unsigned int textureID = 0;
			GLCall(glGenTextures(1, &textureID));
			GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, ImageLoader::width, ImageLoader::height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageLoader::imageBuffer));
			textureSetup();
			m_textures.push_back(textureID);
			m_materialCache[mFilePath] = textureID;
			if (ImageLoader::imageBuffer)
			{
				ImageLoader::freeData();
			}
			return textureID;
		}
		else
		{
			m_materialCache[mFilePath] = m_fallbackTexture;
			return m_fallbackTexture;
		}
	}
	else
	{
		return m_materialCache[mFilePath];
	}
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
		GLCall(glDeleteTextures(1, &x));
	}

	m_vaos.clear();
	m_vbos.clear();
	m_textures.clear();

	m_meshCache.clear();
	m_imageCache.clear();
	m_materialCache.clear();
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

void DataManager::textureSetup()
{
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

void DataManager::createFallbacks()
{
	//Fallback texture
	GLCall(glGenTextures(1, &m_fallbackTexture));
	glBindTexture(GL_TEXTURE_2D, m_fallbackTexture);
	ImageLoader::loadFallbackImage();
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageLoader::width, ImageLoader::height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageLoader::imageBuffer));
	textureSetup();

	//Fallback mesh
	unsigned int vaoID = createVAO();
	OBJLoader::loadFallbackMesh();
	bindIndiceBuffer(OBJLoader::loadedIndices);
	storeDataInAttributes(AttributeLocation::Position, 3, OBJLoader::loadedVertices);
	storeDataInAttributes(AttributeLocation::UVs, 2, OBJLoader::loadedUVs);
	storeDataInAttributes(AttributeLocation::Normal, 3, OBJLoader::loadedNormals);
	unbindVAO();

	m_fallbackMeshID = vaoID;
	m_fallbackMeshVertexCount = OBJLoader::loadedIndices.size();
}

DataManager::DataManager()
{
	createFallbacks();
}
DataManager::~DataManager()
{
}