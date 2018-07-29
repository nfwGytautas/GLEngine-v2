#include "DataManager.h"
#include <iostream>
#include <boost\filesystem.hpp>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
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

std::pair<unsigned int, unsigned int> DataManager::createFlatMesh(unsigned int vertexCount, unsigned int size)
{

	unsigned int count = vertexCount * vertexCount;

	std::vector<float> vertices;
	vertices.resize(count * 3);

	std::vector<float> normals;
	normals.resize(count * 3);

	std::vector<float> textureCoords;
	textureCoords.resize(count * 2);

	std::vector<unsigned int> indices;
	indices.resize(6 * (vertexCount - 1) * (vertexCount - 1));

	int vertexIndex = 0;
	for (unsigned int i = 0; i < vertexCount; i++) {
		for (unsigned int j = 0; j < vertexCount; j++) {
			vertices[vertexIndex * 3] = (float)j / ((float)vertexCount - 1) * size;
			vertices[vertexIndex * 3 + 1] = 0;
			vertices[vertexIndex * 3 + 2] = (float)i / ((float)vertexCount - 1) * size;
			normals[vertexIndex * 3] = 0;
			normals[vertexIndex * 3 + 1] = 1;
			normals[vertexIndex * 3 + 2] = 0;
			textureCoords[vertexIndex * 2] = (float)j / ((float)vertexCount - 1);
			textureCoords[vertexIndex * 2 + 1] = (float)i / ((float)vertexCount - 1);
			vertexIndex++;
		}
	}

	int index = 0;
	for (unsigned int gz = 0; gz < vertexCount - 1; gz++) {
		for (unsigned int gx = 0; gx < vertexCount - 1; gx++) {
			int topLeft = (gz * vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * vertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			indices[index++] = topLeft;
			indices[index++] = bottomLeft;
			indices[index++] = topRight;
			indices[index++] = topRight;
			indices[index++] = bottomLeft;
			indices[index++] = bottomRight;
		}
	}
	auto result = createMesh(vertices, normals, textureCoords, indices);
	return result;
}

std::pair<unsigned int, unsigned int> DataManager::createHeightMappedMesh(std::string mHeightMapFilePath, float mMaxHeight, unsigned int size, std::vector<std::vector<float>>& mCalculatedHeights)
{
	float MAX_PIXEL_COLOR = 256 * 256 * 256;
	auto boostFilePath = boost::filesystem::path(mHeightMapFilePath);
	ImageLoader::loadImage(boostFilePath.string(), boostFilePath.extension().string());
	unsigned int vertexCount = ImageLoader::height;
	std::vector<glm::vec3> heightMap;
	heightMap.resize(ImageLoader::height * ImageLoader::width);

	unsigned int k = 1;
	unsigned int hindex = 0;
	for (int j = 0; j < ImageLoader::height; j++)
	{
		for (int i = 0; i < ImageLoader::width; i++)
		{

			hindex = (j * ImageLoader::height) + i;

			heightMap[hindex].x = (float)ImageLoader::imageBuffer[k-1];
			heightMap[hindex].y = (float)ImageLoader::imageBuffer[k];
			heightMap[hindex].z = (float)ImageLoader::imageBuffer[k+1];

			k += 4;
		}
	}

	unsigned int count = vertexCount * vertexCount;

	std::vector<float> vertices;
	vertices.resize(count * 3);
	std::vector<float> normals;
	normals.resize(count * 3);
	std::vector<float> textureCoords;
	textureCoords.resize(count * 2);
	std::vector<unsigned int> indices;
	indices.resize(6 * (vertexCount - 1) * (vertexCount - 1));
	int vertexIndex = 0;
	mCalculatedHeights.resize(vertexCount);
	for (unsigned int i = 0; i < vertexCount; i++)
	{
		std::vector<float> pushResult;
		pushResult.resize(vertexCount);
		mCalculatedHeights[i] = pushResult;
	}
	float height = 0;	
	for (unsigned int i = 0; i < vertexCount; i++) {
		for (unsigned int j = 0; j < vertexCount; j++) {
			vertices[vertexIndex * 3] = (float)j / ((float)vertexCount - 1) * size;
			height = getHeight(j, i, heightMap, MAX_PIXEL_COLOR, mMaxHeight);
			mCalculatedHeights[j][i] = height;
			vertices[vertexIndex * 3 + 1] = height;
			vertices[vertexIndex * 3 + 2] = (float)i / ((float)vertexCount - 1) * size;
			glm::vec3 normal = calculateNormal(j, i, heightMap, MAX_PIXEL_COLOR, mMaxHeight);
			normals[vertexIndex * 3] = normal.x;
			normals[vertexIndex * 3 + 1] = normal.y;
			normals[vertexIndex * 3 + 2] = normal.z;
			textureCoords[vertexIndex * 2] = (float)j / ((float)vertexCount - 1);
			textureCoords[vertexIndex * 2 + 1] = (float)i / ((float)vertexCount - 1);
			vertexIndex++;
		}
	}

	int index = 0;
	for (unsigned int gz = 0; gz < vertexCount - 1; gz++) {
		for (unsigned int gx = 0; gx < vertexCount - 1; gx++) {
			int topLeft = (gz * vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * vertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			indices[index++] = topLeft;
			indices[index++] = bottomLeft;
			indices[index++] = topRight;
			indices[index++] = topRight;
			indices[index++] = bottomLeft;
			indices[index++] = bottomRight;
		}
	}
	ImageLoader::freeData();
	auto result = createMesh(vertices, normals, textureCoords, indices);
	return result;
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

glm::vec3 DataManager::calculateNormal(int x, int y, std::vector<glm::vec3>& mHeightMap, float maxPixelColor, int mMaxHeight)
{
	float heightL = getHeight(x - 1, y, mHeightMap, maxPixelColor, mMaxHeight);
	float heightR = getHeight(x + 1, y, mHeightMap, maxPixelColor, mMaxHeight);
	float heightD = getHeight(x, y-1, mHeightMap, maxPixelColor, mMaxHeight);
	float heightU = getHeight(x, y+1, mHeightMap, maxPixelColor, mMaxHeight);
	glm::vec3 result = glm::normalize(glm::vec3(heightL - heightR, 2, heightD - heightU));
	return result;
}

float DataManager::getHeight(int x, int y, std::vector<glm::vec3>& mHeightMap, float maxPixelColor, int mMaxHeight)
{
	if (x < 0 || x >= ImageLoader::height || y < 0 || y >= ImageLoader::height)
	{
		return 0.0f;
	}
	float height = (mHeightMap[x * ImageLoader::height + y].x * mHeightMap[x * ImageLoader::height + y].y * mHeightMap[x * ImageLoader::height + y].z);
	height = height * -4;
	height += (maxPixelColor / 2.0f);
	height /= (maxPixelColor / 2.0f);
	height *= mMaxHeight;
	return height;
}

DataManager::DataManager()
{
	createFallbacks();
}
DataManager::~DataManager()
{
}