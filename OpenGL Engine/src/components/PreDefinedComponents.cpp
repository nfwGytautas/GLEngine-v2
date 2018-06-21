#include "PreDefinedComponents.h"
#include "Entity.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\graphics\FrameworkAssert.h"
#include "..\graphics\gtypes\gTypes.h"
#include "..\graphics\shader\StaticShader.h"
#include "..\maths\Maths.h"

void CTransformation::init()
{
	cPosition = &entity->getComponent<CPosition>();
}

void CTransformation::draw()
{
	m_shader->LoadTransformationMatrix
	(
		Maths::CreateTransformationMatrix(cPosition->value, glm::vec3(rotationX, rotationY, rotationZ), scale)
	);
}

void CMesh::draw()
{
	GLCall(glBindVertexArray(m_vaoID));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
	GLCall(glEnableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Normal));	
}

void CMaterial::draw()
{
	m_shader->LoadShineVariables(shineDamper, reflectivity);
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
}

void CRenderer::draw()
{
	GLCall(glDrawElements(GL_TRIANGLES, entity->getComponent<CMesh>().vertexCount, GL_UNSIGNED_INT, (void*)0));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
	GLCall(glDisableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Normal));
	GLCall(glBindVertexArray(0));
}

void CLightEmiter::init()
{
	cPosition = &entity->getComponent<CPosition>();
	cColor = &entity->getComponent<CColor>();
}

void CLightEmiter::draw()
{
	m_shader->loadLight(*entity);
}