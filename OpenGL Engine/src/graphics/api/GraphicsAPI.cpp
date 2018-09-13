#include "GraphicsAPI.h"
#include "..\..\SGEDefs.h"
#include <iostream>

unsigned int GraphicsAPI::m_currentVAO = 0;
unsigned int GraphicsAPI::m_currentTextures[16] = { 0 };

bool GraphicsAPI::initialize()
{
	#ifdef SGE_GRAPHICS_TECHNOLOGY_OPENGL

	//Initializes glfw
	if (!glfwInit())
	{
		GLCall(glfwTerminate());
		std::cout << "[SGE] GLFW could not be initialized!" << std::endl;
		return false;
	}

	//Creates display
	if (!Display::createDisplay())
	{
		std::cout << "[SGE] Window could not be created!" << std::endl;
		return false;
	}

	//Initializes glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "[SGE] GLEW could not be initialized!" << std::endl;
		return false;
	}

	#endif // SGE_GRAPHICS_TECHNOLOGY_OPENGL	
	return true;
}

void GraphicsAPI::bindCubeMap(unsigned int id, unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, id));
}
void GraphicsAPI::bindTexture(unsigned int id, unsigned int slot)
{
	if (m_currentTextures[slot] != id)
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, id));
		m_currentTextures[slot] = id;
	}
}

void GraphicsAPI::bindTexture(const GUI* mGui, unsigned int slot)
{
	bindTexture(mGui->m_textureID, slot);
}
void GraphicsAPI::bindVAO(unsigned int id)
{
	if (m_currentVAO != id)
	{
		GLCall(glBindVertexArray(id));
		m_currentVAO = id;
	}
}