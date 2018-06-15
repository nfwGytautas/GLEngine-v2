#pragma once

#include <string>

class Mesh;
class DataManager;

class OBJLoader
{
public:
	static Mesh LoadOBJ(std::string filePath, DataManager& manager);
};

