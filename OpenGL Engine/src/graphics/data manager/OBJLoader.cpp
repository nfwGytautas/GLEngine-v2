#include "OBJLoader.h"
#include <iostream>
#include <Assimp\assimp\Importer.hpp>
#include <Assimp\assimp\scene.h>
#include <Assimp\assimp\postprocess.h>

std::vector<glm::vec3> OBJLoader::loadedVertices;
std::vector<glm::vec3> OBJLoader::loadedNormals;
std::vector<glm::vec2> OBJLoader::loadedUVs;
std::vector<unsigned int> OBJLoader::loadedIndices;

void OBJLoader::LoadOBJ(std::string filePath)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(
		filePath,
		aiProcess_Triangulate |
		aiProcess_GenNormals |
		aiProcess_JoinIdenticalVertices
	);

	if (!scene)
	{
		std::cout << "[Engine][Resource manager][OBJLoader] Assimp error." << importer.GetErrorString() << "\n";
		return;
	}

	for (unsigned int meshIdx = 0; meshIdx < scene->mNumMeshes; meshIdx++)
	{
		aiMesh* mesh = scene->mMeshes[meshIdx];

		for (unsigned int verticeIdx = 0; verticeIdx < mesh->mNumVertices; verticeIdx++)
		{
			glm::vec3 vertice;
			vertice.x = mesh->mVertices[verticeIdx].x;
			vertice.y = mesh->mVertices[verticeIdx].y;
			vertice.z = mesh->mVertices[verticeIdx].z;
			loadedVertices.push_back(vertice);
			glm::vec3 normal;
			normal.x = mesh->mNormals[verticeIdx].x;
			normal.y = mesh->mNormals[verticeIdx].y;
			normal.z = mesh->mNormals[verticeIdx].z;
			loadedNormals.push_back(normal);
			glm::vec2 uv;
			uv.x = mesh->mTextureCoords[0][verticeIdx].x;
			uv.y = mesh->mTextureCoords[0][verticeIdx].y;
			loadedUVs.push_back(uv);
		}

		for (unsigned int faceIdx = 0; faceIdx < mesh->mNumFaces; faceIdx++)
		{
			//Get the face
			aiFace face = mesh->mFaces[faceIdx];
			//Add the indices of the face to the vector
			for (unsigned int indiceIdx = 0; indiceIdx < face.mNumIndices; indiceIdx++) { loadedIndices.push_back(face.mIndices[indiceIdx]); }
		}
	}	
}
