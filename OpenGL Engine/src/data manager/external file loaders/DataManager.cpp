#include "DataManager.h"
#include <iostream>
#include <thread>
#include <boost\filesystem.hpp>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\..\SGEDefs.h"
#include "OBJLoader.h"
#include "ImageLoader.h"
#include "ModelLoader.h"
#include "..\..\Settings.h"
#include "..\..\graphics\gtypes\gTypes.h"
#include "..\..\graphics\GraphicsAssert.h"
#include "..\..\components\Entity.h"
#include "..\..\components\PreDefinedComponents.h"


void calculateIndices(std::vector<unsigned int>& mIndices, unsigned int mVertexCount)
{
	int index = 0;
	for (unsigned int gz = 0; gz < mVertexCount - 1; gz++) {
		for (unsigned int gx = 0; gx < mVertexCount - 1; gx++) {
			int topLeft = (gz * mVertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * mVertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			mIndices[index++] = topLeft;
			mIndices[index++] = bottomLeft;
			mIndices[index++] = topRight;
			mIndices[index++] = topRight;
			mIndices[index++] = bottomLeft;
			mIndices[index++] = bottomRight;
		}
	}
}

VAO DataManager::createVAO(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& textureCoords, std::vector<unsigned int>& indices)
{
	unsigned int vaoID = createVAO();
	bindIndiceBuffer(indices);
	storeDataInAttributes(AttributeLocation::Position, 3, vertices);
	storeDataInAttributes(AttributeLocation::UVs, 2, textureCoords);
	storeDataInAttributes(AttributeLocation::Normal, 3, normals);
	unbindVAO();

	VAO result(vaoID, indices.size());

	SGE::Instances::instances->batchManagerInstance->addVAO(result);

	return result;
}

VAO DataManager::createVAO(std::string pathToFile) 
{
	if (m_VAOCache.find(pathToFile) == m_VAOCache.end())
	{
		if (OBJLoader::LoadOBJ(pathToFile))
		{
			VAO result = createVAO(OBJLoader::loadedVertices, OBJLoader::loadedNormals, OBJLoader::loadedUVs, OBJLoader::loadedIndices);
			SGE::Instances::instances->batchManagerInstance->addVAO(result);
			m_VAOCache[pathToFile] = result;
			return result;
		}
		else
		{
			VAO result(m_fallbackMeshID, m_fallbackMeshVertexCount);
			SGE::Instances::instances->batchManagerInstance->addVAO(result);
			m_VAOCache[pathToFile] = result;
			return result;
		}
	}
	else
	{
		return m_VAOCache[pathToFile];
	}
}

VAO DataManager::create2DQuad(std::vector<float>& vertices)
{
	unsigned int vaoID = createVAO();
	storeDataInAttributes(AttributeLocation::Position, 2, vertices);
	unbindVAO();
	return VAO(vaoID, vertices.size() / 2);
}

VAO DataManager::create3DCube(std::vector<float>& vertices)
{
	unsigned int vaoID = createVAO();
	storeDataInAttributes(AttributeLocation::Position, 3, vertices);
	unbindVAO();
	return VAO(vaoID, vertices.size() / 3);
}

std::tuple<unsigned int, unsigned int, unsigned int> DataManager::createSkybox()
{
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
	std::vector<std::string> cubeFiles = arrayToVector(Settings::skyboxFiles);
	unsigned int textureID = loadCubeMap(cubeFiles);
	std::vector<float> cubeMesh = arrayToVector(skyboxVertices);
	VAO cube = create3DCube(cubeMesh);
	std::tuple<unsigned int, unsigned int, unsigned int> result = std::make_tuple(cube.ID, cube.elementCount, textureID);
	return result;
}

unsigned int DataManager::createVBO(unsigned int floatCount)
{
	unsigned int vboID;

	GLCall(glGenBuffers(1, &vboID));
	m_vbos.push_back(vboID);

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, floatCount * 4, NULL, GL_STREAM_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	return vboID;
}

unsigned int DataManager::loadCubeMap(std::vector<std::string>& textureFiles)
{
	unsigned int textureID = 0;
	GLCall(glGenTextures(1, &textureID));
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, textureID));

	for (unsigned int i = 0; i < textureFiles.size(); i++)
	{
		auto boostFilePath = boost::filesystem::path(textureFiles[i]);
		ImageLoader::loadImage(boostFilePath.string(), boostFilePath.extension().string());
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, ImageLoader::width, ImageLoader::height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageLoader::imageBuffer));
		ImageLoader::freeData();
	}

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

	m_textures.push_back(textureID);
	return textureID;
}

unsigned int DataManager::loadTexture(std::string mFilePath)
{
	auto boostFilePath = boost::filesystem::path(mFilePath);
	if (ImageLoader::loadImage(boostFilePath.string(), boostFilePath.extension().string()))
	{
		unsigned int textureID = 0;
		GLCall(glGenTextures(1, &textureID));
		GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, ImageLoader::width, ImageLoader::height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageLoader::imageBuffer));
		textureSetup();
		m_textures.push_back(textureID);
		if (ImageLoader::imageBuffer)
		{
			ImageLoader::freeData();
		}
		return textureID;
	}
	else
	{
		return m_fallbackTexture;
	}
}

Model DataManager::loadModel(std::string pathToModel)
{
	if (m_modelCache.find(pathToModel) == m_modelCache.end())
	{
		ModelLoader::loadModel(pathToModel);
		auto boostFilePath = boost::filesystem::path(pathToModel);

		auto meshes = ModelLoader::modelMeshes;

		std::vector<Mesh> loadedMeshes;

		for (auto mesh : meshes)
		{
			Mesh loadedMesh;
			//TODO: Clean this up
			std::vector<float> vertices = Maths::Vec3ToFloatVector(mesh.positions);
			std::vector<float> normals = Maths::Vec3ToFloatVector(mesh.normals);
			std::vector<float> uvs = Maths::Vec2ToFloatVector(mesh.texCoords);
			VAO meshVAO = createVAO(vertices, normals, uvs, mesh.indices);
			loadedMesh.setVAO(meshVAO);

			Material meshMaterial;

			if (mesh.diffuse_map != "")
			{
				meshMaterial.addShadingMap(ShadingMap(loadTexture((boostFilePath.parent_path().string() + "/" + mesh.diffuse_map)), ShadingMapType::Diffuse));
			}
			if (mesh.specular_map != "")
			{
				meshMaterial.addShadingMap(ShadingMap(loadTexture((boostFilePath.parent_path().string() + "/" + mesh.specular_map)), ShadingMapType::Specular));
				meshMaterial.changeSpecularShininess(mesh.shininess);
			}
			
			loadedMesh.setMaterial(meshMaterial);

			loadedMeshes.push_back(loadedMesh);
		}
		Model loadedModel;
		for (auto mesh : loadedMeshes)
		{
			loadedModel.addMesh(mesh);
		}
		m_modelCache[pathToModel] = loadedModel;
		return loadedModel;
	}
	else
	{
		return m_modelCache[pathToModel];
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

glm::vec3 DataManager::calculateNormal(int x, int y, std::vector<glm::vec3>& mHeightMap, float maxPixelColor, float mMaxHeight)
{
	float heightL = getHeight(x - 1, y, mHeightMap, maxPixelColor, mMaxHeight);
	float heightR = getHeight(x + 1, y, mHeightMap, maxPixelColor, mMaxHeight);
	float heightD = getHeight(x, y - 1, mHeightMap, maxPixelColor, mMaxHeight);
	float heightU = getHeight(x, y + 1, mHeightMap, maxPixelColor, mMaxHeight);
	glm::vec3 result = glm::normalize(glm::vec3(heightL - heightR, 2, heightD - heightU));
	return result;
}

float DataManager::getHeight(int x, int y, std::vector<glm::vec3>& mHeightMap, float maxPixelColor, float mMaxHeight)
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