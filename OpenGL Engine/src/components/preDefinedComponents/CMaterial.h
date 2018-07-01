#pragma once
#include "..\Component.h"
//Dependencies
class BatchManager;

struct CMaterial : Component
{
	void use();

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
private:
	unsigned int m_textureID;
	friend BatchManager;
};