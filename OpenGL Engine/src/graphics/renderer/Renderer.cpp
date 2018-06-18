#include "Renderer.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\gtypes\gTypes.h"

#include "..\FrameworkAssert.h"

#include "..\mesh\Mesh.h"
#include "..\material\Material.h"
#include "..\renderables\Model.h"
#include "..\renderables\Entity.h"

#include "..\..\maths\Maths.h"

#include "..\shader\StaticShader.h"

Renderer3D::Renderer3D(StaticShader& shader, glm::mat4 projectionMatrix)
	:m_shader(shader)
{
	m_shader.Bind();
	m_shader.LoadProjectionMatrix(projectionMatrix);
	m_shader.Unbind();
}
Renderer3D::~Renderer3D()
{
}

void Renderer3D::Render(std::unordered_map<Model, std::vector<Entity>, KeyHasher> renderList)
{
	for(auto it : renderList)
	{
		Model model = it.first;
		prepareModel(model);
		std::vector<Entity> batch = it.second;
		for (Entity entity : batch)
		{
			prepareInstance(entity);
			GLCall(glDrawElements(GL_TRIANGLES, (GLsizei)model.GetMesh().GetVertexCount(), GL_UNSIGNED_INT, (void*)0));
		}
		unbindModel();
	}
}

void Renderer3D::prepareModel(Model & model)
{
	Mesh mesh = model.GetMesh();
	GLCall(glBindVertexArray(mesh.GetRenderID()));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
	GLCall(glEnableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Normal));
	Material material = model.GetMaterial();
	m_shader.LoadShineVariables(material.GetShineDamper(), material.GetReflectivity());
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, model.GetMaterial().GetTextureID()));
}

void Renderer3D::unbindModel()
{
	GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
	GLCall(glDisableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Normal));
	GLCall(glBindVertexArray(0));
}

void Renderer3D::prepareInstance(Entity & entity)
{
	m_shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));
}