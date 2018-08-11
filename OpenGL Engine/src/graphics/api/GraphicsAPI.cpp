#include "GraphicsAPI.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\FrameworkAssert.h"

void GraphicsAPI::bindCubeMap(unsigned int id, unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, id));
}
void GraphicsAPI::bindTexture(unsigned int id, unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, id));
}
void GraphicsAPI::bindTexture(const CMaterial& mMaterial, unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, mMaterial.m_textureID));
}
void GraphicsAPI::bindTexture(const GUI& mGui, unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, mGui.m_textureID));
}
void GraphicsAPI::bindVAO(unsigned int id)
{
	GLCall(glBindVertexArray(id));
}

void GraphicsAPI::bindVAO(const CMesh& mMesh)
{
	GLCall(glBindVertexArray(mMesh.m_vaoID));
}
