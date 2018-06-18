#include "TerrainRenderer.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\FrameworkAssert.h"
#include "..\gtypes\gTypes.h"
#include "..\renderables\Terrain.h"
#include "..\shader\TerrainShader.h"

#include "..\..\maths\Maths.h"

TerrainRenderer::TerrainRenderer(TerrainShader& shader, glm::mat4 projectionMatrix)
	:m_shader(shader)
{
	m_shader.Bind();
	m_shader.LoadProjectionMatrix(projectionMatrix);
}
TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::Render(std::vector<Terrain> terrains)
{
	for (Terrain x : terrains)
	{
		prepareTerrain(x);
		loadModelMatrix(x);
		GLCall(glDrawElements(GL_TRIANGLES, (GLsizei)x.GetMesh().GetVertexCount(), GL_UNSIGNED_INT, (void*)0));
		unbindTerrain();
	}
}

void TerrainRenderer::prepareTerrain(Terrain& terrain)
{
	Mesh mesh = terrain.GetMesh();
	GLCall(glBindVertexArray(mesh.GetRenderID()));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Position));
	GLCall(glEnableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glEnableVertexAttribArray(AttributeLocation::Normal));
	Material material = terrain.GetMaterial();
	m_shader.LoadShineVariables(material.GetShineDamper(), material.GetReflectivity());
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, material.GetTextureID()));
}

void TerrainRenderer::unbindTerrain()
{
	GLCall(glDisableVertexAttribArray(AttributeLocation::Position));
	GLCall(glDisableVertexAttribArray(AttributeLocation::UVs));
	GLCall(glDisableVertexAttribArray(AttributeLocation::Normal));
	GLCall(glBindVertexArray(0));
}

void TerrainRenderer::loadModelMatrix(Terrain& terrain)
{
	m_shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(glm::vec3(terrain.GetX(), 0, terrain.GetZ()) , glm::vec3(0,0,0), 1));
}