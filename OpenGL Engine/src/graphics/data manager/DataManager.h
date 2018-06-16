#pragma once

#include <memory>
#include <vector>

class Mesh;

class DataManager
{
public:
	DataManager();
	~DataManager();

	Mesh LoadToVAO(std::vector<float> positions, std::vector<float> textureCoords, std::vector<float> normals, std::vector<unsigned int> indices);
	unsigned int LoadTexture(std::string filePath);


	void CleanUp();

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

