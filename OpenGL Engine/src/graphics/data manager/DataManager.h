#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <utility>
class DataManager
{
public:
	DataManager();
	~DataManager();

	std::pair<unsigned int, unsigned int> loadMesh(std::string mFilePath);
	unsigned int loadMaterial(std::string mFilePath);

	void cleanUp();
private:
	unsigned int createVAO();
	void storeDataInAttributes(unsigned int location, unsigned int dataSize, std::vector<float> positions);
	void bindIndiceBuffer(std::vector<unsigned int> indices);
	void unbindVAO();

	std::vector<float> fallbackTexture();
	void fallbackMesh();
	void createFallbacks();
private:
	std::vector<unsigned int> m_vaos;
	std::vector<unsigned int> m_vbos;
	std::vector<unsigned int> m_textures;

	unsigned int m_fallbackTexture;
	unsigned int m_fallbackMeshID;
	unsigned int m_fallbackMeshVertexCount;

	std::unordered_map<std::string, std::pair<unsigned int, unsigned int>> m_meshCache;
};