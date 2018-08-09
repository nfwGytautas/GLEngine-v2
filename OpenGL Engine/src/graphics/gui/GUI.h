#pragma once
#include <glm\glm.hpp>

class GraphicsAPI;
class GUI
{
public:
	GUI(unsigned int mTexture, glm::vec2 mPosition, float mRotation ,glm::vec2 mScale);

	bool operator==(const GUI& gui) const
	{
		if (m_textureID != gui.m_textureID)
		{
			return false;
		}
		if (m_position != gui.m_position)
		{
			return false;
		}
		if (m_scale != gui.m_scale)
		{
			return false;
		}
		return true;
	}

	glm::vec2 getPosition()
	{
		return m_position;
	}
	float getRotation()
	{
		return m_rotation;
	}
	glm::vec2 getScale()
	{
		return m_scale;
	}
private:
	unsigned int m_textureID;
	glm::vec2 m_position;
	float m_rotation;
	glm::vec2 m_scale;

	friend GraphicsAPI;
};

