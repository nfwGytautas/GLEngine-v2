#include "GUI.h"
#include "..\..\SGEDefs.h"

GUI::GUI(std::string mFilepath, glm::vec2 mPosition, float mRotation, glm::vec2 mScale)
	: m_textureID(SGE::Instances::instances->dataManagerInstance->loadTexture(mFilepath)), m_position(mPosition), m_rotation(mRotation), m_scale(mScale)
{
	SGE::Instances::instances->batchManagerInstance->acknowledgeGUI(this);
}
