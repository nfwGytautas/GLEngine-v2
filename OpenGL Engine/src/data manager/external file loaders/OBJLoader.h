#pragma once
#include <vector>
#include <string>
#include <glm\glm.hpp>
class OBJLoader
{
public:
	static bool LoadOBJ(std::string filePath);
	static std::vector<float> loadedVertices;
	static std::vector<float> loadedNormals;
	static std::vector<float> loadedUVs;
	static std::vector<unsigned int> loadedIndices;
	static void calculateMinMax(glm::vec3& maxValues, glm::vec3& minValues, const glm::vec3& currentVertex);

	static void loadFallbackMesh();
};

