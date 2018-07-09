#include "DataManager.h"
#include <iostream>
#include <boost\filesystem.hpp>
#include <SOIL\SOIL\SOIL.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "OBJLoader.h"
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
		return m_fallbackTexture;
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

std::vector<float> DataManager::fallbackTexture()
{
	std::vector<float> tempBuffer;
	tempBuffer.reserve(8 * 8 * 8 * 8);
	//Starts with pink block
	bool drawPink = true;
	//8 Lines
	for (int i = 0; i < 8; i++)
	{
		// 8 Collumns
		for (int j = 0; j < 8; j++)
		{
			//8 Pixels in a block
			for (int k = 0; k < 8; k++)
			{
				//Alternating blocks
				if (drawPink)
				{
					for (int z = 0; z < 8; z++)
					{
						//Pink pixel
						tempBuffer.push_back(255);
						tempBuffer.push_back(0);
						tempBuffer.push_back(165);
					}
					drawPink = false;
				}
				else
				{
					for (int z = 0; z < 8; z++)
					{
						//Black pixel
						tempBuffer.push_back(0);
						tempBuffer.push_back(0);
						tempBuffer.push_back(0);
					}
					drawPink = true;
				}
			}
		}
		drawPink = !drawPink;
	}
	m_textures.push_back(m_fallbackTexture);
	return tempBuffer;
}
void DataManager::fallbackMesh()
{
	OBJLoader::loadFallbackMesh();
}
void DataManager::createFallbacks()
{
	//Fallback texture
	GLCall(glGenTextures(1, &m_fallbackTexture));
	glBindTexture(GL_TEXTURE_2D, m_fallbackTexture);
	auto tempBuffer = fallbackTexture();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_FLOAT, &tempBuffer[0]);
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	//Fallback mesh
	unsigned int vaoID = createVAO();
	fallbackMesh();
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