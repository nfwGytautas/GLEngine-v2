#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <glm\glm.hpp>
#include "..\algorithm\Algorithm.h"


class DataManager
{
public:
	DataManager();
	~DataManager();

	std::pair<unsigned int, unsigned int> loadMesh(std::string mFilePath);
	std::pair<unsigned int, unsigned int> createMesh(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& textureCoords, std::vector<unsigned int>& indices);
	std::pair<unsigned int, unsigned int> create2DQuad(std::vector<float>& vertices);
	std::pair<unsigned int, unsigned int> create3DCube(std::vector<float>& vertices);
	std::tuple<unsigned int, unsigned int, unsigned int> createSkybox();
	std::pair<unsigned int, unsigned int> createFlatMesh(unsigned int vertexCount, unsigned int size);
	std::pair<unsigned int, unsigned int> createHeightMappedMesh(std::string mHeightMapFilePath, float mMaxHeight, unsigned int size, continuous2DArray<float>& mCalculatedHeights);

	unsigned int loadMaterial(std::string mFilePath);
	/*Texture files must be in this order: Right, Left, Top, Bottom, Back, Front*/
	unsigned int loadCubeMap(std::vector<std::string>& textureFiles);
	unsigned int loadTexture(std::string mFilePath);


	void cleanUp();
private:
	void createFallbacks();
	unsigned int createVAO();
	void storeDataInAttributes(unsigned int location, unsigned int dataSize, std::vector<float> positions);
	void bindIndiceBuffer(std::vector<unsigned int> indices);
	void unbindVAO();
	void textureSetup();
	glm::vec3 calculateNormal(int x, int y, std::vector<glm::vec3>& mHeightMap, float maxPixelColor, float mMaxHeight);
	float getHeight(int x, int y, std::vector<glm::vec3>& mHeightMap, float maxPixelColor, float mMaxHeight);
private:
	std::vector<unsigned int> m_vaos;
	std::vector<unsigned int> m_vbos;
	std::vector<unsigned int> m_textures;

	unsigned int m_fallbackTexture;
	unsigned int m_fallbackMeshID;
	unsigned int m_fallbackMeshVertexCount;

	std::unordered_map<std::string, std::pair<unsigned int, unsigned int>> m_meshCache;
	std::unordered_map<std::string, unsigned int> m_materialCache;
};