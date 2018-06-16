#include "Renderer.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\gtc\matrix_transform.hpp>

#include "..\gtypes\gTypes.h"

#include "..\FrameworkAssert.h"

#include "..\display\Display.h"

#include "..\mesh\Mesh.h"
#include "..\material\Material.h"
#include "..\renderables\Model.h"
#include "..\renderables\Entity.h"

#include "..\..\maths\Maths.h"

#include "..\shader\StaticShader.h"

Renderer3D::Renderer3D(StaticShader* shader)
{
	createProjectionMatrix();
	shader->Bind();
	shader->LoadProjectionMatrix(m_projectionMatrix);
	shader->Unbind();
}
Renderer3D::~Renderer3D()
{
}

void Renderer3D::Prepare()
{
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0, 0.3f, 0.0f, 1));
}

void Renderer3D::Render(Entity entity, StaticShader* shader)
{
	Model model = entity.GetModel();
	Mesh mesh = model.GetMesh();
	GLCall(glBindVertexArray(mesh.GetRenderID()));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
	GLCall(glEnableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Normal));
	shader->LoadTransformationMatrix(Maths::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, model.GetMaterial().GetTextureID()));
	GLCall(glDrawElements(GL_TRIANGLES, (GLsizei)mesh.GetVertexCount(), GL_UNSIGNED_INT, (void*)0));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
	GLCall(glDisableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Normal));
	GLCall(glBindVertexArray(0));
}

void Renderer3D::createProjectionMatrix()
{
	float aspectRatio = (float)Display::GetWidth() / (float)Display::GetHeight();
	float y_scale = (float)((1.0f / glm::tan(glm::radians(FOV / 2.0f))) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = FAR_PLANE - NEAR_PLANE;

	m_projectionMatrix = glm::mat4(1);
	m_projectionMatrix[0] = glm::vec4(x_scale, 0, 0, 0);
	m_projectionMatrix[1] = glm::vec4(0, y_scale, 0 , 0);
	m_projectionMatrix[2] = glm::vec4(0, 0, -((FAR_PLANE + NEAR_PLANE) / frustum_length), -1);
	m_projectionMatrix[3] = glm::vec4(0, 0, -((2 * FAR_PLANE * NEAR_PLANE) / frustum_length), 0);
}
