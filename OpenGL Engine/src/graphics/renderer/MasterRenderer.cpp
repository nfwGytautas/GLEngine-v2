#include "MasterRenderer.h"

#include "Renderer.h"

#include "..\shader\StaticShader.h"

#include "..\renderables\Entity.h"
#include "..\material\Material.h"
#include "..\renderables\Light.h"
#include "..\display\Camera.h"

MasterRenderer::MasterRenderer(StaticShader& shader)
	:m_shader(shader)
{
	m_renderer = new Renderer3D(m_shader);
}

MasterRenderer::~MasterRenderer()
{
	delete m_renderer;
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

void MasterRenderer::Render(Light& sun, Camera& camera)
{
	m_renderer->Prepare();
	m_shader.Bind();
	m_shader.LoadLight(sun);
	m_shader.LoadViewMatrix(camera);
	m_renderer->Render(m_entitiesHashMap);
	m_shader.Unbind();
	m_entitiesHashMap.clear();
}