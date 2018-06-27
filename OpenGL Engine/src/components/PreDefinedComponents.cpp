#include "PreDefinedComponents.h"
#include "Entity.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\graphics\data manager\BatchManager.h"
#include "..\graphics\FrameworkAssert.h"
#include "..\graphics\gtypes\gTypes.h"
#include "..\maths\Maths.h"

void CTransformation::init()
{
	cPosition = &entity->getComponent<CPosition>();
}

void CTransformation::update(float frameTime)
{
	transformationMatrix = Maths::CreateTransformationMatrix(cPosition->value, glm::vec3(rotationX, rotationY, rotationZ), scale);
}

void CMesh::use()
{
	GLCall(glBindVertexArray(m_vaoID));
}

size_t CMesh::hash() const
{
	size_t res = 17;
	res = res * 31 + std::hash<unsigned int>()(vertexCount);
	res = res * 31 + std::hash<unsigned int>()(m_vaoID);
	return res;
}

void CMaterial::use()
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
}

size_t CMaterial::hash() const
{
	size_t res = 17;
	res = res * 31 + std::hash<float>()(shineDamper);
	res = res * 31 + std::hash<float>()(reflectivity);
	res = res * 31 + std::hash<unsigned int>()(m_textureID);
	return res;
}

void CLightEmiter::init()
{
	cPosition = &entity->getComponent<CPosition>();
	cColor = &entity->getComponent<CColor>();
}