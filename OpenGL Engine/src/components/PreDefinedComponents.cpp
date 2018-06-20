#include "PreDefinedComponents.h"
#include "Entity.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\graphics\gtypes\gTypes.h"
#include "..\graphics\FrameworkAssert.h"
#include "..\graphics\maths\Maths.h"
#include "..\graphics\graphics\shader\StaticShader.h"

void CTransformation::init()
{
	cPosition = &entity->getComponent<CPosition>();
}

void CTransformation::draw()
{
	m_shader->LoadTransformationMatrix
	(
		Maths::CreateTransformationMatrix(cPosition->position, glm::vec3(rotationX, rotationY, rotationZ), scale)
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
