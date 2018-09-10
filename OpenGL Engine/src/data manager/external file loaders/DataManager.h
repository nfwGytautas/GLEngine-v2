#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <glm\glm.hpp>
#include "..\data structures\Model.h"
#include "..\..\algorithm\Algorithm.h"

class Entity;
class DataManager
{
public:
	DataManager();
	~DataManager();

	VAO createVAO(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& textureCoords, std::vector<unsigned int>& indices);
	VAO createVAO(std::string pathToFile);

	VAO create2DQuad(std::vector<float>& vertices);
	VAO create3DCube(std::vector<float>& vertices);
	std::tuple<unsigned int, unsigned int, unsigned int> createSkybox();

	/*Texture files must be in this order: Right, Left, Top, Bottom, Back, Front*/
	unsigned int loadCubeMap(std::vector<std::string>& textureFiles);
	unsigned int loadTexture(std::string mFilePath);

	Model loadModel(std::string pathToModel);

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

	std::unordered_map<std::string, VAO> m_VAOCache;
	std::unordered_map<std::string, ShadingMap> m_shadingMapCache;
	std::unordered_map<std::string, Model> m_modelCache;

	unsigned int m_fallbackTexture;
	unsigned int m_fallbackMeshID;
	unsigned int m_fallbackMeshVertexCount;
};