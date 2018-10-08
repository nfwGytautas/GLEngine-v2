#pragma once
#include <vector>
#include "Asset.h"

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

class AssetLoader
{
public:	
	Asset* loadAsset(std::string filePath, std::string name, AssetType type);

public:
	AssetLoader();
	~AssetLoader();
private:
	//Model
	Asset* loadModelAsset(std::string filePath, std::string name);

	//Image
	Asset* loadImageAsset(std::string filePath, std::string name);

	void freeData(unsigned char* buffer);

	//Pointer storage
	std::vector<Asset*> m_LoadedAssets;
};

