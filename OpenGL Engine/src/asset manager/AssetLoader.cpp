#include "AssetLoader.h"
#include <iostream>

#include <glm\glm.hpp>
#include <Assimp/assimp/Importer.hpp>
#include <Assimp/assimp/scene.h>
#include <Assimp/assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb image\stb_image.h"

#include "..\algorithm\Algorithm.h"

Asset* AssetLoader::loadAsset(std::string filePath, std::string name, AssetType type)
{
	switch (type)
	{
	case AssetType::Model:
		return loadModelAsset(filePath, name);
	case AssetType::Image:
		return loadImageAsset(filePath, name);
	case AssetType::UNKNOWN:
		throw "AssetType UNKNOWN";
		return nullptr;
	default:
		throw "AssetType NOT DEFINED";
		return nullptr;
	}
}

AssetLoader::AssetLoader()
{
}
AssetLoader::~AssetLoader()
{
	for(Asset* asset : m_LoadedAssets)
	{
		delete asset;
	}
}

//======================================================================================================
//IMAGE
//======================================================================================================

Asset* AssetLoader::loadImageAsset(std::string filePath, std::string name)
{
	//Image data
	unsigned char* imageBuffer;
	int width;
	int height;
	int BPP;

	//Get image information
	try
	{
		//Check to see if file exists
		if (!fexists(filePath))
		{
			std::cout << "[Engine][Asset loader] Error: Loading image! File does not exist: " << filePath << std::endl;
			return false;
		}

		std::vector<std::string> splitDirectory = ssplit(filePath, '/');

		if (splitDirectory[splitDirectory.size()-1] == ".png")
		{
			stbi_set_flip_vertically_on_load(1);
		}
		else
		{
			stbi_set_flip_vertically_on_load(0);
		}

		imageBuffer = stbi_load(filePath.c_str(), &width, &height, &BPP, 4);			
	}
	catch (...)
	{
		std::cout << "[Engine][Data manager] Error: Loading image!"<< stbi_failure_reason() << std::endl;
		return nullptr;
	}

	//Construct asset
	AImage* image = new AImage(width, height, BPP, imageBuffer);
	m_LoadedAssets.push_back(image);
	return image;

	return nullptr;
}
void AssetLoader::freeData(unsigned char* buffer)
{
	stbi_image_free(buffer);
}

//======================================================================================================
//MODEL
//======================================================================================================

Asset* AssetLoader::loadModelAsset(std::string filePath, std::string name)
{
	//Mesh data
	std::vector<RawMeshData> modelMeshes;

	//Get the mesh information
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "[SGE] Error: " << importer.GetErrorString() << " while loading model: " << filePath << std::endl;
		return;
	}
	ModelLoadingImplementation::processNode(scene->mRootNode, scene, modelMeshes);

	//Construct asset

	return nullptr;
}

namespace ModelLoadingImplementation
{
	void processNode(aiNode* node, const aiScene* scene, std::vector<RawMeshData>& modelMeshes)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			modelMeshes.push_back(processMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene, modelMeshes);
		}
	}

	void processMinMax(glm::vec3 & maxValues, glm::vec3 & minValues, const glm::vec3& currentVertex)
	{
		//Max values
		if (maxValues.x < currentVertex.x)
		{
			maxValues.x = currentVertex.x;
		}
		if (maxValues.y < currentVertex.y)
		{
			maxValues.y = currentVertex.y;
		}
		if (maxValues.z < currentVertex.z)
		{
			maxValues.z = currentVertex.z;
		}
		//Min values
		if (minValues.x > currentVertex.x)
		{
			minValues.x = currentVertex.x;
		}
		if (minValues.y > currentVertex.y)
		{
			minValues.y = currentVertex.y;
		}
		if (minValues.z > currentVertex.z)
		{
			minValues.z = currentVertex.z;
		}
	}

	RawMeshData processMesh(aiMesh* mesh, const aiScene* scene)
	{
		RawMeshData result;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;
		std::vector<unsigned int> indices;
		float width = 0;
		float height = 0;

		glm::vec3 minValues(mesh->mVertices[0].x, mesh->mVertices[0].y, mesh->mVertices[0].z);
		glm::vec3 maxValues(mesh->mVertices[0].x, mesh->mVertices[0].y, mesh->mVertices[0].z);

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{

			positions.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
			normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
			if (mesh->mTextureCoords[0])
			{
				texCoords.push_back(glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
			}
			else
			{
				texCoords.push_back(glm::vec2(0.0f, 0.0f));
			}

		}
		result.positions = positions;
		result.normals = normals;
		result.texCoords = texCoords;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		result.indices = indices;
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			loadMaterialTextures(material, aiTextureType_DIFFUSE, result);
			loadMaterialTextures(material, aiTextureType_SPECULAR, result);
		}
		result.width = glm::abs(minValues.x) + glm::abs(maxValues.x);
		result.height = glm::abs(minValues.y) + glm::abs(maxValues.y);
		result.depth = glm::abs(minValues.z) + glm::abs(maxValues.z);
		return result;
	}

	void loadMaterialTextures(aiMaterial* mat, aiTextureType type, RawMeshData& target)
	{
		if (mat->GetTextureCount(type) > 0)
		{
			aiString str;
			mat->GetTexture(type, 0, &str);
			if (type == aiTextureType_DIFFUSE)
			{
				target.diffuse_map = std::string(str.C_Str());
			}
			else if (type == aiTextureType_SPECULAR)
			{
				target.specular_map = std::string(str.C_Str());
				float value = 0.0f;
				mat->Get(AI_MATKEY_SHININESS, value);
				target.shininess = value;
			}
		}
	}
}