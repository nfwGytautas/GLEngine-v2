#pragma once

class Material
{
public:
	Material(unsigned int id);
	~Material();

	//Temporary
	unsigned int GetTextureID()
	{
		return m_textureID;
	}
private:
	unsigned int m_textureID;
};

