#pragma once
#include <memory>
#include <vector>
#include <string>
class Entity;
class DataManager
{
public:
	DataManager();
	~DataManager();

	void loadMesh(Entity& mTarget, std::string mFilePath);
	unsigned int loadMaterial(std::string mFilePath);

	void cleanUp();
private:
	unsigned int createVAO();
	void storeDataInAttributes(unsigned int location, unsigned int dataSize, std::vector<float> positions);
	void bindIndiceBuffer(std::vector<unsigned int> indices);
	void unbindVAO();
private:
	std::vector<unsigned int> m_vaos;
	std::vector<unsigned int> m_vbos;
	std::vector<unsigned int> m_textures;
};