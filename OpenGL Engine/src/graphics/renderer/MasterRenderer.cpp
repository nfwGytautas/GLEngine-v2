#include "MasterRenderer.h"

#include "Renderer.h"
#include "TerrainRenderer.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>

#include "..\display\Display.h"
#include "..\FrameworkAssert.h"
#include "..\shader\StaticShader.h"
#include "..\shader\TerrainShader.h"

#include "..\renderables\Entity.h"
#include "..\material\Material.h"
#include "..\renderables\Light.h"
#include "..\display\Camera.h"
#include "..\renderables\Terrain.h"

MasterRenderer::MasterRenderer(StaticShader& shader, TerrainShader& terrainShader)
	:m_shader(shader), m_terrainShader(terrainShader)
{
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));
	createProjectionMatrix();
	m_renderer = new Renderer3D(m_shader, m_projectionMatrix);
	m_terrainRenderer = new TerrainRenderer(m_terrainShader, m_projectionMatrix);
}

MasterRenderer::~MasterRenderer()
{
	delete m_renderer;
	delete m_terrainRenderer;
}

void MasterRenderer::Prepare()
{
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0, 0.3f, 0.0f, 1));
}

void MasterRenderer::ProcessEntity(Entity& entity)
{
	Model entityModel = entity.GetModel();

	if (m_entitiesHashMap.find(entityModel) != m_entitiesHashMap.end())
	{
		m_entitiesHashMap[entityModel].push_back(entity);
	}
	else
	{
		std::vector<Entity> newBatch;
		newBatch.push_back(entity);
		m_entitiesHashMap[entityModel] = newBatch;
	}
}

void MasterRenderer::ProcessTerrain(Terrain& terrain)
{
	m_terrains.push_back(terrain);
}

void MasterRenderer::Render(Light& sun, Camera& camera)
{
	Prepare();
	m_shader.Bind();
	m_shader.LoadLight(sun);
	m_shader.LoadViewMatrix(camera);
	m_renderer->Render(m_entitiesHashMap);
	m_shader.Unbind();
	m_entitiesHashMap.clear();

	m_terrainShader.Bind();
	m_terrainShader.LoadLight(sun);
	m_terrainShader.LoadViewMatrix(camera);
	m_terrainRenderer->Render(m_terrains);
	m_terrainShader.Unbind();
	m_terrains.clear();
}

void MasterRenderer::createProjectionMatrix()
{
	float aspectRatio = (float)Display::GetWidth() / (float)Display::GetHeight();
	float y_scale = (float)((1.0f / glm::tan(glm::radians(FOV / 2.0f))) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = FAR_PLANE - NEAR_PLANE;

	m_projectionMatrix = glm::mat4(1);
	m_projectionMatrix[0] = glm::vec4(x_scale, 0, 0, 0);
	m_projectionMatrix[1] = glm::vec4(0, y_scale, 0, 0);
	m_projectionMatrix[2] = glm::vec4(0, 0, -((FAR_PLANE + NEAR_PLANE) / frustum_length), -1);
	m_projectionMatrix[3] = glm::vec4(0, 0, -((2 * FAR_PLANE * NEAR_PLANE) / frustum_length), 0);
}