#pragma once

class Material
{
public:
	Material(unsigned int id);
	Material(unsigned int id, float shineDamper, float reflectivity);
	~Material();

	//Temporary
	unsigned int GetTextureID()
	{
		return m_textureID;
	}
	//Temporary
	float GetShineDamper()
	{
		return m_shineDamper;
	}
	//Temporary
	float GetReflectivity()
	{
		return m_reflectivity;
	}
private:
	unsigned int m_textureID;
	float m_shineDamper;
	float m_reflectivity;
};

