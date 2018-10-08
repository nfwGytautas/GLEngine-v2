#pragma once
#include <vector>
#include "..\gui\GUI.h"

struct VAO
{
	VAO();
	VAO(unsigned int ID, unsigned int elementCount);

	unsigned int ID;
	unsigned int elementCount;

	//Compares vertex arrays
	inline bool operator==(const VAO& rhs) const;
	inline bool operator!=(const VAO& rhs) const
	{
		return !(*this == rhs);
	}
};
struct Texture
{
	Texture();
	Texture(unsigned int ID);

	unsigned int ID;

	//Compares textures
	inline bool operator==(const Texture& rhs) const;
	inline bool operator!=(const Texture& rhs) const
	{
		return !(*this == rhs);
	}
};

class GraphicsAPI
{
public:
	static bool initialize();

	static void bindCubeMap(unsigned int id, unsigned int slot = 0);

	static void bindTexture(unsigned int id, unsigned int slot = 0);
	static void bindTexture(const GUI* mGui, unsigned int slot = 0);

	static void bindVAO(unsigned int id);

private:
	static unsigned int m_currentVAO;
	static unsigned int m_currentTextures[16];

	static std::vector<VAO> m_VAOS;
	static std::vector<Texture> m_TEXTURES;
};