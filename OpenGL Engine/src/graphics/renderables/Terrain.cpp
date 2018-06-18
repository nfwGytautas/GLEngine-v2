#include "Terrain.h"

#include <vector>

#include "..\..\Engine.h"

Terrain::Terrain(int xPosition, int zPosition, Material texture)
	:m_x((float)xPosition * size), m_z((float)zPosition * size), m_texture(texture), m_mesh(Mesh(-1, 0))
{
	GenerateTerrain();
}

Terrain::~Terrain()
{
}

void Terrain::GenerateTerrain()
{
	int count = vertexCount * vertexCount;

	std::vector<float> vertices;
	vertices.resize(count * 3);

	std::vector<float> normals;
	normals.resize(count * 3);

	std::vector<float> textureCoords;
	textureCoords.resize(count * 2);

	std::vector<unsigned int> indices;
	indices.resize(6 * (vertexCount - 1) * (vertexCount - 1));

	int vertexIndex = 0;
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			vertices[vertexIndex * 3] = (float)j / ((float)vertexCount - 1) * size;
			vertices[vertexIndex * 3 + 1] = 0;
			vertices[vertexIndex * 3 + 2] = (float)i / ((float)vertexCount - 1) * size;
			normals[vertexIndex * 3] = 0;
			normals[vertexIndex * 3 + 1] = 1;
			normals[vertexIndex * 3 + 2] = 0;
			textureCoords[vertexIndex * 2] = (float)j / ((float)vertexCount - 1);
			textureCoords[vertexIndex * 2 + 1] = (float)i / ((float)vertexCount - 1);
			vertexIndex++;
		}
	}

	int index = 0;
	for (int gz = 0; gz < vertexCount - 1; gz++) {
		for (int gx = 0; gx < vertexCount - 1; gx++) {
			int topLeft = (gz * vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * vertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			indices[index++] = topLeft;
			indices[index++] = bottomLeft;
			indices[index++] = topRight;
			indices[index++] = topRight;
			indices[index++] = bottomLeft;
			indices[index++] = bottomRight;
		}
	}

	m_mesh = Engine::Loader::LoadToVAO(vertices, textureCoords, normals, indices);
}
