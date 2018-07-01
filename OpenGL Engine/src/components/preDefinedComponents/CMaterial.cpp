#include "CMaterial.h"
#include <functional>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\..\graphics\FrameworkAssert.h"

void CMaterial::use()
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
}

CMaterial::CMaterial(unsigned int mTextureID, float mShineDamper, float mReflectivity)
	: m_textureID{ mTextureID }, shineDamper{ mShineDamper }, reflectivity{ mReflectivity } {}

size_t CMaterial::hash() const
{
	size_t res = 17;
	res = res * 31 + std::hash<float>()(shineDamper);
	res = res * 31 + std::hash<float>()(reflectivity);
	res = res * 31 + std::hash<unsigned int>()(m_textureID);
	return res;
}