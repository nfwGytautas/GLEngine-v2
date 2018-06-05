#pragma once

#include <memory>
#include <vector>

class Mesh;

class DataManager
{
public:
	DataManager();
	~DataManager();

	Mesh LoadToVAO(std::vector<float> positions);


	void CleanUp();

private:
	unsigned int createVAO();
	void storeDataInAttributes(unsigned int location, std::vector<float> positions);

	void unbindVAO();

private:
	std::vector<unsigned int> m_vaos;
	std::vector<unsigned int> m_vbos;
};

