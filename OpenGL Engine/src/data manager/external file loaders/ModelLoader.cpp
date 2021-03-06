#include "ModelLoader.h"
#include <iostream>

std::vector<RawMeshData> ModelLoader::modelMeshes;

void ModelLoader::loadModel(std::string& path)
{
	modelMeshes.clear();
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "[SGE] Error: " << importer.GetErrorString() << " while loading model: " << path << std::endl;
		return;
	}
	processNode(scene->mRootNode, scene);
}

void ModelLoader::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		modelMeshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

void ModelLoader::processMinMax(glm::vec3 & maxValues, glm::vec3 & minValues, const glm::vec3& currentVertex)
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

RawMeshData ModelLoader::processMesh(aiMesh* mesh, const aiScene* scene)
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

void ModelLoader::loadMaterialTextures(aiMaterial* mat, aiTextureType type,RawMeshData& target)
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