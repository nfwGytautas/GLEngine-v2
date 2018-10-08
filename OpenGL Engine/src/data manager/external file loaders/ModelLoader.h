#pragma once
#include <string>
#include <vector>
#include <glm\glm.hpp>
#include <Assimp/assimp/Importer.hpp>
#include <Assimp/assimp/scene.h>
#include <Assimp/assimp/postprocess.h>

struct RawMeshData
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;
	std::string diffuse_map;
	std::string specular_map;
	float shininess;
	float width;
	float height;
	float depth;
};

class ModelLoader
{
public:
	static void loadModel(std::string& path);

	static std::vector<RawMeshData> modelMeshes;
private:
	static void processNode(aiNode* node, const aiScene* scene);
	static void processMinMax(glm::vec3& maxValues, glm::vec3& minValues, const glm::vec3& currentVertex);
	static RawMeshData processMesh(aiMesh* mesh, const aiScene* scene);
	static void loadMaterialTextures(aiMaterial* mat, aiTextureType type, RawMeshData& target);
};

