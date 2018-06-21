#pragma once
#include <vector>
#include <string>
#include <glm\glm.hpp>
class OBJLoader
{
public:
	static void LoadOBJ(std::string filePath);
	static std::vector<glm::vec3> loadedVertices;
	static std::vector<glm::vec3> loadedNormals;
	static std::vector<glm::vec2> loadedUVs;
	static std::vector<unsigned int> loadedIndices;
};

