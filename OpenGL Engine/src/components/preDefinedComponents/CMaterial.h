#pragma once
#include "..\Component.h"
//Dependencies
class BatchManager;
class GraphicsAPI;

struct CMaterial : Component
{
	float shineDamper;
	float reflectivity;

	CMaterial(unsigned int mTextureID, float mShineDamper, float mReflectivity);

	size_t hash() const;
	bool operator==(const CMaterial& mat) const
	{
		if (hash() == mat.hash())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator!=(const CMaterial& mat) const
	{
		return !(*this == mat);
	}

	virtual CMaterial* clone() { return new CMaterial(*this); }
private:
	unsigned int m_textureID;
	friend BatchManager;
	friend GraphicsAPI;
};