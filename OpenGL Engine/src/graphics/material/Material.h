#pragma once

#ifdef NFW_DLL_EXPORT
#	define NFW_API __declspec(dllexport)
#else
#	define NFW_API __declspec(dllimport)
#endif

class NFW_API Material
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

