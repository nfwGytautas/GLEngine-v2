#include "OBJLoader.h"
#include <iostream>
#include <Assimp\assimp\Importer.hpp>
#include <Assimp\assimp\scene.h>
#include <Assimp\assimp\postprocess.h>

#include "..\..\maths\Maths.h"

std::vector<float> OBJLoader::loadedVertices;
std::vector<float> OBJLoader::loadedNormals;
std::vector<float> OBJLoader::loadedUVs;
std::vector<unsigned int> OBJLoader::loadedIndices;

bool OBJLoader::LoadOBJ(std::string filePath)
{
	//TODO: Instancing as cache
	loadedVertices.clear();
	loadedNormals.clear();
	loadedUVs.clear();
	loadedIndices.clear();

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(
		filePath,
		aiProcess_Triangulate |
		aiProcess_GenNormals |
		aiProcess_JoinIdenticalVertices
	);

	if (!scene)
	{
		std::cout << "[SGE][Data manager][OBJLoader] Assimp error." << importer.GetErrorString() << "\n";
		return false;
	}

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	for (unsigned int meshIdx = 0; meshIdx < scene->mNumMeshes; meshIdx++)
	{
		aiMesh* mesh = scene->mMeshes[meshIdx];

		try
		{
			for (unsigned int verticeIdx = 0; verticeIdx < mesh->mNumVertices; verticeIdx++)
			{
				glm::vec3 vertice;
				vertice.x = mesh->mVertices[verticeIdx].x;
				vertice.y = mesh->mVertices[verticeIdx].y;
				vertice.z = mesh->mVertices[verticeIdx].z;
				vertices.push_back(vertice);
				glm::vec3 normal;
				normal.x = mesh->mNormals[verticeIdx].x;
				normal.y = mesh->mNormals[verticeIdx].y;
				normal.z = mesh->mNormals[verticeIdx].z;
				normals.push_back(normal);
				glm::vec2 uv;
				if (mesh->mTextureCoords[0])
				{
					uv.x = mesh->mTextureCoords[0][verticeIdx].x;
					uv.y = mesh->mTextureCoords[0][verticeIdx].y;
				}
				else
				{
					uv = glm::vec2(0.0f, 0.0f);
				}
				uvs.push_back(uv);
			}
			for (unsigned int faceIdx = 0; faceIdx < mesh->mNumFaces; faceIdx++)
			{
				//Get the face
				aiFace face = mesh->mFaces[faceIdx];
				//Add the indices of the face to the vector
				for (unsigned int indiceIdx = 0; indiceIdx < face.mNumIndices; indiceIdx++) { loadedIndices.push_back(face.mIndices[indiceIdx]); }
			}
		}
		catch (...)
		{
			std::cout << "[Engine][Resource manager][OBJLoader] Parsing error! \n";
			return false;
		}
	}	


	loadedVertices = Maths::Vec3ToFloatVector(vertices);
	loadedNormals = Maths::Vec3ToFloatVector(normals);
	loadedUVs = Maths::Vec2ToFloatVector(uvs);
	return true;
}

void OBJLoader::loadFallbackMesh()
{
#pragma region OBJ DECLARATION


	std::vector<float> vertices = 
	{
		0.296f, -0.347089f, -0.102656f,
		0.142f, -0.6754f, -0.123928f,
		0.023f, -0.6754f, -0.123928f,
		0.356f, -0.415945f, -0.107118f,
		0.142f, -0.6754f, -0.123928f,
		0.356f, -0.415945f, -0.107118f,
		0.687f, -0.675401f, -0.123928f,
		0.569f, -0.675401f, -0.123928f,
		0.415f, -0.347089f, -0.102656f,
		0.687f, -0.675401f, -0.123928f,
		0.356f, -0.415945f, -0.107118f,
		0.002f, 0.005173f, -0.079833f,
		0.296f, -0.347089f, -0.102656f,
		0.356f, -0.276237f, -0.098066f,
		0.415f, -0.347089f, -0.102656f,
		0.356f, -0.276237f, -0.098066f,
		0.706f, 0.005172f, -0.079833f,
		0.121f, 0.005173f, -0.079833f,
		0.356f, -0.276237f, -0.098066f,
		0.588f, 0.005172f, -0.079833f,
		0.142f, -0.685745f, 0.035737f,
		0.296f, -0.357434f, 0.057009f,
		0.023f, -0.685745f, 0.035737f,
		0.356f, -0.42629f, 0.052548f,
		0.142f, -0.685745f, 0.035737f,
		0.687f, -0.685746f, 0.035737f,
		0.356f, -0.42629f, 0.052548f,
		0.569f, -0.685746f, 0.035737f,
		0.415f, -0.357434f, 0.057009f,
		0.687f, -0.685746f, 0.035737f,
		0.356f, -0.42629f, 0.052548f,
		0.002f, -0.005173f, 0.079833f,
		0.296f, -0.357434f, 0.057009f,
		0.356f, -0.286582f, 0.0616f,
		0.415f, -0.357434f, 0.057009f,
		0.706f, -0.005173f, 0.079833f,
		0.356f, -0.286582f, 0.0616f,
		0.121f, -0.005173f, 0.079833f,
		0.356f, -0.286582f, 0.0616f,
		0.588f, -0.005173f, 0.079833f,
		0.588f, 0.005172f, -0.079833f,
		0.706f, -0.005173f, 0.079833f,
		0.706f, 0.005172f, -0.079833f,
		0.356f, -0.276237f, -0.098066f,
		0.588f, -0.005173f, 0.079833f,
		0.588f, 0.005172f, -0.079833f,
		0.121f, 0.005173f, -0.079833f,
		0.356f, -0.286582f, 0.0616f,
		0.356f, -0.276237f, -0.098066f,
		0.002f, 0.005173f, -0.079833f,
		0.121f, -0.005173f, 0.079833f,
		0.121f, 0.005173f, -0.079833f,
		0.296f, -0.347089f, -0.102656f,
		0.002f, -0.005173f, 0.079833f,
		0.002f, 0.005173f, -0.079833f,
		0.023f, -0.6754f, -0.123928f,
		0.296f, -0.357434f, 0.057009f,
		0.296f, -0.347089f, -0.102656f,
		0.142f, -0.6754f, -0.123928f,
		0.023f, -0.685745f, 0.035737f,
		0.023f, -0.6754f, -0.123928f,
		0.356f, -0.415945f, -0.107118f,
		0.142f, -0.685745f, 0.035737f,
		0.142f, -0.6754f, -0.123928f,
		0.569f, -0.675401f, -0.123928f,
		0.356f, -0.42629f, 0.052548f,
		0.356f, -0.415945f, -0.107118f,
		0.687f, -0.675401f, -0.123928f,
		0.569f, -0.685746f, 0.035737f,
		0.569f, -0.675401f, -0.123928f,
		0.687f, -0.675401f, -0.123928f,
		0.415f, -0.357434f, 0.057009f,
		0.687f, -0.685746f, 0.035737f,
		0.706f, 0.005172f, -0.079833f,
		0.415f, -0.357434f, 0.057009f,
		0.415f, -0.347089f, -0.102656f,
		0.588f, -0.005173f, 0.079833f,
		0.356f, -0.286582f, 0.0616f,
		0.121f, -0.005173f, 0.079833f,
		0.002f, -0.005173f, 0.079833f,
		0.296f, -0.357434f, 0.057009f,
		0.023f, -0.685745f, 0.035737f,
		0.142f, -0.685745f, 0.035737f,
		0.356f, -0.42629f, 0.052548f,
		0.569f, -0.685746f, 0.035737f,
		0.687f, -0.685746f, 0.035737f,
		0.415f, -0.347089f, -0.102656f,
		0.706f, -0.005173f, 0.079833f
	};

	std::vector<float> textureCoords = 
	{
		0, 0,
		1, 0,
		1, 1,
		1, 0,
		1, 1,
		0, 0,
		1, 0,
		1, 1,
		1, 0,
		1, 1,
		1, 1,
		0, 0,
		1, 1,
		1, 0,
		1, 1,
		0, 0,
		1, 0,
		1, 0,
		1, 1,
		0, 0,
		0, 0,
		1, 0,
		1, 1,
		0, 0,
		1, 1,
		0, 0,
		1, 0,
		1, 1,
		0, 0,
		1, 1,
		1, 1,
		1, 0,
		1, 1,
		0, 0,
		1, 1,
		0, 0,
		1, 0,
		0, 0,
		1, 1,
		1, 0,
		1, 0,
		0, 1,
		0, 0,
		1, 0,
		0, 1,
		0, 0,
		1, 0,
		0, 1,
		0, 0,
		1, 0,
		0, 1,
		0, 0,
		1, 0,
		0, 1,
		0, 0,
		1, 0,
		0, 1,
		0, 0,
		1, 0,
		0, 1,
		0, 0,
		1, 0,
		0, 1,
		0, 0,
		1, 0,
		0, 1,
		0, 0,
		1, 0,
		0, 1,
		0, 0,
		0, 0,
		1, 1,
		0, 1,
		1, 0,
		0, 1,
		0, 0,
		1, 1,
		1, 1,
		1, 1,
		1, 1,
		1, 1,
		1, 1,
		1, 1,
		1, 1,
		1, 1,
		1, 1,
		1, 0,
		1, 1
	};

	std::vector<float> normals = 
	{
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, 0.0646f, -0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		0.0f, -0.0646f, 0.9979f,
		-0.427f, 0.9023f, 0.0584f,
		0.9044f, 0.4256f, 0.0276f,
		0.9044f, 0.4256f, 0.0276f,
		-0.0031f, 0.9979f, 0.0646f,
		-0.427f, 0.9023f, 0.0584f,
		-0.427f, 0.9023f, 0.0584f,
		0.4241f, 0.9037f, 0.0585f,
		-0.0031f, 0.9979f, 0.0646f,
		-0.0031f, 0.9979f, 0.0646f,
		-0.9055f, 0.4234f, 0.0274f,
		0.4241f, 0.9037f, 0.0585f,
		0.4241f, 0.9037f, 0.0585f,
		-1.0f, -0.0009f, -0.0f,
		-0.9055f, 0.4234f, 0.0274f,
		-0.9055f, 0.4234f, 0.0274f,
		-0.9051f, -0.4242f, -0.0275f,
		-1.0f, -0.0009f, -0.0f,
		-1.0f, -0.0009f, -0.0f,
		0.4269f, -0.9024f, -0.0584f,
		-0.9051f, -0.4242f, -0.0275f,
		-0.9051f, -0.4242f, -0.0275f,
		-0.0011f, -0.9979f, -0.0646f,
		0.4269f, -0.9024f, -0.0584f,
		0.4269f, -0.9024f, -0.0584f,
		-0.4279f, -0.9019f, -0.0584f,
		-0.0011f, -0.9979f, -0.0646f,
		-0.0011f, -0.9979f, -0.0646f,
		0.9048f, -0.425f, -0.0275f,
		-0.4279f, -0.9019f, -0.0584f,
		-0.4279f, -0.9019f, -0.0584f,
		0.9048f, -0.425f, -0.0275f,
		1.0f, 0.0007f, 0.0f,
		0.9048f, -0.425f, -0.0275f,
		0.9044f, 0.4256f, 0.0276f,
		1.0f, 0.0007f, 0.0f,
		1.0f, 0.0007f, 0.0f,
		-0.427f, 0.9023f, 0.0584f,
		-0.0031f, 0.9979f, 0.0646f,
		0.4241f, 0.9037f, 0.0585f,
		-0.9055f, 0.4234f, 0.0274f,
		-1.0f, -0.0009f, -0.0f,
		-0.9051f, -0.4242f, -0.0275f,
		0.4269f, -0.9024f, -0.0584f,
		-0.0011f, -0.9979f, -0.0646f,
		-0.4279f, -0.9019f, -0.0584f,
		0.9048f, -0.425f, -0.0275f,
		1.0f, 0.0007f, 0.0f,
		0.9044f, 0.4256f, 0.0276f
	};

	std::vector<unsigned int> indices = 
	{
		0, 1, 2,
		0, 3, 4,
		5, 6, 7,
		5, 8, 9,
		0, 8, 10,
		11, 8, 12,
		11, 13, 14,
		15, 16, 14,
		11, 17, 18,
		19, 16, 18,
		20, 21, 22,
		23, 21, 24,
		25, 26, 27,
		28, 26, 29,
		28, 21, 30,
		28, 31, 32,
		33, 31, 34,
		35, 36, 34,
		37, 31, 38,
		35, 39, 38,
		40, 41, 42,
		43, 44, 45,
		46, 47, 48,
		49, 50, 51,
		52, 53, 54,
		55, 56, 57,
		58, 59, 60,
		61, 62, 63,
		64, 65, 66,
		67, 68, 69,
		70, 71, 72,
		73, 74, 75,
		40, 76, 41,
		43, 77, 44,
		46, 78, 47,
		49, 79, 50,
		52, 80, 53,
		55, 81, 56,
		58, 82, 59,
		61, 83, 62,
		64, 84, 65,
		67, 85, 68,
		70, 86, 71,
		73, 87, 74
	};

#pragma endregion

	loadedVertices = vertices;
	loadedNormals = normals;
	loadedUVs = textureCoords;
	loadedIndices = indices;
}