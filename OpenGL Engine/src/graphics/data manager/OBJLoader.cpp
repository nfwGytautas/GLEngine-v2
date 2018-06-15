#include "OBJLoader.h"

#include "DataManager.h"
#include "..\mesh\Mesh.h"

#include <Assimp\assimp\Importer.hpp>
#include <Assimp\assimp\scene.h>
#include <Assimp\assimp\postprocess.h>

#include <iostream>

#include <glm/glm.hpp>
#include "..\..\maths\Maths.h"

Mesh OBJLoader::LoadOBJ(std::string filePath, DataManager& manager)
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
		return Mesh(0, 0);
	}

	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec3> out_normals;
	std::vector<glm::vec2> out_uvs;
	std::vector<unsigned int> out_indices;

	for (unsigned int meshIdx = 0; meshIdx < scene->mNumMeshes; meshIdx++)
	{
		aiMesh* mesh = scene->mMeshes[meshIdx];

		for (unsigned int verticeIdx = 0; verticeIdx < mesh->mNumVertices; verticeIdx++)
		{
			glm::vec3 vertice;
			vertice.x = mesh->mVertices[verticeIdx].x;
			vertice.y = mesh->mVertices[verticeIdx].y;
			vertice.z = mesh->mVertices[verticeIdx].z;
			out_vertices.push_back(vertice);
			glm::vec3 normal;
			normal.x = mesh->mNormals[verticeIdx].x;
			normal.y = mesh->mNormals[verticeIdx].y;
			normal.z = mesh->mNormals[verticeIdx].z;
			out_normals.push_back(normal);
			glm::vec2 uv;
			uv.x = mesh->mTextureCoords[0][verticeIdx].x;
			uv.y = mesh->mTextureCoords[0][verticeIdx].y;
			out_uvs.push_back(uv);
		}

		for (unsigned int faceIdx = 0; faceIdx < mesh->mNumFaces; faceIdx++)
		{
			//Get the face
			aiFace face = mesh->mFaces[faceIdx];
			//Add the indices of the face to the vector
			for (unsigned int indiceIdx = 0; indiceIdx < face.mNumIndices; indiceIdx++) { out_indices.push_back(face.mIndices[indiceIdx]); }
		}
	}
	return manager.LoadToVAO(Maths::Vec3ToFloatVector(out_vertices), Maths::Vec2ToFloatVector(out_uvs), out_indices);
}